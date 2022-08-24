#include "URLEntityIP.h"

URLEntityIP::URLEntityIP() {}

URLEntityIP::~URLEntityIP() {}


URLEntityIP::URLEntityIP(URLEntity *urlEntity) {

	this->serialize(urlEntity);
}

void URLEntityIP::serialize(URLEntity *urlEntity) {
	//TODO: implement inplace for vector:
	//vector<int> indices;

	this->displayURL = malloc<char>(strlen(urlEntity->displayURL.c_str()) + 1);
	strcpy(this->displayURL, urlEntity->displayURL.c_str());

	this->expandedURL = malloc<char>(strlen(urlEntity->expandedURL.c_str()) + 1);
	strcpy(this->expandedURL, urlEntity->expandedURL.c_str());

	this->url = malloc<char>(strlen(urlEntity->url.c_str()) + 1);
	strcpy(this->url, urlEntity->url.c_str());
}
