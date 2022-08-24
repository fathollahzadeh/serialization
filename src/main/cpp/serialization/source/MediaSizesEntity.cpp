#include "MediaSizesEntity.h"

using namespace std;

//Default constructor:
MediaSizesEntity::MediaSizesEntity() {
}


MediaSizesEntity::MediaSizesEntity(SizeEntity *thumb, SizeEntity *large, SizeEntity *medium,
								   SizeEntity *small) {
	this->thumb = thumb;
	this->large = large;
	this->medium = medium;
	this->small = small;
}

//Hand Coded C++ serialization:
char *MediaSizesEntity::serializeHandcoded(char *buffer, int &objectSize) {

	buffer = this->thumb->serializeHandcoded(buffer, objectSize);

	buffer = this->large->serializeHandcoded(buffer, objectSize);

	buffer = this->medium->serializeHandcoded(buffer, objectSize);

	buffer = this->small->serializeHandcoded(buffer, objectSize);

	return buffer;
}


MediaSizesEntity *MediaSizesEntity::deserializeHandcoded(char *buffer, int &bytesRead) {

	this->thumb = new SizeEntity();
	this->thumb->deserializeHandcoded(buffer, bytesRead);

	this->large = new SizeEntity();
	this->large->deserializeHandcoded(buffer, bytesRead);

	this->medium = new SizeEntity();
	this->medium->deserializeHandcoded(buffer, bytesRead);

	this->small = new SizeEntity();
	this->small->deserializeHandcoded(buffer, bytesRead);

	return this;
}

bsoncxx::document::value MediaSizesEntity::serializeBSON() {
	using bsoncxx::builder::stream::document;
	using bsoncxx::builder::stream::finalize;
	using bsoncxx::builder::stream::array;

	document doc = document{};
	if (this->thumb != nullptr)
		doc << "thumb" << bsoncxx::types::b_document{this->thumb->serializeBSON().view()};

	if (this->large != nullptr)
		doc << "large" << bsoncxx::types::b_document{this->large->serializeBSON().view()};

	if (this->medium != nullptr)
		doc << "medium" << bsoncxx::types::b_document{this->medium->serializeBSON().view()};

	if (this->small != nullptr)
		doc << "small" << bsoncxx::types::b_document{this->small->serializeBSON().view()};

	return doc << finalize;
}

MediaSizesEntity *MediaSizesEntity::deserializeBSON(bsoncxx::document::view doc) {
	bsoncxx::document::element element = doc["thumb"];
	if (element) {
		this->thumb = new SizeEntity();
		this->thumb->deserializeBSON(element.get_document().view());
	} else
		this->thumb = nullptr;

	element = doc["large"];
	if (element) {
		this->large = new SizeEntity();
		this->large->deserializeBSON(element.get_document().view());
	} else
		this->large = nullptr;

	element = doc["medium"];
	if (element) {
		this->medium = new SizeEntity();
		this->medium->deserializeBSON(element.get_document().view());
	} else
		this->medium = nullptr;

	element = doc["small"];
	if (element) {
		this->small = new SizeEntity();
		this->small->deserializeBSON(element.get_document().view());
	} else
		this->small = nullptr;
	return this;
}


MediaSizesEntity::~MediaSizesEntity() {

	//free memory:
	if (thumb != nullptr)
		delete thumb;
	if (large != nullptr)
		delete large;
	if (medium != nullptr)
		delete medium;
	if (small != nullptr)
		delete small;
}

