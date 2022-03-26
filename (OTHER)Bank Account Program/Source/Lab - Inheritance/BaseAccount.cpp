#include "BaseAccount.h"

BaseAccount::BaseAccount() : accBalance(0), withdrawals(0) //constructor
{

}

void BaseAccount::Deposit(float amt)
{
	accBalance += amt;
}

void BaseAccount::Withdraw(float amt)
{
	accBalance -= amt;
	withdrawals += 1;
}