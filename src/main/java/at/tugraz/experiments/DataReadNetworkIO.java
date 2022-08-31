package at.tugraz.experiments;

import at.tugraz.runtime.ObjectReader;
import at.tugraz.runtime.ObjectWriter;
import at.tugraz.tweet.TweetStatus;
import at.tugraz.util.CommonThreadPool;
import at.tugraz.util.Const;
import at.tugraz.util.MachineInfo;
import at.tugraz.util.Network;
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

public class DataReadNetworkIO {

    private static Logger logger = Logger.getLogger(DataReadNetworkIO.class);
    private static int QUEUE_SIZE = (int) Math.ceil(Const.NETWORK_CLIENT_QUEUE_SIZE * ((double) Const.PAGESIZE / Const.NETWORK_PAGESIZE));

    public static void main(String[] args) throws IOException, InterruptedException, ExecutionException {

        String inDataPath = System.getProperty("inDataPath");
        String method = System.getProperty("method");
        String config = System.getProperty("config");
        String plan = System.getProperty("plan");

        Network network = new Network(config);
        MachineInfo machineInfo = network.getCurrentMachine();
        ObjectReader reader = new ObjectReader(inDataPath, method);


        if (machineInfo.getNodeType() == NodeType.LEAF) {
            Client client = initClient(machineInfo.getRoot().getIp(), machineInfo.getPort());
            ArrayList<byte[]> pages = reader.readAllPages();

            ObjectWriter writer = new ObjectWriter(method, machineInfo.getTotalNRow(), Const.NETWORK_PAGESIZE);
            for (byte[] bb : pages) {
                writer.writeToNetworkPage(bb, client.dos, client.dis);
            }

            byte ack = client.dis.readByte();
            if (ack != 1) {
                throw new RuntimeException("writeObjectToNetworkPage " + ack);
            }
            client.dos.writeInt(-1);
            ack = client.dis.readByte();
            if (ack != 1) {
                throw new RuntimeException("LEAF read final network page " + ack);
            }
            client.dos.close();
            client.dis.close();
            client.socket.close();

        } else if (machineInfo.getNodeType() == NodeType.MIDDLE) {
            ServerSocket serverSocket = new ServerSocket(machineInfo.getPort());
            serverSocket.setSoTimeout(Const.NETWORK_TIMEOUT);
            Client client = initClient(machineInfo.getRoot().getIp(), machineInfo.getPort());

            ArrayList<Task> tasks = new ArrayList<>();
            ArrayList<Task> dataTasks = new ArrayList<>();
            ArrayList<Client> clients = new ArrayList<>();
            ExecutorService pool = CommonThreadPool.get(machineInfo.getLeaves().size() + 3);
            Socket socket;

            for (int i = 0; i < machineInfo.getLeaves().size(); i++) {
                socket = serverSocket.accept();
                Client cli = new Client(socket, new DataOutputStream(socket.getOutputStream()), new DataInputStream(socket.getInputStream()));
                ObjectReader clientReader = new ObjectReader(method);
                NetworkReadTask clientTask = new NetworkReadTask(cli, clientReader);
                tasks.add(clientTask);
                dataTasks.add(clientTask);
                clients.add(cli);
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

            // terminate all sockets
            byte ack = 1;
            for (Client c : clients) {
                c.dos.writeByte(ack);
                c.dos.close();
                c.dis.close();
                c.socket.close();
            }

        } else if (machineInfo.getNodeType() == NodeType.ROOT) {
            String outDataPath = System.getProperty("outDataPath");
            ObjectWriter writer = new ObjectWriter(outDataPath, method, machineInfo.getTotalNRow());
            ServerSocket serverSocket = new ServerSocket(machineInfo.getPort());
            serverSocket.setSoTimeout(Const.NETWORK_TIMEOUT);

            ArrayList<Task> tasks = new ArrayList<>();
            ArrayList<Task> dataTasks = new ArrayList<>();
            ArrayList<Client> clients = new ArrayList<>();
            ExecutorService pool = CommonThreadPool.get(machineInfo.getLeaves().size() + 3);
            Socket socket;
            for (int i = 0; i < machineInfo.getLeaves().size(); i++) {
                socket = serverSocket.accept();
                Client cli = new Client(socket, new DataOutputStream(socket.getOutputStream()), new DataInputStream(socket.getInputStream()));
                ObjectReader clientReader = new ObjectReader(method);
                NetworkReadTask clientTask = new NetworkReadTask(cli, clientReader);
                tasks.add(clientTask);
                dataTasks.add(clientTask);
                clients.add(cli);
            }
            System.out.println("SSSSSSSSSSSSSSSSSSSSSSSSSSSSS");
            // read objects from local
            Task clientTask = new LocalReadTask(reader, machineInfo.getNrow());
            tasks.add(clientTask);
            dataTasks.add(clientTask);

            // add external sort task
            if (plan.equalsIgnoreCase("d2d") || plan.equalsIgnoreCase("m2d"))
                tasks.add(new ExternalSortTask(dataTasks, writer, true, null, null));
            else tasks.add(new ExternalSortTask(dataTasks, null, true, null, null));

            List<Future<Boolean>> rt = pool.invokeAll(tasks);
            pool.shutdown();

            //check for exceptions
            for (Future<Boolean> f : rt) {
                f.get();
            }

            // terminate all sockets
            byte ack = 1;
            for (Client c : clients) {
                c.dos.writeByte(ack);
                c.dos.close();
                c.dis.close();
                c.socket.close();
            }
        }
    }

    private static Client initClient(String ip, int port) throws InterruptedException {
        boolean flag = false;
        Socket socket;
        Client client = null;
        for (int i = 0; i < 1000 && !flag; i++) {
            try {
                socket = new Socket(ip, port);
                socket.setSoTimeout(Const.NETWORK_TIMEOUT);
                client = new Client(socket, new DataOutputStream(socket.getOutputStream()), new DataInputStream(socket.getInputStream()));
                flag = socket.isConnected();
            } catch (Exception ignored) {
            }
            TimeUnit.SECONDS.sleep(1);
        }
        if (!flag) throw new RuntimeException("Client can't start >> " + ip + ":" + port);
        else {
            return client;
        }
    }

    private static abstract class Task implements Callable<Boolean> {
        protected final ObjectReader reader;
        protected final BlockingQueue<byte[]> queue;
        protected boolean status;

        public Task(ObjectReader reader) {
            this.reader = reader;
            this.queue = new ArrayBlockingQueue<>(QUEUE_SIZE);
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

                byte[] pageSizeBytes = new byte[4];
                client.dis.read(pageSizeBytes);
                int pageSize = ByteBuffer.wrap(pageSizeBytes).getInt();
                if (pageSize == -1) {
                    //client.dos.writeByte(ack);
                    break;
                }
                System.out.println("NetworkReadTask>>>>>>>>>>> "+ pageSize);
                byte[] buffer = new byte[pageSize+4];
                buffer[0] = pageSizeBytes[0];
                buffer[1] = pageSizeBytes[1];
                buffer[2] = pageSizeBytes[2];
                buffer[3] = pageSizeBytes[3];
                int off = 4;
                do {
                    off += client.dis.read(buffer, off, pageSize + 4 - off);
                    System.out.println("+++++ "+ off);
                } while (off < pageSize+3);
                System.out.println("RRRRRRRRRRRRRR");
                this.queue.put(buffer);
            }
            this.status = false;
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
            ArrayList<byte[]> pages = reader.readAllPages();
            for (byte[] bb : pages) {
                this.queue.put(bb);
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


    private static class ExternalSortTask extends Task {
        protected final ArrayList<Task> tasks;
        protected final ObjectWriter writer;
        protected final DataInputStream dis;
        protected final DataOutputStream dos;
        protected final boolean onDisk;

        public ExternalSortTask(ArrayList<Task> tasks, ObjectWriter writer, boolean onDisk, DataInputStream dis, DataOutputStream dos) {
            super(null);
            this.tasks = tasks;
            this.writer = writer;
            this.onDisk = onDisk;
            this.dis = dis;
            this.dos = dos;
        }

        @Override
        public Boolean call() throws InterruptedException {
            int numberOfClients = tasks.size();
            boolean flag;
            do {
                flag = false;
                for (int i = 0; i < numberOfClients; i++) {
                    System.out.println("waiting");
                    while (tasks.get(i).status && tasks.get(i).queue.isEmpty());
                    System.out.println("release");
                    if (!tasks.get(i).queue.isEmpty()) {
                        byte[] bb = tasks.get(i).queue.take();
                        if (writer != null) {
                            if (onDisk) writer.writeNetworkPageToFile(bb);
                            else writer.writeToNetworkPage(bb, dos, dis);
                        }
                        flag = true;
                        System.out.println("FFFFFFFFFFFFFFFFFFFFFFFFFFF");
                    }
                }
            } while (flag);

            logger.info("Network External Sort Transfer: Done!");
            if (writer != null) {
                if (onDisk) writer.flushNetworkPageWriter();
                else {
                    try {
                        byte ack = dis.readByte();
                        if (ack != 1) {
                            throw new RuntimeException("External Sort Transfer: flushToNetwork " + ack);
                        }
                        dos.writeInt(-1);
                        ack = dis.readByte();
                        if (ack != 1) {
                            throw new RuntimeException("External Sort Transfer: flushToNetwork final ACK " + ack);
                        }
                    } catch (Exception ex) {
                        throw new RuntimeException("Network External Sort:", ex);
                    }
                }
            }
            return null;
        }
    }
}
