#include "VariantEntity.h"

using namespace std;


//Copy constructor:
VariantEntity::VariantEntity(const VariantEntity &obj) {
	throw invalid_argument("VariantEntity: Not copy constructible.");
}


//Default constructor:
VariantEntity::VariantEntity() {
}

//Constructor with arguments:
VariantEntity::VariantEntity(long bitrate, string contentType, string url) {
	this->bitrate = bitrate;
	this->contentType = contentType;
	this->url = url;
}

//Hand Coded C++ serialization:
char *VariantEntity::serializeHandcoded(char *buffer, int &objectSize) {
	//Serialize the object.
	//Copy Long elements:
	buffer = copyLong(buffer, this->bitrate, objectSize);
	//Copy Strings:
	buffer = copyString(buffer, this->contentType, objectSize);
	buffer = copyString(buffer, this->url, objectSize);

	return buffer;
}


VariantEntity *VariantEntity::deserializeHandcoded(char *buffer, int &bytesRead) {

	this->bitrate = parseLong(buffer + bytesRead);
	bytesRead += sizeof(this->bitrate);

	//Parse Strings:
	parseString(buffer + bytesRead, this->contentType);
	bytesRead += (sizeof(int) + this->contentType.length());
	parseString(buffer + bytesRead, this->url);
	bytesRead += (sizeof(int) + this->url.length());

	return this;
}

VariantEntity::~VariantEntity() {}

bsoncxx::document::value VariantEntity::serializeBSON() {
	using bsoncxx::builder::stream::document;
	using bsoncxx::builder::stream::finalize;
	using bsoncxx::builder::stream::array;

	document doc = document{};
	doc << "bitrate" << this->bitrate <<
		"content_type" << this->contentType <<
		"url" << this->url;

	return doc << finalize;
}

VariantEntity *VariantEntity::deserializeBSON(bsoncxx::document::view doc) {
	bsoncxx::document::element element = doc["bitrate"];
	this->bitrate = element.type() == bsoncxx::type::k_int64 ? element.get_int64() : element.get_int32();

	element = doc["content_type"];
	this->contentType = bsoncxx::string::to_string(element.get_utf8().value);

	element = doc["url"];
	this->url = bsoncxx::string::to_string(element.get_utf8().value);

	return this;
}
