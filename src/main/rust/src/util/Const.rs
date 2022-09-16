pub const PAGESIZE: u32 = 1024*1024;
pub const BATCHSIZE: u32 = 512;
pub const NETWORK_PAGESIZE: u64 = 20*1024*1024;
pub const NETWORK_LOCAL_READ_LENGTH: u32 = 20000;
pub const NETWORK_CLIENT_QUEUE_SIZE: u16 = 10;
pub const NETWORK_TIMEOUT: u32 = 2000*1000;

pub const JSON: u16 = 1;
pub const BINCODE: u16 = 2;
pub const MESSAGEPACK: u16 = 3;
pub const BSON: u16 = 4;
pub const FLEXBUF: u16 = 5;

pub fn getMethodID( method: &str) -> u16 {
    let methodID: u16;
    match method {
        "Json" => methodID = JSON,
        "Bincode" => methodID = BINCODE,
        "MessagePack" => methodID = MESSAGEPACK,
        "Bson" => methodID = BSON,
        "FlexBuf" => methodID = FLEXBUF,
        _ => { methodID = 0 }
    }
    return methodID;
}
// enum NodeType {  ROOT,  MIDDLE, LEAF };