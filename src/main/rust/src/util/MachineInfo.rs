use crate::util::Const::NodeType;

#[derive(Debug)]
pub struct MachineInfo {
    ip: String,
    port: u16,
    root: String,
    nrow: u32,
    nrowLeaf: u32,
    leaves: Vec<String>,
}

impl MachineInfo {
    pub fn new(ip: String, port: u16, root: String, nrow: u32) -> Self {
        Self {
            ip: ip,
            port: port,
            root: root,
            nrow: nrow,
            nrowLeaf: 0,
            leaves: vec![],
        }
    }
    pub fn addLeaf(&mut self, leaf: String) {
        self.leaves.push(leaf);
    }

    pub fn getNodeType(&mut self) -> NodeType {
        if self.root == "root" {
            return NodeType::ROOT;
        } else if self.leaves.len() == 0 {
            return NodeType::LEAF;
        } else {
            return NodeType::MIDDLE;
        }
    }


    pub fn ip(&self) -> &str {
        &self.ip
    }
    pub fn port(&self) -> u16 {
        self.port
    }
    pub fn root(&self) -> &str {
        &self.root
    }
    pub fn nrow(&self) -> u32 {
        self.nrow
    }
    pub fn nrowLeaf(&self) -> u32 {
        self.nrowLeaf
    }
    pub fn leaves(&self) -> &Vec<String> {
        &self.leaves
    }

    pub fn set_ip(&mut self, ip: String) {
        self.ip = ip;
    }
    pub fn set_port(&mut self, port: u16) {
        self.port = port;
    }
    pub fn set_root(&mut self, root: String) {
        self.root = root;
    }
    pub fn set_nrow(&mut self, nrow: u32) {
        self.nrow = nrow;
    }
    pub fn set_nrowLeaf(&mut self, nrowLeaf: u32) {
        self.nrowLeaf = nrowLeaf;
    }
    pub fn set_leaves(&mut self, leaves: Vec<String>) {
        self.leaves = leaves;
    }
}