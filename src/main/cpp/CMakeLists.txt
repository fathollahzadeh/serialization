cmake_minimum_required(VERSION 3.16.3)

project(cpp)

# set clang as the default compiler
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_FIND_DEBUG_MODE 1)

find_package(mongocxx CONFIG REQUIRED)
find_package(bsoncxx CONFIG REQUIRED)

include_directories(${LIBMONGOCXX_INCLUDE_DIR})
include_directories(${LIBBSONCXX_INCLUDE_DIR})


# set the output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/libraries")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/tools/cmake")
set(CTEST_BINARY_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

# check the operating system and add the appropriate flags
if (APPLE)
    SET(CMAKE_CXX_FLAGS " -std=c++11 -g -fPIC -Wno-deprecated-declarations")
    SET(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -undefined dynamic_lookup")
elseif (UNIX AND NOT APPLE)
    SET(CMAKE_CXX_FLAGS " -std=c++11 -g -march=native -O3 -fPIC -Wno-deprecated-declarations -pthread -lprotobuf -lboost_serialization")
endif ()


# set the directories with the common header files
include_directories("${PROJECT_SOURCE_DIR}/runtime/header")
include_directories("${PROJECT_SOURCE_DIR}/util/header")
include_directories("${PROJECT_SOURCE_DIR}/serialization/header")
include_directories("${PROJECT_SOURCE_DIR}/serialization/header/inplace")
include_directories("${PROJECT_SOURCE_DIR}/serialization/header/proto")
include_directories("${PROJECT_SOURCE_DIR}/benchmark/proto/*.h")
include_directories("${PROJECT_SOURCE_DIR}/benchmark/complexobject/header")
include_directories("${PROJECT_SOURCE_DIR}/benchmark/complexobject/header/inplace")
include_directories("${PROJECT_SOURCE_DIR}/benchmark/flatbuffers/*.h")
include_directories("${PROJECT_SOURCE_DIR}/serialization/header/flatbuffers")
include_directories("${PROJECT_SOURCE_DIR}/serialization/header/flatbuffers/flatbuffers")

# set the directories with the common source files
include_directories("${PROJECT_SOURCE_DIR}/runtime/source")
include_directories("${PROJECT_SOURCE_DIR}/util/source")
include_directories("${PROJECT_SOURCE_DIR}/serialization/source/")
include_directories("${PROJECT_SOURCE_DIR}/serialization/source/inplace/")
include_directories("${PROJECT_SOURCE_DIR}/serialization/source/proto/")
include_directories("${PROJECT_SOURCE_DIR}/benchmark/complexobject/source/")
include_directories("${PROJECT_SOURCE_DIR}/benchmark/complexobject/source/inplace/")
include_directories("${PROJECT_SOURCE_DIR}/benchmark/proto/*.cc")
include_directories("${PROJECT_SOURCE_DIR}/benchmark/flatbuffers/*.cc")
include_directories("${PROJECT_SOURCE_DIR}/serialization/source/flatbuffers/")
include_directories("${PROJECT_SOURCE_DIR}/experiments/")

# set serialization source files
file(GLOB srcIO "${PROJECT_SOURCE_DIR}/runtime/source/*.cpp")
file(GLOB srcUtil "${PROJECT_SOURCE_DIR}/util/source/*.cpp")
file(GLOB srcSerialization "${PROJECT_SOURCE_DIR}/serialization/source/*.cpp")
file(GLOB srcInPlace "${PROJECT_SOURCE_DIR}/serialization/source/inplace/*.cpp")
file(GLOB srcProtobuf "${PROJECT_SOURCE_DIR}/serialization/source/proto/*.cpp")
file(GLOB srcProtobufcc "${PROJECT_SOURCE_DIR}/serialization/source/proto/*.cc")
file(GLOB srcFlatbuf "${PROJECT_SOURCE_DIR}/serialization/source/flatbuffers/*.cpp")
file(GLOB srcBenchmarkCCP "${PROJECT_SOURCE_DIR}/benchmark/proto/*.cc")
file(GLOB srcBenchmarkCCF "${PROJECT_SOURCE_DIR}/benchmark/flatbuffers/*.cc")
file(GLOB srcComplexObject "${PROJECT_SOURCE_DIR}/benchmark/complexobject/source/*.cpp")
file(GLOB srcComplexObjectIP "${PROJECT_SOURCE_DIR}/benchmark/complexobject/source/inplace/*.cpp")


## prepare data
#add_executable(DataPrepare
#        experiments/DataPrepare.cpp
#        ${srcIO}
#        ${srcUtil}
#        ${srcSerialization}
#        ${srcInPlace}
#        ${srcProtobuf}
#        ${srcProtobufcc}
#        ${srcFlatbuf}
#        )
#target_link_libraries(DataPrepare PRIVATE mongo::bsoncxx_shared)
#target_link_libraries(DataPrepare PRIVATE mongo::mongocxx_shared)
#
## load data to memory- single thread
#add_executable(DataLoadToMemorySingle
#        experiments/DataLoadToMemorySingle.cpp
#        ${srcIO}
#        ${srcUtil}
#        ${srcSerialization}
#        ${srcInPlace}
#        ${srcProtobuf}
#        ${srcProtobufcc}
#        ${srcFlatbuf}
#        )
#target_link_libraries(DataLoadToMemorySingle PRIVATE mongo::bsoncxx_shared)
#target_link_libraries(DataLoadToMemorySingle PRIVATE mongo::mongocxx_shared)
#
## load data to memory- multi thread
#add_executable(DataLoadToMemoryParallel
#        experiments/DataLoadToMemoryParallel.cpp
#        ${srcIO}
#        ${srcUtil}
#        ${srcSerialization}
#        ${srcInPlace}
#        ${srcProtobuf}
#        ${srcProtobufcc}
#        ${srcFlatbuf}
#        )
#target_link_libraries(DataLoadToMemoryParallel PRIVATE mongo::bsoncxx_shared)
#target_link_libraries(DataLoadToMemoryParallel PRIVATE mongo::mongocxx_shared)
#
#
## serialize data single thread
#add_executable(DataSerializationSingle
#        experiments/DataSerializationSingle.cpp
#        ${srcIO}
#        ${srcUtil}
#        ${srcSerialization}
#        ${srcInPlace}
#        ${srcProtobuf}
#        ${srcProtobufcc}
#        ${srcFlatbuf}
#        )
#target_link_libraries(DataSerializationSingle PRIVATE mongo::bsoncxx_shared)
#target_link_libraries(DataSerializationSingle PRIVATE mongo::mongocxx_shared)
#
## serialize data multi thread
#add_executable(DataSerializationParallel
#        experiments/DataSerializationParallel.cpp
#        ${srcIO}
#        ${srcUtil}
#        ${srcSerialization}
#        ${srcInPlace}
#        ${srcProtobuf}
#        ${srcProtobufcc}
#        ${srcFlatbuf}
#        )
#target_link_libraries(DataSerializationParallel PRIVATE mongo::bsoncxx_shared)
#target_link_libraries(DataSerializationParallel PRIVATE mongo::mongocxx_shared)
#
## serialize data single thread
#add_executable(DataWriteSingle
#        experiments/DataWriteSingle.cpp
#        ${srcIO}
#        ${srcUtil}
#        ${srcSerialization}
#        ${srcInPlace}
#        ${srcProtobuf}
#        ${srcProtobufcc}
#        ${srcFlatbuf}
#        )
#target_link_libraries(DataWriteSingle PRIVATE mongo::bsoncxx_shared)
#target_link_libraries(DataWriteSingle PRIVATE mongo::mongocxx_shared)
#
## serialize data multi thread
#add_executable(DataWriteParallel
#        experiments/DataWriteParallel.cpp
#        ${srcIO}
#        ${srcUtil}
#        ${srcSerialization}
#        ${srcInPlace}
#        ${srcProtobuf}
#        ${srcProtobufcc}
#        ${srcFlatbuf}
#        )
#target_link_libraries(DataWriteParallel PRIVATE mongo::bsoncxx_shared)
#target_link_libraries(DataWriteParallel PRIVATE mongo::mongocxx_shared)
#
## read data single thread
#add_executable(DataReadSingle
#        experiments/DataReadSingle.cpp
#        ${srcIO}
#        ${srcUtil}
#        ${srcSerialization}
#        ${srcInPlace}
#        ${srcProtobuf}
#        ${srcProtobufcc}
#        ${srcFlatbuf}
#        )
#target_link_libraries(DataReadSingle PRIVATE mongo::bsoncxx_shared)
#target_link_libraries(DataReadSingle PRIVATE mongo::mongocxx_shared)
#
#add_executable(DataReadParallel
#        experiments/DataReadParallel.cpp
#        ${srcIO}
#        ${srcUtil}
#        ${srcSerialization}
#        ${srcInPlace}
#        ${srcProtobuf}
#        ${srcProtobufcc}
#        ${srcFlatbuf}
#        )
#target_link_libraries(DataReadParallel PRIVATE mongo::bsoncxx_shared)
#target_link_libraries(DataReadParallel PRIVATE mongo::mongocxx_shared)
#
## read I/O data single thread
#add_executable(DataReadIOSingle
#        experiments/DataReadIOSingle.cpp
#        ${srcIO}
#        ${srcUtil}
#        ${srcSerialization}
#        ${srcInPlace}
#        ${srcProtobuf}
#        ${srcProtobufcc}
#        ${srcFlatbuf}
#        )
#target_link_libraries(DataReadIOSingle PRIVATE mongo::bsoncxx_shared)
#target_link_libraries(DataReadIOSingle PRIVATE mongo::mongocxx_shared)
#
#
## read I/O data multi thread
#add_executable(DataReadIOParallel
#        experiments/DataReadIOParallel.cpp
#        ${srcIO}
#        ${srcUtil}
#        ${srcSerialization}
#        ${srcInPlace}
#        ${srcProtobuf}
#        ${srcProtobufcc}
#        ${srcFlatbuf}
#        )
#target_link_libraries(DataReadIOParallel PRIVATE mongo::bsoncxx_shared)
#target_link_libraries(DataReadIOParallel PRIVATE mongo::mongocxx_shared)
#
## External sort
#add_executable(ExternalSort
#        experiments/ExternalSort.cpp
#        ${srcIO}
#        ${srcUtil}
#        ${srcSerialization}
#        ${srcInPlace}
#        ${srcProtobuf}
#        ${srcProtobufcc}
#        ${srcFlatbuf}
#        )
#target_link_libraries(ExternalSort PRIVATE mongo::bsoncxx_shared)
#target_link_libraries(ExternalSort PRIVATE mongo::mongocxx_shared)
#
## External sort IO
#add_executable(ExternalSortIO
#        experiments/ExternalSortIO.cpp
#        ${srcIO}
#        ${srcUtil}
#        ${srcSerialization}
#        ${srcInPlace}
#        ${srcProtobuf}
#        ${srcProtobufcc}
#        ${srcFlatbuf}
#        )
#target_link_libraries(ExternalSortIO PRIVATE mongo::bsoncxx_shared)
#target_link_libraries(ExternalSortIO PRIVATE mongo::mongocxx_shared)
#
#
## Data Read Network
#add_executable(DataReadNetwork
#        experiments/DataReadNetwork.cpp
#        util/header/
#        ${srcIO}
#        ${srcUtil}
#        ${srcSerialization}
#        ${srcInPlace}
#        ${srcProtobuf}
#        ${srcProtobufcc}
#        ${srcFlatbuf}
#        )
#target_link_libraries(DataReadNetwork PRIVATE mongo::bsoncxx_shared)
#target_link_libraries(DataReadNetwork PRIVATE mongo::mongocxx_shared)
#
## Data Read Network NetworkIO
#add_executable(DataReadNetworkIO
#        experiments/DataReadNetworkIO.cpp
#        util/header/
#        ${srcIO}
#        ${srcUtil}
#        ${srcSerialization}
#        ${srcInPlace}
#        ${srcProtobuf}
#        ${srcProtobufcc}
#        ${srcFlatbuf}
#        )
#target_link_libraries(DataReadNetworkIO PRIVATE mongo::bsoncxx_shared)
#target_link_libraries(DataReadNetworkIO PRIVATE mongo::mongocxx_shared)

# Benchmark
add_executable(ProtoBufBench
        benchmark/proto/ComplexObjectL4.cpp
        ${srcBenchmark}
        ${srcBenchmarkCCP}
        )

add_executable(FlatBufBench
        benchmark/flatbuffers/ComplexObjectL4.cpp
        ${srcBenchmark}
        ${srcBenchmarkCCF}
        )

add_executable(ComplexObjectBench
        benchmark/complexobject/ComplexObject.cpp
        util/header/
        ${srcUtil}
        ${srcInPlace}
        ${srcComplexObject}
        ${srcComplexObjectIP}
        ${srcSerialization}
        )
target_link_libraries(ComplexObjectBench PRIVATE mongo::bsoncxx_shared)
target_link_libraries(ComplexObjectBench PRIVATE mongo::mongocxx_shared)