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
use crate::NodeType::LEAF;
use crate::util::Const::NodeType;
use crate::util::ObjectFileIndex::ObjectFileIndex;
use crate::util::Network::Network;

mod tweetStructs;
mod runtime;
mod util;

fn main() -> io::Result<()> {
    let args: Vec<String> = env::args().collect();
    let inDataPath: &str = args[1].as_str();
    let outDataPath: &str = args[2].as_str();
    let method: &str = args[3].as_str();
    let config: String= args[4].to_string();
    let plan: &str = args[5].as_str();

    let mut network = Network::new(config);
    let mut machineInfo = network.getCurrentMachine();
    let mut reader = ObjectReader::new1(inDataPath, method);
    let mut mm = machineInfo.getNodeType();
    if mm == LEAF {

    }

    //MachineInfo machineInfo = network.getCurrentMachine();
    //         ObjectReader reader = new ObjectReader(inDataPath, method);
    //
    //         if (machineInfo.getNodeType() == NodeType.LEAF) {
    //             Client client = initClient(machineInfo.getRoot().getIp(), machineInfo.getPort());
    //             ArrayList<RootData> list = new ArrayList<>();
    //             reader.readObjects(0, machineInfo.getNrow(), list);
    //             Collections.sort(list);
    //
    //             ObjectWriter writer = new ObjectWriter(method, machineInfo.getTotalNRow(), Const.NETWORK_PAGESIZE);
    //             for (RootData rd : list)
    //                 writer.writeObjectToNetworkPage(rd, client.dos, client.dis);
    //
    //             writer.flushToNetwork(client.dos, client.dis);
    //             client.socket.close();
    //
    //         }


    Ok(())
}