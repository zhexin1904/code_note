cmake_minimum_required(VERSION 3.0)
project(google_tool)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_BUILD_TYPE Release)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin CACHE PATH "The directory in which to place executables built by this project")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package(Glog REQUIRED)
if (GLOG_FOUND)
    message(STATUS "Found Google Logging: ${GLOG_INCLUDE_DIRS}")
else (GLOG_FOUND)
    message(FATAL_ERROR "Can't find Google Logging. Please set GLOG_INCLUDE_DIR & "
            "GLOG_LIBRARY")
endif (GLOG_FOUND)

include_directories(
        ${GLOG_INCLUDE_DIRS}
)

add_executable(google_tool src/main.cpp)
target_link_libraries(google_tool glog::glog)

