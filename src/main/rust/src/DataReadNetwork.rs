// use blockingqueue::BlockingQueue;
// use std::{thread, time};
//
// fn main() {
//     let bq = BlockingQueue::new();
//
//     let bq_clone1 = bq.clone();
//    let  t1 = thread::spawn(move || {
//        // thread::sleep(time::Duration::from_millis(100));
//         bq_clone1.push(1);
//         bq_clone1.push(1);
//         bq_clone1.push(1);
//     });
//
//     let bq_clone2 = bq.clone();
//     let t2= thread::spawn(move || {
//         //thread::sleep(time::Duration::from_millis(400));
//         bq_clone2.push(2);
//         bq_clone2.push(2);
//         bq_clone2.push(2);
//     });
//
//     t1.join();
//     t2.join();
//     let k = bq.clone();
//     for f in 0..6{
//         println!("{}", k.pop());
//     }


// let bq_clone3 = bq.clone();
// let read_three_thread = thread::spawn(move || {
//     for _ in 0..3 {
//         println!("Popped in child thread: {}", bq_clone3.pop());
//     }
// });
//
// for _ in 0..3 {
//     println!("Popped in parent thread: {}", bq.pop());
// }
//
// read_three_thread.join().unwrap();
//
// println!("I will wait forever here...");
// println!("{}", bq.pop());
//}



#![allow(non_snake_case)]
#![allow(dead_code)]
#![allow(unused_variables)]

use std::{io, env};
use std::borrow::Borrow;
use crate::runtime::ObjectReader::ObjectReader;
use crate::runtime::ObjectWriter::ObjectWriter;
use crate::tweetStructs::TweetStatus::TweetStatus;
use priority_queue::PriorityQueue;
use std::cmp::Reverse;
use crate::Const::NodeType;
use crate::util::Const;
use crate::util::ObjectFileIndex::ObjectFileIndex;
use crate::util::Network::Network;
////////////////////
use std::thread;
use std::net::{TcpListener, TcpStream, Shutdown};
use std::io::{Read, Write};
use std::str::from_utf8;
use blockingqueue::BlockingQueue;
use byteorder::ReadBytesExt;

mod tweetStructs;
mod runtime;
mod util;

fn main() -> io::Result<()> {
    let args: Vec<String> = env::args().collect();
    let inDataPath: &str = args[1].as_str();
    let outDataPath: &str = args[2].as_str();
    let method: &str = args[3].as_str();
    let config: String = args[4].to_string();
    let plan: &str = args[5].as_str();

    let mut network = Network::new(config);
    let mut machineInfo = network.getCurrentMachine();
    let mut reader = ObjectReader::new1(inDataPath, method);
    let mut nodeType = machineInfo.getNodeType();
    let mut queues: Vec<BlockingQueue<TweetStatus>> = vec![];

    if nodeType == NodeType::LEAF {
        match TcpStream::connect(format!("{}:{}", machineInfo.ip(), machineInfo.port())) {
            Ok(mut stream) => {
                let mut list: Vec<TweetStatus> = vec![];
                reader.readObjects(0, machineInfo.nrow(), &mut list);
                list.sort_by(|cu, ot| cu.getOrder().cmp(&ot.getOrder()));
                let mut writer = ObjectWriter::new2(method, machineInfo.nrow(), Const::NETWORK_PAGESIZE as usize);
                for rd in list {
                    writer.writeObjectToNetworkPage(rd, stream.try_clone().unwrap());
                }
            }
            Err(e) => {
                println!("Failed to connect: {}", e);
            }
        }
        println!("Terminated.");
    } else if nodeType == NodeType::MIDDLE {
        let serverSocket = TcpListener::bind(format!("{}:{}", machineInfo.ip(), machineInfo.port())).unwrap();

        for i in 0..machineInfo.leaves().len() {
            for stream in serverSocket.incoming() {
                match stream {
                    Ok(stream) => {
                        thread::spawn(move || {
                            NetworkReadTask(stream);
                            // connection succeeded
                            //handle_client(stream)
                        });
                    }
                    _ => {}
                }
            }
        }
    }

    Ok(())
}

