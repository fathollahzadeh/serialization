#![allow(non_snake_case)]
#![allow(dead_code)]
#![allow(unused_variables)]

extern crate num_cpus;
extern crate crossbeam;

use std::{io, env};
use std::fs::File;
use std::io::{BufRead, BufReader};
use crate::runtime::ObjectReader::ObjectReader;
use crate::tweetStructs::TweetStatus::TweetStatus;

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
    let mut tweets: Vec<Option<TweetStatus>> = vec![None; nrow as usize];

    if seqRand.to_lowercase().eq("sequential") {
        crossbeam::scope(|scope| {
            let mut sum = 0;
            for tweetsChunk in tweets.chunks_mut(blklen as usize) {
                let beginPos = sum.clone();
                sum += tweetsChunk.len();
                let inDataPath = inDataPath.clone();
                let method = method.clone();
                scope.spawn(move |_| {
                    let mut reader = ObjectReader::new1(inDataPath.as_str(), method.as_str());
                    for (i, e) in tweetsChunk.iter_mut().enumerate() {
                        *e = Option::from(reader.readObject(i + beginPos).unwrap());
                    }
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
        let mut randomIDChuncks = randomIDs.chunks_mut(blklen as usize);

        crossbeam::scope(|scope| {
            let mut sum = 0;
            for tweetsChunk in tweets.chunks_mut(blklen as usize) {
                let beginPos = sum.clone();
                sum += tweetsChunk.len();
                let inDataPath = inDataPath.clone();
                let method = method.clone();
                let randomIDChunk = randomIDChuncks.next().unwrap();
                scope.spawn(move |_| {
                    let mut reader = ObjectReader::new1(inDataPath.as_str(), method.as_str());
                    for (i, e) in tweetsChunk.iter_mut().enumerate() {
                        *e = Option::from(reader.readObject(randomIDChunk[i as usize]).unwrap());
                    }
                    reader.flush();
                });
            }
        }).unwrap();
    }
    Ok(())
}