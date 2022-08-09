package at.tugraz.networkadapter;

import org.apache.log4j.Logger;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.net.InetAddress;
import java.nio.charset.StandardCharsets;
import java.util.HashMap;
import java.util.Map;

public class Network {
    private Logger logger = Logger.getLogger(Network.class);
    private HashMap<String, MachineInfo> machineInfos;
    String config;

    public Network(String config) throws IOException {
        this.config = config;
        this.readConfigFile(config);
    }

    public void readConfigFile(String config) throws IOException {
        machineInfos = new HashMap<>();
        Map<String, String> rootLeaf = new HashMap<>();

        try (BufferedReader br = new BufferedReader(new FileReader(config, StandardCharsets.UTF_8))) {
            String line;
            br.readLine();
            while ((line = br.readLine()) != null) {
                String[] cols = line.split(",");
                String ip = cols[0];
                int port = Integer.parseInt(cols[1]);
                String root = cols[2];
                int nrow = Integer.parseInt(cols[3]);
                rootLeaf.put(ip, root);
                MachineInfo nsi = new MachineInfo(ip, port, nrow);
                machineInfos.put(ip, nsi);
            }
        }

        for (String ip: rootLeaf.keySet()){
            String root = rootLeaf.get(ip);
            if (root.equalsIgnoreCase("root"))
                continue;
            machineInfos.get(root).addLeaf(machineInfos.get(ip));
            machineInfos.get(ip).setRoot(machineInfos.get(root));
        }

        for (String ip: machineInfos.keySet()){
            int sumLeaf = computeNRow(machineInfos.get(ip)) - machineInfos.get(ip).getNrow();
            machineInfos.get(ip).setNrowLeaf(sumLeaf);
        }
    }

    public MachineInfo getCurrentMachine() {
        try {
            String ipstr;
            InetAddress ip;
            ip = InetAddress.getLocalHost();
            ipstr = ip.getHostAddress();
            return machineInfos.get(ipstr);

        } catch (Exception ignored) {
            logger.error("Get Current Machine IP:" + ignored);
        }
        throw new RuntimeException("The machine IP address is not in the config list");
    }

    private int computeNRow(MachineInfo node){
        if (node.getLeaves().size() == 0)
            return node.getNrow();
        else {
            int sum = node.getNrow();
            for (MachineInfo nsi: node.getLeaves())
                sum += computeNRow(nsi);
            return sum;
        }
    }
}
