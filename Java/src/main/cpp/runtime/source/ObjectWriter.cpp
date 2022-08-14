#include "ObjectWriter.h"

ObjectWriter::~ObjectWriter() {}

ObjectWriter::ObjectWriter(const string &fname, const string &method, int rlen) :ObjectWriter(method, rlen, PAGESIZE) {
    this->outStreamRegularFile.open(fname.c_str(), ofstream::binary | ofstream::trunc);
    this->outIndexFile.open((fname + ".index").c_str(), ofstream::binary | ofstream::trunc);
}

ObjectWriter::ObjectWriter(const string &method, int rlen, int pageSize){
    this->currentPageNumber = 0;
    this->currentOffset = 0;
    this->method = method;
    this->pageBuffer = new char[2 * pageSize]; // this is our page
    this->pageBuffer = new char[2 * PAGESIZE];
    this->rlen = rlen;
    this->row = 0;
    this->pageIndex = new int[rlen];
    this->objectIndex = new int[rlen];
    this->objectLength = new int[rlen];

    if (strcasecmp(this->method.c_str(), "inplace") == 0)
        Object::allocator.setUp(this->pageBuffer, 2 * PAGESIZE);
}
