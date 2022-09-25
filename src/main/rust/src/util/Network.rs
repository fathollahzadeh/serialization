use std::borrow::{Borrow, BorrowMut};
use std::collections::HashMap;
use crate::util::MachineInfo::MachineInfo;
use std::error::Error;
use std::io;
use std::process;
use csv;
use csv::Reader;
use local_ip_address::local_ip;

pub struct Network {
    config: String,
    machineInfo: HashMap<String, MachineInfo>,
}

impl Network {
    pub fn new(config: String) -> Self {
        let list = Network::readConfigFile(config.clone());
        Self {
            config: config,
            machineInfo: list,
        }
    }

    fn readConfigFile(config: String) -> HashMap<String, MachineInfo> { //-> HashMap<String, MachineInfo>
        let mut list: HashMap<String, MachineInfo> = HashMap::new();
        let mut rootLeaf: HashMap<String, String> = HashMap::new();

        let mut br = csv::Reader::from_path(config.clone()).unwrap();
        for line in br.records() {
            let record = line.unwrap();
            let ip = record.get(0).unwrap().to_string();
            let port: u16 = record.get(1).unwrap().parse().unwrap();
            let root = record.get(2).unwrap().to_string();
            let nrow: u32 = record.get(3).unwrap().parse().unwrap();
            rootLeaf.insert(ip.clone(), root.clone());

            let nsi = MachineInfo::new(ip.clone(), port, root, nrow);
            list.insert(ip, nsi);

        }

        for ip in rootLeaf.keys() {
            let root = rootLeaf.get(ip.clone().as_str()).unwrap();
            if root.to_lowercase().eq("root") {
                continue;
            }
            list.get_mut(root.clone().as_str()).unwrap().addLeaf(ip.clone());
            list.get_mut(ip.clone().as_str()).unwrap().set_root(root.clone());
        }

        for ip in rootLeaf.keys() {
            let sumLeaf = Network::computeNRow(&list, ip);
            list.get_mut(ip).unwrap().set_nrowLeaf(sumLeaf);
        }
        return list;
    }

    fn computeNRow(list: &HashMap<String, MachineInfo>, node: &str) -> u32 {
        let tmp = list.get(node).borrow().unwrap();
        if tmp.leaves().len() == 0 {
            return tmp.nrow();
        } else {
            let mut sum = tmp.nrow();
            for leaf in tmp.leaves() {
                sum += Network::computeNRow(list.borrow(), leaf);
            }
            return sum;
        }
    }

    pub fn getCurrentMachine(&mut self) -> &mut MachineInfo {
        let ipstr = local_ip().unwrap().to_string();
        return self.machineInfo.get_mut(ipstr.as_str()).unwrap();
    }
}