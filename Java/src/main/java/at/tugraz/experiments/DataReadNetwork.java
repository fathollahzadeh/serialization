package at.tugraz.experiments;

import at.tugraz.networkadapter.MachineInfo;
import at.tugraz.networkadapter.Network;
import at.tugraz.runtime.ObjectReader;
import at.tugraz.runtime.ObjectWriter;
import at.tugraz.tweet.TweetStatus;
import at.tugraz.util.CommonThreadPool;
import at.tugraz.util.Const;
import at.tugraz.util.NodeType;
import at.tugraz.util.Pair;
import at.tugraz.util.RootData;
import org.apache.log4j.Logger;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Date;
import java.util.List;
import java.util.PriorityQueue;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;

public class DataReadNetwork {

    private static Logger logger = Logger.getLogger(DataReadNetwork.class);
    private static SimpleDateFormat formatter = new SimpleDateFormat("dd/MM/yyyy HH:mm:ss");

    public static void main(String[] args) throws IOException, InterruptedException, ExecutionException {

        String inDataPath = System.getProperty("inDataPath");
        String method = System.getProperty("method");
        String config = System.getProperty("config");
        int nrow = Integer.parseInt(System.getProperty("nrow"));


        Network network = new Network(config);
        MachineInfo machineInfo = network.getCurrentMachine();

        ObjectReader reader = new ObjectReader(inDataPath, "Kryo");
        int size = Const.BATCHSIZE;
        ArrayList<RootData> list = new ArrayList<>();
        for (long i = 0; i < nrow; ) {
            int l = (int) reader.readObjects(i, size, list);
            i += l;
            size = (int) Math.min(nrow - i, Const.BATCHSIZE);
        }
        Collections.sort(list);

        DataInputStream dis;
        DataOutputStream dos;

        if (machineInfo.getNodeType() == NodeType.LEAF) {
            ObjectWriter writer = new ObjectWriter(method, nrow, Const.NETWORK_PAGESIZE);
            Pair<DataInputStream, DataOutputStream> pair = initServer(machineInfo);
            if (pair == null) throw new IOException("The server:" + machineInfo.getIp() + " as Leaf Node can't start!");

            dis = pair.getKey();
            dos = pair.getValue();
            for (RootData rd : list)
                writer.writeObjectToNetworkPage(rd, dos, dis);

            writer.flushToNetwork(dos, dis);

        } else if (machineInfo.getNodeType() == NodeType.MIDDLE) {
            ObjectWriter writer = new ObjectWriter(method, nrow, Const.NETWORK_PAGESIZE);
            Pair<DataInputStream, DataOutputStream> pair = initServer(machineInfo);
            if (pair == null) throw new IOException("The server:" + machineInfo.getIp() + " as Middle Node can't start!");
            dis = pair.getKey();
            dos = pair.getValue();

            ArrayList<Pair<String, Integer>> leaves = machineInfo.getLeaves();
            ArrayList<NetworkReadTask> tasks = new ArrayList<>();
            ExecutorService pool = CommonThreadPool.get(leaves.size());

            for (Pair<String, Integer> p : leaves) {
                ObjectReader clientReader = new ObjectReader(method);
                Client client = initClient(p.getKey(), p.getValue());
                tasks.add(new NetworkReadTask(client, clientReader));
            }
            pool.invokeAll(tasks);
            runTheExternalSort(tasks, writer, false, dis, dos);
        }
        else if (machineInfo.getNodeType() == NodeType.ROOT){
            String outDataPath = System.getProperty("outDataPath");
            ObjectWriter writer = new ObjectWriter(outDataPath, method, nrow);
            ArrayList<Pair<String, Integer>> leaves = machineInfo.getLeaves();
            ArrayList<NetworkReadTask> tasks = new ArrayList<>();
            ExecutorService pool = CommonThreadPool.get(leaves.size());

            for (Pair<String, Integer> p : leaves) {
                ObjectReader clientReader = new ObjectReader(method);
                Client client = initClient(p.getKey(), p.getValue());
                tasks.add(new NetworkReadTask(client, clientReader));
            }
            pool.invokeAll(tasks);
            runTheExternalSort(tasks, writer, true, null, null);
        }
    }

    private static Pair<DataInputStream, DataOutputStream> initServer(MachineInfo machineInfo) throws IOException {
        ServerSocket server = new ServerSocket(machineInfo.getPort());
        logger.trace(machineInfo.getNodeType() + " >> " + machineInfo.getIp() + ":" + machineInfo.getPort() + "  Server Started!");
        server.setSoTimeout(20 * 1000);
        Socket socket = server.accept();
        logger.trace(machineInfo.getNodeType() + " >> " + machineInfo.getIp() + ":" + machineInfo.getPort() + "  Server Accepted!");

        DataInputStream dis = new DataInputStream(socket.getInputStream());
        DataOutputStream dos = new DataOutputStream(socket.getOutputStream());

        // read an Int message for start
        byte startACK = dis.readByte();
        Date date = new Date();
        if (startACK == 1) {
            logger.trace("LEAF >> " + machineInfo.getIp() + ":" + machineInfo.getPort() + "  Received Start ACK << 1 >> at: " + formatter.format(date));
        } else {
            logger.trace("LEAF >> " + machineInfo.getIp() + ":" + machineInfo.getPort() + "  Received Wrong Start ACK " + startACK + " at: " + formatter.format(date));
            return null;
        }

        Pair<DataInputStream, DataOutputStream> result = new Pair<>(dis, dos);
        return result;
    }

    private static Client initClient(String ip, int port) {
        try {
            Socket socket = new Socket(ip, port);
            Client client = new Client(socket, new DataOutputStream(socket.getOutputStream()), new DataInputStream(socket.getInputStream()));
            return client;
        } catch (Exception ignored) {
            throw new RuntimeException("Client can't start >> " + ip + ":" + port);
        }
    }

    private static class NetworkReadTask implements Callable<Boolean> {
        protected final Client client;
        protected final ObjectReader reader;
        protected final BlockingQueue<ArrayList<RootData>> queue;
        protected boolean status;

        public NetworkReadTask(Client client, ObjectReader reader) {
            this.client = client;
            this.reader = reader;
            this.queue = new ArrayBlockingQueue<>(10);
        }

        @Override
        public Boolean call() throws IOException {
            this.status = true;
            while (true) {
                byte ack = 1;
                client.dos.writeByte(ack);

                int pageSize = client.dis.readInt();
                if (pageSize == -1) {
                    client.dos.close();
                    client.dis.close();
                    client.socket.close();
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
                    bb.get(objectBuffer, relativePosition, objectSize);
                    relativePosition += objectSize;
                    list.add(reader.readObjectWithSerialization(new TweetStatus(), objectBuffer));

                } while (relativePosition < pageSize);
                this.queue.add(list);
            }
            this.status = false;
            return null;
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

    private static  void runTheExternalSort(ArrayList<NetworkReadTask> tasks, ObjectWriter writer, boolean onDisk, DataInputStream dis, DataOutputStream dos) throws InterruptedException {
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
        logger.trace("Network External Sort: First page reading is done! ");

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
            if (onDisk)
                writer.writeObjectToFile(tmpObjectNetworkIndex.myObject);
            else
                writer.writeObjectToNetworkPage(tmpObjectNetworkIndex.myObject, dos, dis);
        }
        logger.trace("Network External Sort: Done!");
        if (onDisk)
            writer.flush();
        else
            writer.flushToNetwork(dos, dis);
    }
}
