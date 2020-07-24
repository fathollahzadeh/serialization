use std::io::Write;
use std::fs::OpenOptions;
use std::time::{Duration};
use std::io;

pub struct LogFileHandler {
    file_name: String
}

impl LogFileHandler {
    pub fn new(file_name: String) -> LogFileHandler {
        LogFileHandler { file_name }
    }

    pub fn add_log(&self, read: bool, serialization_type: i32, seq: bool, datatype: String, iotime: Duration, totaltime: Duration, taskset: bool)-> io::Result<()> {
        let mut  log;
        if read {
            log = format!("{}{}{}","[ReadTimeRUST]#" , taskset , "#");
        } else {
            log = format!("{}{}{}","[WriteTimeRUST]#", taskset, "#");
        }
        let method;
        match serialization_type {
            1 => method = "Rust JSON",
            2 => method = "Rust Bincode",
            3 => method = "Rust MessagePack",
            4 => method = "Rust BSON",
            5 => method = "Rust FlexBuffers",
            _ => {method = ""}
        }

        let seqString;
        if !seq{
            seqString="false";
        }
        else {
            seqString="true";
        }

        log+=format!("{}#", method).as_ref();
        log+=format!("{}#",seqString).as_ref();
        log+=format!("{}#",datatype).as_ref();
        log+=format!("{:?}#",iotime.as_secs_f64()).as_ref();
        log+=format!("{:?}",totaltime.as_secs_f64()).as_ref();

        let mut file = OpenOptions::new()
            .create(true)
            .append(true)
            .open(&self.file_name).unwrap();

         if let Err(e) = writeln!(file, "{}",log.as_str() ) {
            eprintln!("Couldn't write to file: {}", e);
        }
        file.flush();
        Ok(())
    }
}