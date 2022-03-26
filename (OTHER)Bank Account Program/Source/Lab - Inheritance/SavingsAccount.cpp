#include "SavingsAccount.h"

SavingsAccount::SavingsAccount()
{

}

void SavingsAccount::Withdraw(float amt) //SavingsAccount does not allow more than 3 withdrawals
{
	if (SavingsAccount::withdrawals < 3)
	{
		BaseAccount::Withdraw(amt);
	}
	else
	{
		overWithdrawals = true;
	}
}