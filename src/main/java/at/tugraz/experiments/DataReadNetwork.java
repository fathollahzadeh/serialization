package at.tugraz.experiments;

import at.tugraz.util.MachineInfo;
import at.tugraz.util.Network;
import at.tugraz.runtime.ObjectReader;
import at.tugraz.runtime.ObjectWriter;
import at.tugraz.tweet.TweetStatus;
import at.tugraz.util.CommonThreadPool;
import at.tugraz.util.Const;
import at.tugraz.util.NodeType;
import at.tugraz.util.RootData;
import org.apache.log4j.Logger;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.PriorityQueue;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;

public class DataReadNetwork {

    private static Logger logger = Logger.getLogger(DataReadNetwork.class);

    public static void main(String[] args) throws IOException, InterruptedException, ExecutionException {

        // disk-to-disk (d2d)
        // disk-to-memory (d2m)
        // memory-to-memory (m2m)
        // memory-to-disk (m2d)

        String inDataPath = System.getProperty("inDataPath");
        String method = System.getProperty("method");
        String config = System.getProperty("config");
        String plan = System.getProperty("plan");

        String localMethod = "Kryo";

        if (plan.equalsIgnoreCase("d2d") || plan.equalsIgnoreCase("d2m"))
            localMethod = method;

        Network network = new Network(config);
        MachineInfo machineInfo = network.getCurrentMachine();
        ObjectReader reader = new ObjectReader(inDataPath, localMethod);

        if (machineInfo.getNodeType() == NodeType.LEAF) {
            ArrayList<RootData> list = new ArrayList<>();
            reader.readObjects(0, machineInfo.getNrow(), list);
            Collections.sort(list);

            ObjectWriter writer = new ObjectWriter(method, machineInfo.getTotalNRow(), Const.NETWORK_PAGESIZE);
            Client client = initClient(machineInfo.getRoot().getIp(), machineInfo.getPort());
            for (RootData rd : list)
                writer.writeObjectToNetworkPage(rd, client.dos, client.dis);

            writer.flushToNetwork(client.dos, client.dis);
            client.socket.close();

        } else if (machineInfo.getNodeType() == NodeType.MIDDLE) {
            ServerSocket serverSocket = new ServerSocket(machineInfo.getPort());
            serverSocket.setSoTimeout(Const.NETWORK_TIMEOUT);
            Client client = initClient(machineInfo.getRoot().getIp(), machineInfo.getPort());

            ArrayList<Task> tasks = new ArrayList<>();
            ArrayList<Task> dataTasks = new ArrayList<>();
            ExecutorService pool = CommonThreadPool.get(machineInfo.getLeaves().size() + 3);
            Socket socket;

            for (int i = 0; i < machineInfo.getLeaves().size(); i++) {
                socket = serverSocket.accept();
                logger.info("Accepted Client In MIDDLE node:" + machineInfo.getIp() + " Client >> " + socket.getLocalAddress() + " - " + socket.getInetAddress().getHostAddress());

                Client cli = new Client(socket, new DataOutputStream(socket.getOutputStream()), new DataInputStream(socket.getInputStream()));
                ObjectReader clientReader = new ObjectReader(method);
                NetworkReadTask clientTask = new NetworkReadTask(cli, clientReader);
                tasks.add(clientTask);
                dataTasks.add(clientTask);
            }

            // read objects from local
            Task clientTask = new LocalReadTask(reader, machineInfo.getNrow());
            tasks.add(clientTask);
            dataTasks.add(clientTask);

            ObjectWriter writer = new ObjectWriter(method, machineInfo.getTotalNRow(), Const.NETWORK_PAGESIZE);
            // add external sort task
            tasks.add(new ExternalSortTask(dataTasks, writer, false, client.dis, client.dos));

            // invoke all tasks
            List<Future<Boolean>> rt = pool.invokeAll(tasks);
            pool.shutdown();

            //check for exceptions
            for (Future<Boolean> f : rt) {
                f.get();
            }
        } else if (machineInfo.getNodeType() == NodeType.ROOT) {
            String outDataPath = System.getProperty("outDataPath");
            ObjectWriter writer = new ObjectWriter(outDataPath, method, machineInfo.getTotalNRow());
            ServerSocket serverSocket = new ServerSocket(machineInfo.getPort());
            serverSocket.setSoTimeout(Const.NETWORK_TIMEOUT);

            ArrayList<Task> tasks = new ArrayList<>();
            ArrayList<Task> dataTasks = new ArrayList<>();
            ExecutorService pool = CommonThreadPool.get(machineInfo.getLeaves().size() + 3);
            Socket socket;
            for (int i = 0; i < machineInfo.getLeaves().size(); i++) {
                socket = serverSocket.accept();
                logger.info("Accepted Client In ROOT node:" + machineInfo.getIp() + " Client >> " + socket.getInetAddress().getHostAddress());

                Client cli = new Client(socket, new DataOutputStream(socket.getOutputStream()), new DataInputStream(socket.getInputStream()));
                ObjectReader clientReader = new ObjectReader(method);
                NetworkReadTask clientTask = new NetworkReadTask(cli, clientReader);
                tasks.add(clientTask);
                dataTasks.add(clientTask);

            }
            // read objects from local
            Task clientTask = new LocalReadTask(reader, machineInfo.getNrow());
            tasks.add(clientTask);
            dataTasks.add(clientTask);

            // add external sort task
            if (plan.equalsIgnoreCase("d2d") || plan.equalsIgnoreCase("m2d"))
                tasks.add(new ExternalSortTask(dataTasks, writer, true, null, null));
            else
                tasks.add(new ExternalSortTask(dataTasks, null, true, null, null));


            List<Future<Boolean>> rt = pool.invokeAll(tasks);
            pool.shutdown();

            //check for exceptions
            for (Future<Boolean> f : rt) {
                f.get();
            }
        }
    }

