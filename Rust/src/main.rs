use std::{io, env};
use crate::benchmarks::DataSerialization::DataSerialization;
use crate::benchmarks::SequentialRead::SequentialRead;
use crate::benchmarks::RandomRead::RandomRead;
use bytes::{BytesMut, BufMut, Buf};
use crate::benchmarks::ExternalSort::ExternalSort;
use std::convert::TryInto;


mod tweetStructs;
mod filehandler;
mod benchmarks;
mod util;

fn main() -> io::Result<()>{

    let args: Vec<String> = env::args().collect();
    let bench_type=&args[1];

    if bench_type=="write" {
        DataSerialization(args);
    } else if bench_type=="sequential_read" {
        SequentialRead(args);
    }
    else if bench_type=="random_read" {
        RandomRead(args);
    }else if bench_type=="external_sort" {
        ExternalSort(args);
    }

    Ok(())
}
