#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "CodeUnderTest.h"

//we expect our vector to have certain values
TEST(VectorToTests, ElementsAreTest)
{
    std::vector<int> v = generateNumbers(5, 3);
    //0, 1, 2, 0, 1
    ASSERT_THAT(v, testing::ElementsAre(0, 1, 2, 0, 1));
}

TEST(VectorToTests, RangeTest)
{
    using namespace testing;

    std::vector<int> v = generateNumbers(5, 3);
    //0, 1, 2, 0, 1
    ASSERT_THAT(v, Each(AllOf(Ge(0),Lt(3))));
}

int main(int argc, char **argv)
{
 testing::InitGoogleTest(&argc, argv);
 return RUN_ALL_TESTS();
}
