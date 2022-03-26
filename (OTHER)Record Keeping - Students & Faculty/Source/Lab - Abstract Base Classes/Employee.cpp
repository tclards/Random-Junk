#include "Employee.h"
#include <iostream>

void Employee::SetSalary(int input)
{
	salary = input;
}

void Employee::DisplayRecord()
{
	std::cout << "Employee: " << GetName() << std::endl;
	std::cout << "Salary: " << salary << std::endl;
}

Employee::Employee() : salary(0) //constructor
{

}

Employee::~Employee() //destructor
{
	Base::~Base();
}

Employee& Employee::operator=(Employee& _other) //assignment operator
{
	if (this != &_other)
	{
		this->SetName(_other.GetName());
		this->SetSalary(_other.salary);
	}

	return *this;
}

Employee::Employee(Employee& _other) : salary(0) //copy constructor
{
	if (this != &_other)
	{
		this->SetName(_other.GetName());
		this->SetSalary(_other.salary);
	}
}