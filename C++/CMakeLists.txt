cmake_minimum_required(VERSION 3.5)

project(C__)


# set clang as the default compiler
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
# set(CMAKE_CXX_STANDARD 11)

find_package(libmongocxx REQUIRED)
find_package(libbsoncxx REQUIRED)
include_directories(${LIBMONGOCXX_INCLUDE_DIR})
include_directories(${LIBBSONCXX_INCLUDE_DIR})
include_directories("/usr/local/include/mongocxx/v_noabi")
include_directories("/usr/local/include/bsoncxx/v_noabi")
include_directories("/usr/local/include/libmongoc-1.0")
include_directories("/usr/local/include/libbson-1.0")
include_directories("/usr/local/lib")


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
include_directories("${PROJECT_SOURCE_DIR}/src/filehandler/header")
include_directories("${PROJECT_SOURCE_DIR}/src/rootdata/header")
include_directories("${PROJECT_SOURCE_DIR}/src/serialization/header")
include_directories("${PROJECT_SOURCE_DIR}/src/serialization/header/inplace")
include_directories("${PROJECT_SOURCE_DIR}/src/serialization/header/proto")
include_directories("${PROJECT_SOURCE_DIR}/src/serialization/header/flatbuffers")
include_directories("${PROJECT_SOURCE_DIR}/src/serialization/header/flatbuffers/flatbuffers")
include_directories("${PROJECT_SOURCE_DIR}/src/benchmarks/header")
include_directories("${PROJECT_SOURCE_DIR}/src/networkadapter/header")

# set the directories with the common source files
include_directories("${PROJECT_SOURCE_DIR}/src/serialization/source/")
include_directories("${PROJECT_SOURCE_DIR}/src/serialization/source/inplace/")
include_directories("${PROJECT_SOURCE_DIR}/src/serialization/source/proto/")
include_directories("${PROJECT_SOURCE_DIR}/src/serialization/source/flatbuffers/")
include_directories("${PROJECT_SOURCE_DIR}/src/rootdata/source/")
include_directories("${PROJECT_SOURCE_DIR}/src/filehandler/source/")
include_directories("${PROJECT_SOURCE_DIR}/src/networkadapter/source")

# set serialization source files
file(GLOB serializationSource "${PROJECT_SOURCE_DIR}/src/serialization/source/*.cpp")
file(GLOB inPlaceSerializationSource "${PROJECT_SOURCE_DIR}/src/serialization/source/inplace/*.cpp")
file(GLOB protSerializationSource "${PROJECT_SOURCE_DIR}/src/serialization/source/proto/*.cpp")
file(GLOB flatBuffersSerializationSource "${PROJECT_SOURCE_DIR}/src/serialization/source/flatbuffers/*.cpp")
file(GLOB rootDataSource "${PROJECT_SOURCE_DIR}/src/rootdata/source/*.cpp")
file(GLOB rootDataHeader "${PROJECT_SOURCE_DIR}/src/rootdata/header/*.h")
file(GLOB networkAdapterSource "${PROJECT_SOURCE_DIR}/src/networkadapter/source/*.cpp")

# data serialization
add_executable(TwitterSerialization
        src/benchmarks/source/DataSerialization.cpp
        src/filehandler/source/FileHandler.cpp
        src/filehandler/source/DataReader.cpp
        src/filehandler/source/LogFileHandler.cpp
        src/serialization/source/proto/TweetStatusP.pb.cc
        ${serializationSource}
        ${inPlaceSerializationSource}
        ${protSerializationSource}
        ${flatBuffersSerializationSource}
        ${rootDataSource}
        )

target_link_libraries(TwitterSerialization ${LIBMONGOCXX_LIBRARIES})
target_link_libraries(TwitterSerialization ${LIBBSONCXX_LIBRARIES})

# generate random list for benchmark random read
add_executable(TwitterGenerateRandomList
        src/benchmarks/source/GenerateRandomList.cpp
        )
