
const PAGESIZE: u32 = 1024*1024;
const BATCHSIZE: u32 = 512;
const NETWORK_PAGESIZE: u64 = 20*1024*1024;
const NETWORK_LOCAL_READ_LENGTH: u32 = 20000;
const NETWORK_CLIENT_QUEUE_SIZE: u16 = 10;
const NETWORK_TIMEOUT: u32 = 2000*1000;

const JSON: u32 = 1;
const BINCODE: u32 = 2;
const MESSAGEOACK: u32 = 3;
const BSON: u32 = 4;
const FLEXBUF: u32 = 5;

// const auto NUM_THREADS = std::thread::hardware_concurrency();
//
// enum NodeType {  ROOT,  MIDDLE, LEAF };