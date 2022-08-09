package at.tugraz.networkadapter;

import at.tugraz.util.NodeType;

import java.util.ArrayList;

public class MachineInfo {
    private String ip;
    private int port;
    private MachineInfo root;
    private int nrow;
    private int nrowLeaf;
    private ArrayList<MachineInfo> leaves;

    public MachineInfo(String ip, int port, int nrow) {
        this.leaves = new ArrayList<>();
        this.ip = ip;
        this.port = port;
        this.nrow = nrow;
        this.nrowLeaf = 0;
    }

    public String getIp() {
        return ip;
    }

    public void setIp(String ip) {
        this.ip = ip;
    }

    public int getPort() {
        return port;
    }

    public void setPort(int port) {
        this.port = port;
    }

    public int getNrow() {
        return nrow;
    }

    public void setNrow(int nrow) {
        this.nrow = nrow;
    }

    public int getNrowLeaf() {
        return nrowLeaf;
    }

    public void setNrowLeaf(int nrowLeaf) {
        this.nrowLeaf = nrowLeaf;
    }

    public void addLeaf(MachineInfo leaf){
        this.leaves.add(leaf);
    }

    public void setRoot(MachineInfo root) {
        this.root = root;
    }

    public MachineInfo getRoot() {
        return root;
    }

    public ArrayList<MachineInfo> getLeaves() {
        return leaves;
    }

    public void setLeaves(ArrayList<MachineInfo> leaves) {
        this.leaves = leaves;
    }

    public NodeType getNodeType() {
        if (root == null)
            return NodeType.ROOT;
        else if (leaves.size() == 0)
            return NodeType.LEAF;
        else
            return NodeType.MIDDLE;
    }

    public int getTotalNRow(){
        return nrow + nrowLeaf;
    }
}