fn NetworkReadTask(mut stream: TcpStream){
    let mut ack_data = [0 as u8; 1];
    let mut i32_data = [0 as u8; 4];
    let ack = b"1";


    while true {
        stream.write(&ack.clone());
        stream.read_exact(&mut i32_data).unwrap();
        let pageSize = i32::from_be_bytes(i32_data);

        // match stream.read_exact(&mut ack_data) {
        //     Ok(_) => {
        //         if &ack_data != ack {
        //             println!("NetworkReadTask!");
        //             return;
        //         }
        //         stream.write(&last_len.to_be_bytes());
        //         stream.write(tbuffer.bytes()).unwrap();
        //         last_len = 0;
        //     }
        //     _ => {
        //         println!("writeObjectToNetworkPage (pattern)!");
        //         return;
        //     }
        // }
    }
}
// public Boolean call() throws IOException, InterruptedException {
//             this.status = true;
//             while (true) {
//                 byte ack = 1;
//                 client.dos.writeByte(ack);
//                 int pageSize = client.dis.readInt();
//                 if (pageSize == -1) {
//                     //client.dos.writeByte(ack);
//                     break;
//                 }
//                 byte[] buffer = new byte[pageSize];
//                 int off = 0;
//                 do {
//                     off += client.dis.read(buffer, off, pageSize - off);
//                 } while (off < pageSize);
//
//                 ByteBuffer bb = ByteBuffer.allocate(pageSize).put(buffer);
//                 ArrayList<RootData> list = new ArrayList<>();
//                 int relativePosition = 0;
//                 do {
//                     bb.position(relativePosition);
//                     int objectSize = bb.getInt();
//                     relativePosition += 4;
//                     byte[] objectBuffer = new byte[objectSize];
//                     bb.position(relativePosition);
//                     bb.get(objectBuffer, 0, objectSize);
//                     relativePosition += objectSize;
//                     list.add(reader.readObjectWithSerialization(new TweetStatus(), objectBuffer));
//                 } while (relativePosition < pageSize);
//                 this.queue.put(list);
//             }
//             this.status = false;
//             return false;
//         }

//else if (machineInfo.getNodeType() == NodeType.MIDDLE) {
//             ServerSocket serverSocket = new ServerSocket(machineInfo.getPort());
//             serverSocket.setSoTimeout(Const.NETWORK_TIMEOUT);
//             Client client = initClient(machineInfo.getRoot().getIp(), machineInfo.getPort());
//
//             ArrayList<Task> tasks = new ArrayList<>();
//             ArrayList<Task> dataTasks = new ArrayList<>();
//             ArrayList<Client> clients = new ArrayList<>();
//             ExecutorService pool = CommonThreadPool.get(machineInfo.getLeaves().size() + 3);
//             Socket socket;
//
//             for (int i = 0; i < machineInfo.getLeaves().size(); i++) {
//                 socket = serverSocket.accept();
//                 Client cli = new Client(socket, new DataOutputStream(socket.getOutputStream()), new DataInputStream(socket.getInputStream()));
//                 ObjectReader clientReader = new ObjectReader(method);
//                 NetworkReadTask clientTask = new NetworkReadTask(cli, clientReader);
//                 tasks.add(clientTask);
//                 dataTasks.add(clientTask);
//                 clients.add(cli);
//             }
//
//             // read objects from local
//             Task clientTask = new LocalReadTask(reader, machineInfo.getNrow());
//             tasks.add(clientTask);
//             dataTasks.add(clientTask);
//
//             ObjectWriter writer = new ObjectWriter(method, machineInfo.getTotalNRow(), Const.NETWORK_PAGESIZE);
//             // add external sort task
//             tasks.add(new ExternalSortTask(dataTasks, writer, false, client.dis, client.dos));
//
//             // invoke all tasks
//             List<Future<Boolean>> rt = pool.invokeAll(tasks);
//             pool.shutdown();
//
//             //check for exceptions
//             for (Future<Boolean> f : rt) {
//                 f.get();
//             }
//
//             // terminate all sockets
//             byte ack = 1;
//             for (Client c: clients){
//                 c.dos.writeByte(ack);
//                 c.dos.close();
//                 c.dis.close();
//                 c.socket.close();
//             }
//
//         }