    private static Client initClient(String ip, int port) throws InterruptedException {
        boolean flag = false;
        Socket socket;
        Client client = null;
        for (int i = 0; i < 10 && !flag; i++) {
            TimeUnit.SECONDS.sleep(1);
            try {
                socket = new Socket(ip, port);
                socket.setSoTimeout(Const.NETWORK_TIMEOUT);
                client = new Client(socket, new DataOutputStream(socket.getOutputStream()), new DataInputStream(socket.getInputStream()));
                flag = socket.isConnected();
            } catch (Exception ignored) {
            }
        }
        if (!flag) throw new RuntimeException("Client can't start >> " + ip + ":" + port);
        else {
           return client;
        }
    }

    private static abstract class Task implements Callable<Boolean> {
        protected final ObjectReader reader;
        protected final BlockingQueue<ArrayList<RootData>> queue;
        protected boolean status;

        public Task(ObjectReader reader) {
            this.reader = reader;
            this.queue = new ArrayBlockingQueue<>(Const.NETWORK_CLIENT_QUEUE_SIZE);
        }
    }

    private static class NetworkReadTask extends Task {
        protected final Client client;

        public NetworkReadTask(Client client, ObjectReader reader) {
            super(reader);
            this.client = client;
        }

        @Override
        public Boolean call() throws IOException, InterruptedException {
            this.status = true;
            while (true) {
                byte ack = 1;
                client.dos.writeByte(ack);
                int pageSize = client.dis.readInt();
                if (pageSize == -1) {
                    client.dos.writeByte(ack);
                    break;
                }
                byte[] buffer = new byte[pageSize];
                int off = 0;
                do {
                    off += client.dis.read(buffer, off, pageSize - off);
                } while (off < pageSize);

                ByteBuffer bb = ByteBuffer.allocate(pageSize).put(buffer);
                ArrayList<RootData> list = new ArrayList<>();
                int relativePosition = 0;
                do {
                    bb.position(relativePosition);
                    int objectSize = bb.getInt();
                    relativePosition += 4;
                    byte[] objectBuffer = new byte[objectSize];
                    bb.position(relativePosition);
                    bb.get(objectBuffer, 0, objectSize);
                    relativePosition += objectSize;
                    list.add(reader.readObjectWithSerialization(new TweetStatus(), objectBuffer));
                } while (relativePosition < pageSize);
                this.queue.put(list);
            }
            this.status = false;
            client.dos.close();
            client.dis.close();
            client.socket.close();
            return false;
        }
    }

    private static class LocalReadTask extends Task {
        protected final int nrow;

        public LocalReadTask(ObjectReader reader, int nrow) {
            super(reader);
            this.nrow = nrow;
        }

        @Override
        public Boolean call() throws IOException, InterruptedException {
            this.status = true;
            ArrayList<RootData> list = new ArrayList<>();
            this.reader.readObjects(0, this.nrow, list);
            Collections.sort(list);

            int chunks = (int) Math.ceil((double) nrow / Const.NETWORK_LOCAL_READ_LENGTH);

            for (int i = 0; i < chunks & i * Const.NETWORK_LOCAL_READ_LENGTH < nrow; i++) {
                ArrayList<RootData> tmpList = new ArrayList<>();
                for (int j = i * Const.NETWORK_LOCAL_READ_LENGTH; j < Math.min((i + 1) * Const.NETWORK_LOCAL_READ_LENGTH, nrow); j++) {
                    tmpList.add(list.get(j));
                }
                this.queue.put(tmpList);
            }
            this.status = false;
            return false;
        }
    }

