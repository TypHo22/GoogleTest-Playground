add_executable(TestFixtures testFixtures.cpp inc/CodeUnderTest.cpp)
include_directories(inc)
target_link_libraries(TestFixtures gtest_main gmock_main)
