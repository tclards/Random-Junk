#pragma once
#include "BaseAccount.h"
class SavingsAccount :
    public BaseAccount
{
public:
    bool overWithdrawals = false;

    SavingsAccount();

    virtual void Withdraw(float amt); //SavingsAccount does not allow more than 3 withdrawals
};

