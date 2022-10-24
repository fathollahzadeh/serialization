#![allow(non_snake_case)]
#![allow(dead_code)]
#![allow(unused_variables)]

extern crate num_cpus;
extern crate crossbeam;

use std::{io, env};
use std::cmp::min;
use std::fs::File;
use std::io::{BufRead, BufReader};
use crate::runtime::ObjectReader::ObjectReader;

mod tweetStructs;
mod runtime;
mod util;

fn main() -> io::Result<()> {
    let args: Vec<String> = env::args().collect();
    let inDataPath: String = args[1].to_string();
    let method: String = args[2].to_string();
    let seqRand: &str = args[3].as_str();
    let nrow: u32 = args[4].parse().unwrap();

    let NUM_THREADS: usize = num_cpus::get();
    let fv = nrow as f32 / NUM_THREADS as f32;
    let blklen = fv.ceil() as u32;

    if seqRand.to_lowercase().eq("sequential") {
        crossbeam::scope(|scope| {
            for i in 0..NUM_THREADS as u32 {
                let beginPos = i * blklen;
                let endPos = min((i + 1) * blklen, nrow);
                let inDataPath = inDataPath.clone();
                let method = method.clone();
                scope.spawn(move |_| {
                    let mut reader = ObjectReader::new1(inDataPath.as_str(), method.as_str());
                    reader.readIO(beginPos, endPos - beginPos + 1);
                    reader.flush();
                });
            }
        });
    } else {
        let randomDataPath: &str = args[5].as_str();
        let infile = File::open(randomDataPath)?;
        let f = BufReader::new(infile);
        let mut randomIDs: Vec<usize> = vec![];
        for line in f.lines() {
            randomIDs.push(line.ok().unwrap().parse::<usize>().unwrap());
        }
        crossbeam::scope(|scope| {
            let mut i = 0;
            while i < NUM_THREADS as u32 && i * blklen < nrow {
                let beginPos = i * blklen;
                let endPos = min((i + 1) * blklen, nrow);
                let inDataPath = inDataPath.clone();
                let method = method.clone();
                let randomIDs = randomIDs.clone();
                scope.spawn(move |_| {
                    let mut reader = ObjectReader::new1(inDataPath.as_str(), method.as_str());
                    for j in beginPos..endPos {
                        reader.readObjectIO(randomIDs[j as usize]);
                    }
                    reader.flush();
                });
                i += 1;
            }
        }).expect("Finished!");
    }
    Ok(())
}