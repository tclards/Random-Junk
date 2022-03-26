#pragma once
#include "BaseAccount.h"
class CheckingAccount :
    public BaseAccount
{
public:

    CheckingAccount();

    virtual void Withdraw(float amt); //if more than 10 withdrawals, 5 dollar fee charged
};

