#pragma once

/**
 * @brief The Validator class
 * check if a value is in range between a lower and a higher value
 */
class Validator
{
public:
    Validator(int low, int high);
    bool inRange(int valueToTest) const;
private:
    int low_, high_;
};
