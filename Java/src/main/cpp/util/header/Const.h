#if !defined(CONST_H)
#define CONST_H 1

static const int PAGESIZE = 1024*1024;
static const int BATCHSIZE = 512;
static const int NETWORK_PAGESIZE = 20*1024*1024;
static const int NETWORK_LOCAL_READ_LENGTH = 20000;
static const int NETWORK_CLIENT_QUEUE_SIZE = 10;
static const int NETWORK_TIMEOUT = 2000*1000;

static const int HANDCODED= 1;
static const int INPLACE = 2;
static const int BOOST = 3;
static const int PROTOBUF = 4;
static const int BSON = 5;
static const int FLATBUF = 6;

#endif

