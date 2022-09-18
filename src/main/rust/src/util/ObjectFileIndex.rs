use crate::tweetStructs::TweetStatus::TweetStatus;
use std::cmp::Ordering;
use std::hash::{Hash, Hasher};

pub struct ObjectFileIndex {
	myObject: TweetStatus,
	fileIndex: u32,
	id: i64,
}

impl ObjectFileIndex {
	pub fn new(myObject: TweetStatus, fileIndex: u32) -> Self {
		let id = myObject.getId();
		ObjectFileIndex { myObject: myObject, fileIndex: fileIndex, id:id}
	}

	pub fn getObject(&self) -> TweetStatus {
		return self.myObject.to_owned();
	}

	pub fn getFileIndex(&self) -> u32 {
		return self.fileIndex;
	}
}

impl Ord for ObjectFileIndex {
	fn cmp(&self, other: &Self) -> Ordering {
		self.id.cmp(&other.id)
	}
}

impl PartialOrd for ObjectFileIndex {
	fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
		Some(self.cmp(other))
	}
}

impl PartialEq for ObjectFileIndex {
	fn eq(&self, other: &Self) -> bool {
		self.id == other.id
	}
}

impl Eq for ObjectFileIndex {}

impl Hash for ObjectFileIndex {
	fn hash<H: Hasher>(&self, state: &mut H) {
		self.id.hash(state);

	}
}
