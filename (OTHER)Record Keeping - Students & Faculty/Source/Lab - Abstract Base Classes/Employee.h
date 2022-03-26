#pragma once
#include "Base.h"
class Employee :
    public Base
{
private:
    int salary;

public:
    void SetSalary(int input);

    virtual void DisplayRecord();

    Employee(); //constructor
    ~Employee(); //deconstructor
    Employee& operator=(Employee& _other); //assignment operator
    Employee(Employee& _other); //copy constructor


};

