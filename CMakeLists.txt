cmake_minimum_required(VERSION 3.5)

project(Playground LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} main.cpp)
add_subdirectory(assertOnException)
add_subdirectory(assertOnString)
add_subdirectory(assertOnVectors)
add_subdirectory(testFixtures)
add_subdirectory(parametrizedTest)
add_subdirectory(mockingExample)
## add google test
#get googletest
include(FetchContent)
FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG release-1.11.0)
FetchContent_GetProperties(googletest)
#googletest_POPULATED
#googletest_SOURCE_DIR
#googletest_BUILD_DIR
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BUILD_DIR})
endif()

target_link_libraries(${PROJECT_NAME} gtest_main gmock_main)

