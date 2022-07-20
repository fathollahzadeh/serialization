package at.tugraz.networkadapter;

import at.tugraz.util.NodeType;
import at.tugraz.util.Pair;
import org.apache.log4j.Logger;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.net.InetAddress;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.HashMap;

public class Network {
    private Logger logger = Logger.getLogger(Network.class);
    private HashMap<String, MachineInfo> machineInfos;
    String config;

    public Network(String config) throws IOException {
        this.config = config;
        this.readConfigFile(config);
    }

    public void readConfigFile(String config) throws IOException {
        HashMap<String, ArrayList<Pair<String,Integer>>> middleNodes = new HashMap<>();
        HashMap<String, Integer> nodes = new HashMap<>();
        // IP, PORT, ROOT
        try (BufferedReader br = new BufferedReader(new FileReader(config, StandardCharsets.UTF_8))) {
            String line;
            br.readLine();
            while ((line = br.readLine()) != null) {
                String[] cols = line.split(",");
                String ip = cols[0];
                int port = Integer.parseInt(cols[1]);
                String root = cols[2];

                Pair<String, Integer> newNode = new Pair<>(ip, port);
                if (!middleNodes.containsKey(root))
                    middleNodes.put(root, new ArrayList<>());
                middleNodes.get(root).add(newNode);

                nodes.put(ip, port);
            }
        }

        this.machineInfos = new HashMap<>();
        for (String ip: nodes.keySet()){
            MachineInfo machineInfo = new MachineInfo(ip,nodes.get(ip), middleNodes.get(ip));
            if (ip.equalsIgnoreCase("root"))
                machineInfo.setNodeType(NodeType.ROOT);
            this.machineInfos.put(ip, machineInfo);
        }

    }

    public MachineInfo getCurrentMachine(){
        try {
            String ipstr;
            InetAddress ip;
            ip = InetAddress.getLocalHost();
            ipstr = ip.getHostAddress();
            return machineInfos.get(ipstr);

        }
        catch (Exception ignored) {
            logger.error("Get Current Machine IP:"+ignored);
        }
        throw new RuntimeException("The machine IP address is not in the config list");
    }
}
