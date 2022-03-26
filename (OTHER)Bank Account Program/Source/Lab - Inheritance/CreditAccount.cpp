#include "CreditAccount.h"

CreditAccount::CreditAccount()
{

}

void CreditAccount::Withdraw(float amt)
{
	if (amt > 40)
	{
		BaseAccount::Withdraw(5000);
	}
	BaseAccount::Withdraw(amt);
}