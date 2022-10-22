#if !defined(CONST_H)
#define CONST_H 1
#include <thread>

static const int PAGESIZE = 1024*1024;
static const int BATCHSIZE = 512;
static const int NETWORK_PAGESIZE = 20*1024*1024;
static const int NETWORK_LOCAL_READ_LENGTH = 2000;
static const int NETWORK_CLIENT_QUEUE_SIZE = 4;
static const int NETWORK_TIMEOUT = 2000*1000;

static const int HANDCODED= 1;
static const int INPLACE = 2;
static const int BOOST = 3;
static const int PROTOBUF = 4;
static const int BSON = 5;
static const int FLATBUF = 6;

const auto NUM_THREADS = std::thread::hardware_concurrency();

enum NodeType {  ROOT,  MIDDLE, LEAF };

#endif

