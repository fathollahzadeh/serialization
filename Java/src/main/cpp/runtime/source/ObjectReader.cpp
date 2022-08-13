#include "ObjectReader.h"

ObjectReader::ObjectReader(const string &method){
    this->method = method;
    this->currentOffset = 0;
    this->row = 0;
}

ObjectReader::ObjectReader(const string &fname, const string &method):ObjectReader(method) {

    //Allocates write page buffer:
    this->pageBuffer = new char[2 * Const.PAGESIZE];

    try {
        this.objectInEachPage = new HashMap<>();
        Path path = Paths.get(fname);

        //Opening serialized file and keeping it open
        this.inStreamRegularFile = FileChannel.open(path);
        this.bbPageBuffer = ByteBuffer.allocateDirect(Const.PAGESIZE);

        //Read the page and object map data from file
        readIndexesFromFile(fname);

        this.currentPageNumber = -1;
        //calculate object in each page:
        for (int index : pageIndex) {
            if (objectInEachPage.containsKey(index)) objectInEachPage.put(index, objectInEachPage.get(index) + 1);
            else objectInEachPage.put(index, 0);
        }
    } catch (Exception ex) {
        logger.error("prepareToRead! ", ex);
    }
}
