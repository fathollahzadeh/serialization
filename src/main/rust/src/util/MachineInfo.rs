use crate::util::Const::NodeType;

#[derive(Clone)]
pub struct MachineInfo {
    ip: String,
    port:u16,
    root:Option<Box<MachineInfo>>,
    nrow:u32,
    nrowLeaf:u32,
    leaves:Vec<MachineInfo>
}

impl MachineInfo {
    pub fn new(ip:String, port:u16, nrow:u32)-> Self{
        Self{
            ip: ip,
            port:port,
            root: None,
            nrow:nrow,
            nrowLeaf: 0,
            leaves: vec![]
        }
    }

    pub fn ip(&self) -> &str {
        &self.ip
    }
    pub fn port(&self) -> u16 {
        self.port
    }

    pub fn nrow(&self) -> u32 {
        self.nrow
    }
    pub fn nrowLeaf(&self) -> u32 {
        self.nrowLeaf
    }


    pub fn set_ip(&mut self, ip: String) {
        self.ip = ip;
    }
    pub fn set_port(&mut self, port: u16) {
        self.port = port;
    }

    pub fn set_nrow(&mut self, nrow: u32) {
        self.nrow = nrow;
    }
    pub fn set_nrowLeaf(&mut self, nrowLeaf: u32) {
        self.nrowLeaf = nrowLeaf;
    }

    pub fn root(&self) -> &Option<Box<MachineInfo>> {
        &self.root
    }

    // pub fn set_root(&mut self, root: MachineInfo) {
    //     self.root = Box(root, ());
    // }

    pub fn addLeaf(&mut self, leaf: MachineInfo){
          self.leaves.push(leaf);
    }
    pub fn getNodeType(&mut self) -> NodeType{
        // if self.root == None {
        //     return NodeType::ROOT;
        // }
        // else if self.leaves.len() == 0 {
        //     return NodeType::LEAF;
        // }
        // else {
        //     return NodeType::MIDDLE;
        // }
        return NodeType::MIDDLE;
    }


}