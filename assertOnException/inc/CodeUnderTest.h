#pragma once
#include <stdexcept>

float divide(int value, int divisor)
{
    if(divisor == 0)
    {
        throw std::runtime_error("Divisor 0 is unspecific");
    }

    return value / divisor;
}
