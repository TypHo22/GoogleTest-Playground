#include "CodeUnderTest.h"
#include <stdexcept>

Account::Account() : balance_(0)
{

}

void Account::deposit(double sum)
{
    balance_ += sum;
}

void Account::withdrawal(double sum)
{
    if(sum > balance_)
        throw std::runtime_error("Insufficient funds");
    balance_ -= sum;
}

double Account::getBalance() const
{
    return balance_;
}

void Account::transfer(Account& to, double sum)
{
    withdrawal(sum);
    to.deposit(sum);
}
