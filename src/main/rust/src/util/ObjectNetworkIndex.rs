use crate::tweetStructs::TweetStatus::TweetStatus;
use std::cmp::Ordering;
use std::hash::{Hash, Hasher};

pub struct ObjectNetworkIndex {
	myObject: TweetStatus,
	clientIndex: u32,
	id: i64,
}

impl ObjectNetworkIndex {
	pub fn new(myObject: TweetStatus, clientIndex: u32) -> Self {
		let id = myObject.getId();
		ObjectNetworkIndex { myObject: myObject, clientIndex: clientIndex, id:id}
	}

	pub fn getObject(&self) -> TweetStatus {
		return self.myObject.to_owned();
	}

	pub fn getClientIndex(&self) -> u32 {
		return self.clientIndex;
	}
}

impl Ord for ObjectNetworkIndex {
	fn cmp(&self, other: &Self) -> Ordering {
		self.id.cmp(&other.id)
	}
}

impl PartialOrd for ObjectNetworkIndex {
	fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
		Some(self.cmp(other))
	}
}

impl PartialEq for ObjectNetworkIndex {
	fn eq(&self, other: &Self) -> bool {
		self.id == other.id
	}
}

impl Eq for ObjectNetworkIndex {}

impl Hash for ObjectNetworkIndex {
	fn hash<H: Hasher>(&self, state: &mut H) {
		self.id.hash(state);

	}
}