    private static class Client {
        private final DataInputStream dis;
        private final DataOutputStream dos;
        private final Socket socket;

        public Client(Socket socket, DataOutputStream dos, DataInputStream dis) {
            this.dis = dis;
            this.dos = dos;
            this.socket = socket;
        }

        public DataInputStream getDis() {
            return dis;
        }

        public DataOutputStream getDos() {
            return dos;
        }

        public Socket getSocket() {
            return socket;
        }
    }

    private static class ObjectNetworkIndex implements Comparable<ObjectNetworkIndex> {
        private RootData myObject;
        private int clientIndex;

        public ObjectNetworkIndex(int clientIndex, RootData myObject) {
            this.myObject = myObject;
            this.clientIndex = clientIndex;
        }

        public RootData getValue() {
            return myObject;
        }

        public void setValue(RootData myObject) {
            this.myObject = myObject;
        }

        public int getClientIndex() {
            return clientIndex;
        }

        public void setClientIndex(int clientIndex) {
            this.clientIndex = clientIndex;
        }

        @Override
        public int compareTo(ObjectNetworkIndex o) {
            return this.myObject.compareTo(o.myObject);
        }
    }

    private static class ExternalSortTask extends Task {
        protected final ArrayList<Task> tasks;
        protected final ObjectWriter writer;
        protected final DataInputStream dis;
        protected final DataOutputStream dos;
        protected final boolean onDisk;
        protected final ArrayList<RootData> dataList;

        public ExternalSortTask(ArrayList<Task> tasks, ObjectWriter writer, boolean onDisk, DataInputStream dis, DataOutputStream dos) {
            super(null);
            this.tasks = tasks;
            this.writer = writer;
            this.onDisk = onDisk;
            this.dis = dis;
            this.dos = dos;
            if (writer == null)
                this.dataList = new ArrayList<>();
            else
                this.dataList = null;
        }

        @Override
        public Boolean call() throws InterruptedException {
            int numberOfClients = tasks.size();
            long[] pageObjectCounter = new long[numberOfClients];
            PriorityQueue<ObjectNetworkIndex> queue = new PriorityQueue<ObjectNetworkIndex>();

            // reading objects from the first pages and adding them to a priority queue
            for (int i = 0; i < numberOfClients; i++) {
                List<RootData> listReadFromFile = tasks.get(i).queue.take();
                pageObjectCounter[i] = listReadFromFile.size();
                for (RootData rd : listReadFromFile) {
                    ObjectNetworkIndex objectNetworkIndex = new ObjectNetworkIndex(i, rd);
                    queue.add(objectNetworkIndex);
                }
            }
            logger.info("Network External Sort: First page reading is done! ");

            while (!queue.isEmpty()) {
                ObjectNetworkIndex tmpObjectNetworkIndex = queue.remove();
                int clientNumber = tmpObjectNetworkIndex.getClientIndex();

                // reduce the number of objects read from that file.
                pageObjectCounter[clientNumber]--;

                // If needed load more objects from files.
                // if zero load the next page from file and add objects.
                if (pageObjectCounter[clientNumber] == 0) {
                    List<RootData> listReadFromFile = null;
                    if (!tasks.get(clientNumber).queue.isEmpty()) {
                        listReadFromFile = tasks.get(clientNumber).queue.take();
                    } else {
                        while (tasks.get(clientNumber).status && tasks.get(clientNumber).queue.isEmpty()) ;
                        if (!tasks.get(clientNumber).queue.isEmpty()) {
                            listReadFromFile = tasks.get(clientNumber).queue.take();
                        }
                    }
                    if (listReadFromFile != null) {
                        pageObjectCounter[clientNumber] = listReadFromFile.size();
                        for (RootData rd : listReadFromFile) {
                            ObjectNetworkIndex objectNetworkIndex = new ObjectNetworkIndex(clientNumber, rd);
                            queue.add(objectNetworkIndex);
                        }
                    }
                }
                if (writer !=null) {
                    if (onDisk) writer.writeObjectToFile(tmpObjectNetworkIndex.myObject);
                    else writer.writeObjectToNetworkPage(tmpObjectNetworkIndex.myObject, dos, dis);
                }
                else
                    this.dataList.add(tmpObjectNetworkIndex.myObject);
            }
            logger.info("Network External Sort: Done!");
            if (writer != null) {
                if (onDisk) writer.flush();
                else writer.flushToNetwork(dos, dis);
            }
            return null;
        }
    }
}
