#pragma once

class Account
{
public:
    Account();
    void deposit(double sum);
    void withdrawal(double sum);
    double getBalance() const;
    void transfer(Account& to, double sum);
private:
    double balance_;
};

