#include <gtest/gtest.h>
#include "CodeUnderTest.h"

TEST(TestSuiteSample, AssertOnString)
{
    //Arrange
    char inputString[] = "Hello World";
    //Act
    toUpper(inputString);
    //Assert
    EXPECT_STREQ("HELLO WORLD",inputString); //ASSERT_STREQ("HELLO WORLD", inputString);
}

int main(int argc, char **argv)
{
 testing::InitGoogleTest(&argc, argv);
 return RUN_ALL_TESTS();
}
