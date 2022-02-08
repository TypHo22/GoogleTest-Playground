#include<iostream>
#include <gtest/gtest.h>

TEST(TestSuiteSample, TestSample)
{
  int s = 2 + 2;
  ASSERT_EQ(4, 4);
}

int main(int argc, char **argv)
{
 testing::InitGoogleTest(&argc, argv);
 return RUN_ALL_TESTS();
 //std::cout<<"HELLO"<<std::endl;
 return 0;
}
