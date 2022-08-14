#include "OptionEntity.h"

OptionEntity::OptionEntity() {}

OptionEntity::~OptionEntity() {

}

OptionEntity::OptionEntity(int position, const string &text) : position(position), text(text) {}

//C++: Explicit call needed for printing content:
string OptionEntity::toJSON() {
	string stringS = "{" +
					 getIntKeyValue("position", this->position) + " , " +
					 getStringKeyValue("Text", this->text) + "}";
	return stringS;
}

//Hand Coded C++ serialization:
char *OptionEntity::serializeHandcoded(char *buffer, int &objectSize) {
	//Serialize the object.
	//Copy Integers:
	buffer = copyInt(buffer, this->position, objectSize);
	//Copy Strings:
	buffer = copyString(buffer, this->text, objectSize);

	return buffer;
}


OptionEntity *OptionEntity::deserializeHandcoded(char *buffer, int &bytesRead) {

	OptionEntity *optionEntity = new OptionEntity();
	//Parse Integer:
	optionEntity->position = parseInt(buffer + bytesRead);
	bytesRead += sizeof(optionEntity->position);

	//Parse Strings:
	parseString(buffer + bytesRead, optionEntity->text);
	bytesRead += (sizeof(int) + optionEntity->text.length());

	return optionEntity;
}

bsoncxx::document::value OptionEntity::serializeBSON() {
	using bsoncxx::builder::stream::document;
	using bsoncxx::builder::stream::finalize;

	document doc = document{};
	doc << "position" << this->position <<
		"text" << this->text;
	return doc << finalize;
}

OptionEntity *OptionEntity::deserializeBSON(bsoncxx::document::view doc) {
	bsoncxx::document::element element = doc["position"];
	this->position = element.get_int32();

	element = doc["text"];
	this->text = bsoncxx::string::to_string(element.get_utf8().value);

	return this;
}
