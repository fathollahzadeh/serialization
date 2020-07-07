use std::collections::HashMap;
use bytes::BytesMut;

//#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct FileHandler {
     file_name:String,
     current_page_number:i64,
     current_offset:i64,
     page_buffer:BytesMut,

     //total number of objects in serialized file:
     total_of_objects:i64,

     //Output Stream: For Writing:
     //RandomAccessFile randOutStreamRegularFile;

     //Output Stream: For Index Writing:
     //BufferedOutputStream bosIndexFile;

     //Input Stream: For Reading:
     //FileChannel inStreamRegularFile;

     //Page index:
     page_index:Vec<i64>,

     //Object index:
     object_index:Vec<i64>,

     //Object Length:
     object_length:Vec<i64>,

     //Object in each page:
     object_in_each_page:HashMap<i64,i64>,

    //benchmark times:
    io_time:f64,
    index_time:f64,

    //Network Experiments:
    network_page_size:i64,

    serialization_type:i32,

    method:String

}

impl FileHandler{
    pub fn new(fileName: String, serializationType: i32) -> FileHandler {
        let mth;
        match serializationType {
            1=> mth="JSON",
            2 => mth = "Bincode",
            3 => mth = "CBOR",
            4 => mth = "YAML",
            5 => mth = "MessagePack",
            6 => mth = "TOML",
            7 => mth = "Pickle",
            8 => mth = "RON",
            9 => mth = "BSON",
            10 => mth = "Avro",
            11 => mth = "JSON5",
            12 => mth = "Postcard",
            13 => mth = "URL",
            14 => mth = "S-expressions",
            15 => mth = "D-Bus",
            16 => mth = "FlexBuffers",
            _ => {mth =""}
        }
        FileHandler {
            file_name:fileName,
            current_page_number: 0,
            current_offset: 0,
            page_buffer: BytesMut::with_capacity(2*256*1024), // page size = 256K
            total_of_objects: 0,
            page_index: vec![],
            object_index: vec![],
            object_length: vec![],
            object_in_each_page: Default::default(),
            io_time: 0.0,
            index_time: 0.0,
            network_page_size: 0,
            serialization_type:serializationType,
            method: String::from(mth)
        }
    }
}