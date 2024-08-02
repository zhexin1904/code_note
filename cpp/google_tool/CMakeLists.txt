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
        ${CMAKE_SOURCE_DIR}/include
        ${GLOG_INCLUDE_DIRS}
)

add_executable(google_example example/google_example.cpp)
target_link_libraries(google_example glog::glog)

add_library(${PROJECT_NAME}
        src/sample1.cpp
        )

target_link_libraries(${PROJECT_NAME}
        glog::glog
        )

############################### TESTS ##########################################
### Add testing
option(BUILD_DGP_TESTS "Build tests" ON)
if (BUILD_DGP_TESTS)

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/gtest.cmake googletest-download/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
            RESULT_VARIABLE result
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
    if (result)
        message(FATAL_ERROR "CMake step for googletest failed: ${result}")
    endif ()
    execute_process(COMMAND ${CMAKE_COMMAND} --build .
            RESULT_VARIABLE result
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
    if (result)
        message(FATAL_ERROR "Build step for googletest failed: ${result}")
    endif ()

    # Prevent overriding the parent project's compiler/linker
    # settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    # Add googletest directly to our build. This defines
    # the gtest and gtest_main targets.
    add_subdirectory("${CMAKE_BINARY_DIR}/external/googletest-src"
            "${CMAKE_BINARY_DIR}/external/googletest-build"
            EXCLUDE_FROM_ALL)

    # The gtest/gtest_main targets carry header search path
    # dependencies automatically when using CMake 2.8.11 or
    # later. Otherwise we have to add them here ourselves.
    if (CMAKE_VERSION VERSION_LESS 2.8.11)
        include_directories("${gtest_SOURCE_DIR}/include")
    endif ()

    add_executable(
            test_all_example
            test/test_example1.cpp
                )
    target_include_directories(test_all_example PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include>
            )
    target_link_libraries(
            test_all_example
            gtest_main
            ${PROJECT_NAME}
    )
    add_test(
            NAME test_all_example
            COMMAND ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
    )
endif (BUILD_DGP_TESTS)

