#include "CheckingAccount.h"

CheckingAccount::CheckingAccount()
{

}

void CheckingAccount::Withdraw(float amt) //if more than 10 withdrawals, 5 dollar fee charged
{
	if (CheckingAccount::withdrawals > 10)
	{
		CheckingAccount::accBalance -= (float)5;
	}
	BaseAccount::Withdraw(amt);
}