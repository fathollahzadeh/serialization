use crate::tweetStructs::TweetStatus::TweetStatus;
use std::cmp::Ordering;
use std::hash::{Hash, Hasher};
use std::fs::read;
use serde::{Serialize, Deserialize};

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct  ObjectFileIndex{
    myObject:TweetStatus,
    fileIndex:usize,
    id:i64,
}
impl ObjectFileIndex{
    pub fn new(myObject: TweetStatus, fileIndex: usize) -> Self {
        let id= myObject.getId();
        ObjectFileIndex { myObject, fileIndex, id }
    }

    pub fn getObject(&self)->TweetStatus{
        return self.myObject.to_owned();
    }

    pub fn getFileIndex(&self)->usize{
        return self.fileIndex;
    }
}
impl Ord for ObjectFileIndex {
    fn cmp(&self, other: &Self) -> Ordering {
        self.myObject.getOrder().cmp(&other.myObject.getOrder())
    }
}

impl PartialOrd for ObjectFileIndex {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

impl PartialEq for ObjectFileIndex {
    fn eq(&self, other: &Self) -> bool {
        self.myObject.getOrder() == other.myObject.getOrder()
    }
}
impl Eq for ObjectFileIndex {}

impl Hash for ObjectFileIndex {
    fn hash<H: Hasher>(&self, state: &mut H) {
        self.id.hash(state);
    }
}