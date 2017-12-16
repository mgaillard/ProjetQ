cmake_minimum_required(VERSION 3.5)

project(HammingIndex)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

find_package(OpenMP)
if (OPENMP_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

find_package(libmongocxx REQUIRED)
find_package(libbsoncxx REQUIRED)
include_directories(${LIBMONGOCXX_INCLUDE_DIRS})
include_directories(${LIBBSONCXX_INCLUDE_DIRS})

find_library(LIBNODECPP_LIBRARY nodecpp HINT ../NodeCpp/build)
include_directories(../NodeCpp/src)

FIND_PACKAGE(CURL REQUIRED)
INCLUDE_DIRECTORIES(${CURL_INCLUDE_DIR})

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp HammingIndexApplication.h HammingIndexApplication.cpp HammingIndexController.h HammingIndexController.cpp HashStore.h HashStore.cpp Hamming.h Image.h DAOImage.h DAOImage.cpp HashingController.cpp HashingController.h DctPerceptualHash.cpp DctPerceptualHash.h ImageDownloader.cpp ImageDownloader.h)

add_executable(main ${SOURCE_FILES})
target_link_libraries(main ${LIBMONGOCXX_LIBRARIES})
target_link_libraries(main ${LIBBSONCXX_LIBRARIES})
target_link_libraries(main ${LIBNODECPP_LIBRARY})
target_link_libraries(main ${CURL_LIBRARIES})
target_link_libraries(main ${OpenCV_LIBS})
target_link_libraries(main -lfcgi++ -lfcgi)
