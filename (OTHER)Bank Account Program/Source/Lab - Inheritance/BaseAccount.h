#pragma once
class BaseAccount
{
protected:

	float accBalance;
	int withdrawals;

public:

	BaseAccount();

	virtual void Withdraw(float amt);

	void Deposit(float amt);

	float GetBalance() const { return accBalance; }
};

