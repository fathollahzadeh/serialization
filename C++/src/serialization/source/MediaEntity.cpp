#include "MediaEntity.h"

using namespace std;

//Default constructor:
MediaEntity::MediaEntity() {
}

//Constructor with arguments:
MediaEntity::MediaEntity(string displayURL, string expandedURL, long id, vector<int> indices, string mediaURL,
						 string mediaURLHttps, MediaSizesEntity *sizes, long sourceStatusId,
						 string sourceStatusIdStr, string type,
						 string url, VideoEntity *videoInfo, AdditionalMediaInfoEntity *additionalMediaInfo) {
	this->displayURL = displayURL;
	this->expandedURL = expandedURL;
	this->id = id;
	this->indices = indices;
	this->mediaURL = mediaURL;
	this->mediaURLHttps = mediaURLHttps;
	this->sizes = sizes;
	this->sourceStatusId = sourceStatusId;
	this->sourceStatusIdStr = sourceStatusIdStr;
	this->type = type;
	this->url = url;
	this->additionalMediaInfo = additionalMediaInfo;
	this->videoInfo = videoInfo;
}


//C++: Explicit call needed for printing content:
string MediaEntity::toJSON() {
	string stringS = "{" +
					 getStringKeyValue("DisplayURL", this->displayURL) + "," +
					 getStringKeyValue("ExpandedURL", this->expandedURL) + "," +
					 getLongKeyValue("Id", this->id) + ",";
	stringS += "\"indices\":[";
	for (int j = 0; j < indices.size() - 1; ++j) {
		stringS += itos(indices[j]) + ",";
	}
	if (indices.size() > 0)
		stringS += itos(indices[indices.size() - 1]);
	stringS += "]," +

			   getStringKeyValue("MediaURL", this->mediaURL) + " , " +
			   getStringKeyValue("MediaURLHttps", this->mediaURLHttps) + " , " +
			   "\"Sizes\":" + this->sizes->toJSON() + " , " +
			   getLongKeyValue("SourceStatusId", this->sourceStatusId) + ", " +
			   getStringKeyValue("SourceStatusIdStr", this->sourceStatusIdStr) + ", " +
			   getStringKeyValue("Type", this->type) + ", " +
			   getStringKeyValue("Url", this->url);

	stringS += "}";

	return stringS;
}

//Hand Coded C++ serialization:
char *MediaEntity::serializeHandcoded(char *buffer, int &objectSize) {

	//Serialize the object.
	//Copy Integers:
	buffer = copyInt(buffer, this->indices.size(), objectSize);
	for (int i = 0; i < this->indices.size(); ++i) {
		buffer = copyInt(buffer, this->indices[i], objectSize);
	}
	//Copy Longs:
	buffer = copyLong(buffer, this->id, objectSize);
	buffer = copyLong(buffer, this->sourceStatusId, objectSize);

	//Copy Strings:
	buffer = copyString(buffer, this->displayURL, objectSize);
	buffer = copyString(buffer, this->expandedURL, objectSize);
	buffer = copyString(buffer, this->mediaURL, objectSize);
	buffer = copyString(buffer, this->mediaURLHttps, objectSize);
	buffer = copyString(buffer, this->sourceStatusIdStr, objectSize);
	buffer = copyString(buffer, this->type, objectSize);
	buffer = copyString(buffer, this->url, objectSize);

	//Copy MediaSizesEntityHC Objects:
	buffer = this->sizes->serializeHandcoded(buffer, objectSize);

	//Copy AdditionalMediaInfoEntityHC Object:
	if (this->additionalMediaInfo != nullptr) {
		buffer = copyBool(buffer, false, objectSize);
		buffer = this->additionalMediaInfo->serializeHandcoded(buffer, objectSize);
	} else
		buffer = copyBool(buffer, true, objectSize);

	//Copy VideoEntityHC Object:
	if (this->videoInfo != nullptr) {
		buffer = copyBool(buffer, false, objectSize);
		buffer = this->videoInfo->serializeHandcoded(buffer, objectSize);
	} else
		buffer = copyBool(buffer, true, objectSize);


	return buffer;
}