target_link_libraries(TwitterGenerateRandomList ${LIBMONGOCXX_LIBRARIES})
target_link_libraries(TwitterGenerateRandomList ${LIBBSONCXX_LIBRARIES})

# data generate
add_executable(TwitterGenerateData
        src/benchmarks/source/GenerateData.cpp
        )
target_link_libraries(TwitterGenerateData ${LIBMONGOCXX_LIBRARIES})
target_link_libraries(TwitterGenerateData ${LIBBSONCXX_LIBRARIES})


# sequential read benchmark
add_executable(TwitterSequentialRead
        src/benchmarks/source/SequentialRead.cpp
        src/filehandler/source/FileHandler.cpp
        src/filehandler/source/DataReader.cpp
        src/filehandler/source/LogFileHandler.cpp
        src/serialization/source/proto/TweetStatusP.pb.cc
        ${serializationSource}
        ${inPlaceSerializationSource}
        ${protSerializationSource}
        ${flatBuffersSerializationSource}
        ${rootDataSource}
        )
target_link_libraries(TwitterSequentialRead ${LIBMONGOCXX_LIBRARIES})
target_link_libraries(TwitterSequentialRead ${LIBBSONCXX_LIBRARIES})

# random read benchmark
add_executable(TwitterRandomRead
        src/benchmarks/source/RandomRead.cpp
        src/filehandler/source/FileHandler.cpp
        src/filehandler/source/DataReader.cpp
        src/filehandler/source/LogFileHandler.cpp
        src/serialization/source/proto/TweetStatusP.pb.cc
        ${serializationSource}
        ${inPlaceSerializationSource}
        ${protSerializationSource}
        ${flatBuffersSerializationSource}
        ${rootDataSource}
        )
target_link_libraries(TwitterRandomRead ${LIBMONGOCXX_LIBRARIES})
target_link_libraries(TwitterRandomRead ${LIBBSONCXX_LIBRARIES})

# external sort benchmark
add_executable(TwitterExternalSort
        src/benchmarks/source/ExternalSort.cpp
        src/filehandler/source/FileHandler.cpp
        src/filehandler/source/DataReader.cpp
        src/filehandler/source/LogFileHandler.cpp
        src/serialization/source/proto/TweetStatusP.pb.cc
        ${serializationSource}
        ${inPlaceSerializationSource}
        ${protSerializationSource}
        ${flatBuffersSerializationSource}
        ${rootDataSource}
        )
target_link_libraries(TwitterExternalSort ${LIBMONGOCXX_LIBRARIES})
target_link_libraries(TwitterExternalSort ${LIBBSONCXX_LIBRARIES})

# network benchmark
add_executable(TwitterNetworkServer
        src/benchmarks/source/NetworkServer.cpp
        ${serializationSource}
        ${networkAdapterSource}
        ${serializationSource}
        ${inPlaceSerializationSource}
        ${protSerializationSource}
        ${flatBuffersSerializationSource}
        ${rootDataSource}
        src/serialization/source/proto/TweetStatusP.pb.cc
        )
target_link_libraries(TwitterNetworkServer ${LIBMONGOCXX_LIBRARIES})
target_link_libraries(TwitterNetworkServer ${LIBBSONCXX_LIBRARIES})

# network benchmark client
add_executable(TwitterNetworkClient
        src/benchmarks/source/NetworkClient.cpp
        src/filehandler/source/FileHandler.cpp
        src/filehandler/source/DataReader.cpp
        src/filehandler/source/LogFileHandler.cpp
        src/serialization/source/proto/TweetStatusP.pb.cc
        ${serializationSource}
        ${inPlaceSerializationSource}
        ${protSerializationSource}
        ${flatBuffersSerializationSource}
        ${rootDataSource}
        ${networkAdapterSource}
        )
target_link_libraries(TwitterNetworkClient ${LIBMONGOCXX_LIBRARIES})
target_link_libraries(TwitterNetworkClient ${LIBBSONCXX_LIBRARIES})

