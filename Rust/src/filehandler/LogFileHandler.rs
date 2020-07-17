
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
            3 => method = "Rust CBOR",
            4 => method = "Rust YAML",
            5 => method = "Rust MessagePack",
            6 => method = "Rust Pickle",
            7 => method = "Rust RON",
            8 => method = "Rust BSON",
            9 => method = "Rust JSON5",
            10 => method = "Rust FlexBuffers",
            _ => {method = ""}
        }

        let seqString;
        if !seq{
            seqString="false";
        }
        else {
            seqString="true";
        }

        log+= format!("{}#", method).as_ref();
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

//1-JSON, the ubiquitous JavaScript Object Notation used by many HTTP APIs.
//2- Bincode, a compact binary format used for IPC within the Servo rendering engine.
//3- CBOR, a Concise Binary Object Representation designed for small message size without the need for version negotiation.
//4- YAML, a self-proclaimed human-friendly configuration language that ain't markup language.
//5-MessagePack, an efficient binary format that resembles a compact JSON.
//6- TOML, a minimal configuration format used by Cargo.
//7- Pickle, a format common in the Python world.
//8- RON, a Rusty Object Notation.
//9- BSON, the data storage and network transfer format used by MongoDB.
//10- Avro, a binary format used within Apache Hadoop, with support for schema definition.
//11- JSON5, A superset of JSON including some productions from ES5.
//12- Postcard, a no_std and embedded-systems friendly compact binary format.
//13- URL, the x-www-form-urlencoded format.
//14- S-expressions, the textual representation of code and data used by the Lisp language family.
//15- D-Bus's binary wire format.
//16- FlexBuffers, the schemaless cousin of Google's FlatBuffers zero-copy serialization format.

