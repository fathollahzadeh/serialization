use std::borrow::Borrow;
use std::collections::HashMap;
use crate::util::MachineInfo::MachineInfo;
use std::error::Error;
use std::io;
use std::process;
use csv;
use csv::Reader;

pub struct Network {
    config: String,
    objectInEachPage: HashMap<String, MachineInfo>
}

impl Network {
    pub fn new(config: String) -> Self{
        Network::readConfigFile(config.clone());
        Self{
            config: config,
            objectInEachPage: Default::default()
        }
    }

    fn readConfigFile(config: String) -> io::Result<()> { //-> HashMap<String, MachineInfo>
        let mut result: HashMap<String, MachineInfo> = HashMap::new();
        let mut rootLeaf: HashMap<String, String> = HashMap::new();

        let mut br = csv::Reader::from_path(config.clone())?;
         for line in br.records() {
             let record = line?;
             let ip = record.get(0).unwrap().to_string();
             let port:u16 = record.get(1).unwrap().parse().unwrap();
             let root = record.get(2).unwrap().to_string();
             let nrow:u32 = record.get(3).unwrap().parse().unwrap();

             rootLeaf.insert(ip.clone(), root);
             let nsi= MachineInfo::new(ip.clone(), port, nrow);
             result.insert(ip, nsi);
         }

        for ip in rootLeaf.keys() {
            let root = rootLeaf.get(ip.clone().as_str()).unwrap();
            if root.to_lowercase().eq("root") {
                continue;
            }
            let mut tmpRoot = result.get(root.clone().as_str()).unwrap();
            let mut tmpLeaf = result.get(ip.clone().as_str()).unwrap();

            tmpRoot.addLeaf(tmpLeaf.to_owned());
            tmpLeaf.set_root(tmpRoot);
            tmp.set_root()
        }
        Ok(())
    }
}
//  public void readConfigFile(String config) throws IOException {

//
//         for (String ip: rootLeaf.keySet()){
//             String root = rootLeaf.get(ip);
//             if (root.equalsIgnoreCase("root"))
//                 continue;
//             machineInfos.get(root).addLeaf(machineInfos.get(ip));
//             machineInfos.get(ip).setRoot(machineInfos.get(root));
//         }
//
//         for (String ip: machineInfos.keySet()){
//             int sumLeaf = computeNRow(machineInfos.get(ip)) - machineInfos.get(ip).getNrow();
//             machineInfos.get(ip).setNrowLeaf(sumLeaf);
//         }
//     }

//public Network(String config) throws IOException {
//         this.config = config;
//         this.readConfigFile(config);
//     }