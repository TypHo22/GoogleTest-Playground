cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 11)

add_library(databaseConnectionLibrary IDatabaseConnection.cpp)
add_library(employeeManagerLibrary EmployeeManager.cpp)

set(ACTUAL_LIBRARIES databaseConnectionLibrary employeeManagerLibrary)

add_executable(MockingExample testRunner.cpp)
target_link_libraries(MockingExample
    gtest_main
    gmock_main
    pthread 
    ${ACTUAL_LIBRARIES})

