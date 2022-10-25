#include "RootData.h"


using namespace std;

// Copy a double into the buffer.
char *RootData::copyDouble(char *buffer, double copyThis, int &objectSize) {
	memcpy(buffer, &copyThis, sizeof(copyThis));
	buffer += sizeof(copyThis);
	objectSize += sizeof(copyThis);
	return buffer;
}

// Parse a double from buffer.
double RootData::parseDouble(char *buffer) {
	double element;
	memcpy(&element, buffer, sizeof(element));
	return element;
}

// Copy an integer into the buffer.
char *RootData::copyInt(char *buffer, int copyThis, int &objectSize) {
	memcpy(buffer, &copyThis, sizeof(copyThis));
	buffer += sizeof(copyThis);
	objectSize += sizeof(copyThis);
	return buffer;
}

// Parse an integer from buffer.
int RootData::parseInt(char *buffer) {
	int element;
	memcpy(&element, buffer, sizeof(element));
	return element;
}

// Copy an long into the buffer.
char *RootData::copyLong(char *buffer, long copyThis, int &objectSize) {
	memcpy(buffer, &copyThis, sizeof(copyThis));
	buffer += sizeof(copyThis);
	objectSize += sizeof(copyThis);
	return buffer;
}

// Parse an long from buffer.
long RootData::parseLong(char *buffer) {
	long element;
	memcpy(&element, buffer, sizeof(element));
	return element;
}

// Copy a boolean into the buffer.
char *RootData::copyBool(char *buffer, bool copyThis, int &objectSize) {
	memcpy(buffer, &copyThis, sizeof(copyThis));
	buffer += sizeof(copyThis);
	objectSize += sizeof(copyThis);
	return buffer;
}

// Parse a boolean from buffer.
bool RootData::parseBool(char *buffer) {
	// Return bool values as true or false, instead of 0 or 1
	std::cout.setf(std::ios::boolalpha);

	bool element;
	memcpy(&element, buffer, sizeof(element));
	return element;
}


// Copy [size(string), string] into the buffer.
char *RootData::copyString(char *buffer, string copyThis, int &objectSize) {
//    char * RootData::copyString (char * buffer, string copyThis) {
	//Write "length" of the string.
	int sizeofString = copyThis.length();
	memcpy(buffer, &sizeofString, sizeof(sizeofString));
	buffer += sizeof(sizeofString);
	objectSize += sizeof(sizeofString);

	//Write the content of the string.
	memcpy(buffer, copyThis.c_str(), copyThis.length());
	buffer += copyThis.length();
	objectSize += sizeofString;
	return buffer;
}

//Avoid sending string as returned object:
void RootData::parseString(char *buffer, string &s) {
	//Parse "length" of the string.
	int sizeofString;
	memcpy(&sizeofString, buffer, sizeof(sizeofString));
	buffer += sizeof(sizeofString);

	//Parse the content of the string.
	s.assign(buffer, sizeofString);
}


//Convert integer to string.
string RootData::itos(int element) {
	ostringstream ss;
	ss << element;
	return ss.str();
}

//Convert double to string.
string RootData::dtos(double element) {
	//ostringstream ss;
	// ss << element;
	//return ss.str();
	return to_string(element);
}

//Convert long to string.
string RootData::ltos(long element) {
	ostringstream ss;
	ss << element;
	return ss.str();
}

//Convert boolean to string.
string RootData::btos(bool element) {
	ostringstream ss;
	ss << element;
	return ss.str();
}

//Unimplemented Functions:
long RootData::serializeInPlace(char *fileStart) {
	throw invalid_argument("RootData::serializeInPlace(...)");
	return -1;
}


/*void RootData::deserializeBoost(char *buffer, RootData *) {
    throw invalid_argument("RootData* RootData::deserializeBoost(...)");
}*/

void RootData::freePointedObjects() {
	throw invalid_argument("RootData::freeMemory(...)");
}

boost::archive::text_iarchive *RootData::getArchive() {
	throw invalid_argument("RootData::getArchive(...)");
	return NULL;
}

stringstream *RootData::getStream() {
	throw invalid_argument("RootData::getStream(...)");
	return NULL;
}

bool RootData::isDeleted() const {
	return deleted;
}

void RootData::setDeleted(bool deleted) {
	RootData::deleted = deleted;
}

char *RootData::copyInPlaceInt(char *buffer, int copyThis) {
	new(buffer)int(copyThis);

	return buffer + sizeof(int);
}

char *RootData::copyInPlaceLong(char *buffer, long copyThis) {
	new(buffer)int(copyThis);

	return buffer + sizeof(long);
}

char *RootData::copyInPlaceDouble(char *buffer, double copyThis) {
	new(buffer)int(copyThis);

	return buffer + sizeof(double);
}

int RootData::parseInPlaceInt(char *buffer) {
	int element = *(int *) buffer;
	return element;
}

long RootData::parseInPlaceLong(char *buffer) {
	long element = *(long *) buffer;
	return element;
}

double RootData::parseInPlaceDouble(char *buffer) {
	double element = *(double *) buffer;
	return element;
}
