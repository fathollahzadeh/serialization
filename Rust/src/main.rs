use std::{io, env};
use crate::benchmarks::DataSerialization::DataSerialization;
use crate::benchmarks::SequentialRead::SequentialRead;
use crate::benchmarks::RandomRead::RandomRead;
use bytes::{BytesMut, BufMut, Buf};
use crate::benchmarks::ExternalSort::ExternalSort;
use std::convert::TryInto;
use priority_queue::PriorityQueue;

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

    // let mut myVec=vec![];
    //
    // let a1=AA::new(1,1);
    // let a2=AA::new(1,2);
    // let a3=AA::new(0,3);
    // let a4=AA::new(8,4);
    //
    // myVec.push(a1);
    // myVec.push(a2);
    // myVec.push(a3);
    // myVec.push(a4);
    //
    // myVec.sort_by(|a,b|a.a.cmp(&b.a));
    //
    // for i in &myVec {
    //    i.mprint();
    // }

    // let mut pq = PriorityQueue::new();
    //
    // assert!(pq.is_empty());
    // pq.push("Apples", 5);
    // pq.push("Bananas", 8);
    // pq.push("Strawberries", 23);
    //
    // assert_eq!(pq.peek(), Some((&"Strawberries", &23)));
    //
    // pq.change_priority("Bananas", 25);
    // assert_eq!(pq.peek(), Some((&"Bananas", &25)));
    //
    // for (item, _) in pq.into_sorted_iter() {
    //     println!("{}", item);
    // }
    Ok(())
}

// struct  AA {
//     a:u64,
//     b:u64
// }
// impl AA {
//     pub fn new(a: u64, b: u64) -> Self {
//         AA { a, b }
//     }
//
//     pub fn mprint(&self){
//         println!("(a={},b={})",self.a,self.b);
//     }
// }
