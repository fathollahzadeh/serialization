package at.tugraz.networkadapter;

import at.tugraz.util.NodeType;
import at.tugraz.util.Pair;

import java.util.ArrayList;

public class MachineInfo {
    private final String ip;
    private final int port;
    private NodeType nodeType;
    private final ArrayList<Pair<String, Integer>> leaves;

    public MachineInfo(String ip, int port, ArrayList<Pair<String, Integer>> leaves) {
        this.ip = ip;
        this.port = port;
        this.leaves = leaves;
        if (leaves == null || leaves.size() == 0)
            this.nodeType = NodeType.LEAF;
        else
            this.nodeType = NodeType.MIDDLE;
    }

    public String getIp() {
        return ip;
    }

    public int getPort() {
        return port;
    }

    public NodeType getNodeType() {
        return nodeType;
    }

    public void setNodeType(NodeType nodeType) {
        this.nodeType = nodeType;
    }

    public ArrayList<Pair<String, Integer>> getLeaves() {
        return leaves;
    }
}