MediaEntity *MediaEntity::deserializeHandcoded(char *buffer, int &bytesRead) {
	//Parse Integers:
	int numOfIndices = parseInt(buffer + bytesRead);
	bytesRead += sizeof(numOfIndices);
	for (int i = 0; i < numOfIndices; ++i) {
		this->indices.push_back(parseInt(buffer + bytesRead));
		bytesRead += sizeof(int);
	}

	//Parse Longs:
	this->id = parseLong(buffer + bytesRead);
	bytesRead += sizeof(this->id);
	this->sourceStatusId = parseLong(buffer + bytesRead);
	bytesRead += sizeof(this->sourceStatusId);

	//Parse Strings:
	parseString(buffer + bytesRead, this->displayURL);
	bytesRead += (sizeof(int) + this->displayURL.length());
	parseString(buffer + bytesRead, this->expandedURL);
	bytesRead += (sizeof(int) + this->expandedURL.length());
	parseString(buffer + bytesRead, this->mediaURL);
	bytesRead += (sizeof(int) + this->mediaURL.length());
	parseString(buffer + bytesRead, this->mediaURLHttps);
	bytesRead += (sizeof(int) + this->mediaURLHttps.length());
	parseString(buffer + bytesRead, this->sourceStatusIdStr);
	bytesRead += (sizeof(int) + this->sourceStatusIdStr.length());
	parseString(buffer + bytesRead, this->type);
	bytesRead += (sizeof(int) + this->type.length());
	parseString(buffer + bytesRead, this->url);
	bytesRead += (sizeof(int) + this->url.length());

	//Parse MediaSizesEntityHC Objects:
	this->sizes = new MediaSizesEntity();
	this->sizes->deserializeHandcoded(buffer, bytesRead);

	bool checknullptr;
	//Parse AdditionalMediaInfoEntityHC Objects:
	checknullptr = parseBool(buffer + bytesRead);
	bytesRead += sizeof(checknullptr);
	if (!checknullptr) {
		this->additionalMediaInfo = new AdditionalMediaInfoEntity();
		this->additionalMediaInfo->deserializeHandcoded(buffer, bytesRead);

	} else
		this->additionalMediaInfo = nullptr;

	//Parse VideoEntityHC Objects:
	checknullptr = parseBool(buffer + bytesRead);
	bytesRead += sizeof(checknullptr);
	if (!checknullptr) {
		this->videoInfo = new VideoEntity();
		this->videoInfo->deserializeHandcoded(buffer, bytesRead);
	} else
		this->videoInfo = nullptr;

	return this;
}

MediaEntity::~MediaEntity() {

	//free memory:
	indices.shrink_to_fit();

	if (sizes != nullptr)
		delete sizes;

	if (videoInfo != nullptr)
		delete videoInfo;
	if (additionalMediaInfo != nullptr)
		delete additionalMediaInfo;
}

bsoncxx::document::value MediaEntity::serializeBSON() {
	using bsoncxx::builder::stream::document;
	using bsoncxx::builder::stream::finalize;
	using bsoncxx::builder::stream::array;
	using bsoncxx::builder::stream::open_document;
	using bsoncxx::builder::stream::close_document;

	document doc = document{};
	doc << "display_url" << this->displayURL <<
		"expanded_url" << this->expandedURL <<
		"id" << this->id;

	auto arrindices = array{};
	for (int i = 0; i < this->indices.size(); ++i) {
		arrindices << this->indices[i];
	}
	doc << "indices" << arrindices <<
		"media_url" << this->mediaURL <<
		"media_url_https" << this->mediaURLHttps;
	if (this->sizes != nullptr)
		doc << "sizes" << bsoncxx::types::b_document{this->sizes->serializeBSON().view()};
	doc << "type" << this->type <<
		"source_status_id" << this->sourceStatusId <<
		"source_status_id_str" << this->sourceStatusIdStr <<
		"url" << this->url;
	if (this->videoInfo != nullptr)
		doc << "video_info" << bsoncxx::types::b_document{this->videoInfo->serializeBSON().view()};

	if (this->additionalMediaInfo != nullptr)
		doc << "additional_media_info" << bsoncxx::types::b_document{this->additionalMediaInfo->serializeBSON().view()};

	return doc << finalize;
}


MediaEntity *MediaEntity::deserializeBSON(bsoncxx::document::view doc) {

	bsoncxx::document::element element = doc["display_url"];
	this->displayURL = bsoncxx::string::to_string(element.get_utf8().value);

	element = doc["id"];
	this->id = element.type() == bsoncxx::type::k_int64 ? element.get_int64().value : element.get_int32().value;

	element = doc["expanded_url"];
	this->expandedURL = bsoncxx::string::to_string(element.get_utf8().value);

	element = doc["indices"];
	if (element && element.type() == bsoncxx::type::k_array) {
		for (auto ele : element.get_array().value) {
			this->indices.push_back(ele.get_int32());
		}
	}

	element = doc["media_url"];
	this->mediaURL = bsoncxx::string::to_string(element.get_utf8().value);

	element = doc["media_url_https"];
	this->mediaURLHttps = bsoncxx::string::to_string(element.get_utf8().value);

	element = doc["sizes"];
	this->sizes = new MediaSizesEntity();
	this->sizes->deserializeBSON(element.get_document().view());

	element = doc["type"];
	this->type = bsoncxx::string::to_string(element.get_utf8().value);

	element = doc["source_status_id"];
	this->sourceStatusId =
			element.type() == bsoncxx::type::k_int64 ? element.get_int64().value : element.get_int32().value;

	element = doc["source_status_id_str"];
	this->sourceStatusIdStr = bsoncxx::string::to_string(element.get_utf8().value);

	element = doc["url"];
	this->url = bsoncxx::string::to_string(element.get_utf8().value);

	element = doc["video_info"];
	if (element) {
		this->videoInfo = new VideoEntity();
		this->videoInfo->deserializeBSON(element.get_document().view());
	} else
		this->videoInfo = nullptr;


	element = doc["additional_media_info"];
	if (element) {
		this->additionalMediaInfo = new AdditionalMediaInfoEntity();
		this->additionalMediaInfo->deserializeBSON(element.get_document().view());
	} else
		this->additionalMediaInfo = nullptr;
	return this;
}
