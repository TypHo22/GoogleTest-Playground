add_executable(ParametrizedTest parametrizedTest.cpp inc/CodeUnderTest.cpp)
include_directories(inc)
target_link_libraries(ParametrizedTest gtest_main gmock_main)
