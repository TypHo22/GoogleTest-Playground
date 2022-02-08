#include <gtest/gtest.h>

#include <stdexcept>
#include "CodeUnderTest.h"

/**
 * @brief GeneralException
 * We are expecting an exception of any kind
 */
TEST(TestSuiteSample, GeneralException)
{
    //Arrange
    int divisor = 0;
    int value = 9;
    //Act and Assert
    ASSERT_ANY_THROW(divide(value,divisor));//EXPECT_ANY_THROW(divide(value,divisor));
}

/**
 * @brief AssertSpecific
 * We are expecting an exception of type std::runtime_error
 */
TEST(TestSuiteSample, AssertSpecific)
{
    //Arrange
    int divisor = 0;
    int value = 9;
    //Act and Assert
    ASSERT_THROW(divide(value,divisor),std::runtime_error);//EXPECT_THROW(divide(value,divisor),std::runtime_error);
}

/**
 * @brief AssertNoThrow
 * We are expecting that now exception is thrown
 */
TEST(TestSuiteSample, AssertNoThrow)
{
    //Arrange
    int divisor = 3;
    int value = 9;
    //Act and Assert
    ASSERT_NO_THROW(divide(value,divisor));//EXPECT_NO_THROW(divide(value,divisor));
}

int main(int argc, char **argv)
{
 testing::InitGoogleTest(&argc, argv);
 return RUN_ALL_TESTS();
}
