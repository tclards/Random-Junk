#pragma once
#include "BaseAccount.h"
class CreditAccount :
    public BaseAccount
{
public:

    CreditAccount();

    virtual void Withdraw(float amt);
};

