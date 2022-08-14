#include "BoundingBoxCoordinate.h"

using namespace std;


//Default constructor:
BoundingBoxCoordinate::BoundingBoxCoordinate() {
}

//Constructor with arguments:
BoundingBoxCoordinate::BoundingBoxCoordinate(const string &type, const vector <vector<vector < double>>

> &coordinates)
:

type (type), coordinates(coordinates) {}


string BoundingBoxCoordinate::toJSON() {
	string stringS = "{" + getStringKeyValue("Type", this->type) + ",";
	stringS += "\"coordinates\":[";
	if (coordinates.size() > 0) {
		stringS += "[";
		for (int i = 0; i < coordinates.size() - 1; ++i) {
			for (int j = 0; j < coordinates.at(i).size() - 1; ++j) {
				stringS += "[" + dtos(coordinates.at(i).at(j).at(0)) + "," + dtos(coordinates.at(i).at(j).at(1)) + "],";
			}
			if (coordinates.at(i).size() > 0) {
				stringS += "[" + dtos(coordinates.at(i).at(coordinates.at(i).size() - 1).at(0)) + "," +
						   dtos(coordinates.at(i).at(coordinates.at(i).size() - 1).at(1)) + "],";
			}

		}

		for (int j = 0; j < coordinates.at(coordinates.size() - 1).size() - 1; ++j) {
			stringS += "[" + dtos(coordinates.at(coordinates.size() - 1).at(j).at(0)) + "," +
					   dtos(coordinates.at(coordinates.size() - 1).at(j).at(1)) + "],";
		}
		if (coordinates.at(coordinates.size() - 1).size() > 0) {
			stringS += "[" + dtos(coordinates.at(coordinates.size() - 1).at(
					coordinates.at(coordinates.size() - 1).size() - 1).at(0)) + "," +
					   dtos(coordinates.at(coordinates.size() - 1).at(
							   coordinates.at(coordinates.size() - 1).size() - 1).at(1)) + "]";
		}
		stringS += "]";

	}

	stringS += "]";
	return stringS;
}

//Hand Coded C++ serialization:
char *BoundingBoxCoordinate::serializeHandcoded(char *buffer, int &objectSize) {
	//Serialize the object.
	//Copy Doubles:
	int numOfCoordinates = this->coordinates.size();
	buffer = copyInt(buffer, numOfCoordinates, objectSize);

	for (int i = 0; i < numOfCoordinates; i++) {

		int numOfOptions = this->coordinates.at(i).size();
		buffer = copyInt(buffer, numOfOptions, objectSize);
		for (int j = 0; j < numOfOptions; ++j) {
			//Copy Double:
			buffer = copyDouble(buffer, this->coordinates.at(i).at(j).at(0), objectSize); // 8 bytes for latitudes
			buffer = copyDouble(buffer, this->coordinates.at(i).at(j).at(1), objectSize); // 8 bytes for longitudes
		}
	}
	//Copy String:
	buffer = copyString(buffer, this->type, objectSize);
	return buffer;
}

//Hand Coded C++ de-serialization:
BoundingBoxCoordinate *BoundingBoxCoordinate::deserializeHandcoded(char *buffer, int &bytesRead) {
	int numOfCoordinates = parseInt(buffer + bytesRead);
	bytesRead += sizeof(numOfCoordinates);
	for (int i = 0; i < numOfCoordinates; i++) {

		int numOfOptions = parseInt(buffer + bytesRead);
		bytesRead += sizeof(numOfOptions);

		vector <vector<double>> tempOptions;

		for (int j = 0; j < numOfOptions; ++j) {
			vector<double> longitude_latitude;
			//Read 8 bytes for latitudes:
			longitude_latitude.push_back(parseDouble(buffer + bytesRead));
			bytesRead += sizeof(double);

			//Read 8 bytes for longitudes
			longitude_latitude.push_back(parseDouble(buffer + bytesRead));
			bytesRead += sizeof(double);
			tempOptions.push_back(longitude_latitude);
		}
		this->coordinates.push_back(tempOptions);
	}

	//Parse Strings:
	parseString(buffer + bytesRead, this->type);
	bytesRead += (sizeof(int) + this->type.length());

	return this;
}


BoundingBoxCoordinate::~BoundingBoxCoordinate() {
	//free memory:
	for (int i = 0; i < coordinates.size(); ++i) {
		coordinates.at(i).shrink_to_fit();
	}

}

bsoncxx::document::value BoundingBoxCoordinate::serializeBSON() {
	using bsoncxx::builder::stream::document;
	using bsoncxx::builder::stream::finalize;
	using bsoncxx::builder::stream::array;
	document doc = document{};
	doc << "type" << this->type;

	auto arr1 = array{};

	for (int i = 0; i < this->coordinates.size(); i++) {
		auto arr2 = array{};
		for (int j = 0; j < this->coordinates.at(i).size(); ++j) {
			//Copy Double:
			auto arr3 = array{};
			arr3 << this->coordinates.at(i).at(j).at(0) << this->coordinates.at(i).at(j).at(1);
			arr2 << arr3;
		}
		arr1 << arr2;
	}
	doc << "coordinates" << arr1;
	return doc << finalize;
}

BoundingBoxCoordinate *BoundingBoxCoordinate::deserializeBSON(bsoncxx::document::view doc) {
	bsoncxx::document::element element = doc["type"];
	this->type = bsoncxx::string::to_string(element.get_utf8().value);

	element = doc["coordinates"];
	if (element && element.type() == bsoncxx::type::k_array) {
		for (auto ele1 : element.get_array().value) {
			vector <vector<double>> arr2;
			for (auto ele2 : ele1.get_array().value) {
				vector<double> arr3;
				for (auto ele3 : ele2.get_array().value) {
					arr3.push_back(ele3.get_double());
				}
				arr2.push_back(arr3);
			}
			this->coordinates.push_back(arr2);
		}
	}

	return this;
}


