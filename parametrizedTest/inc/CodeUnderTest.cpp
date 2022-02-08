#include "CodeUnderTest.h"

Validator::Validator(int low, int high) : low_{low}, high_{high}
{
}

bool Validator::inRange(int valueToTest) const
{
    return low_ <= valueToTest && valueToTest <= high_;
}
