#include "SymbolEntityIP.h"

SymbolEntityIP::SymbolEntityIP() {}

SymbolEntityIP::~SymbolEntityIP() {}

SymbolEntityIP::SymbolEntityIP(SymbolEntity *symbolEntity) {

	this->serialize(symbolEntity);
}

void SymbolEntityIP::serialize(SymbolEntity *symbolEntity) {

	//TODO: implement inplace for vector:
	//vector<int> indices;

	this->text = malloc<char>(strlen(symbolEntity->text.c_str()) + 1);
	strcpy(this->text, symbolEntity->text.c_str());
}
