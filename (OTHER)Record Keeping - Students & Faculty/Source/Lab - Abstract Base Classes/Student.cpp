#include "Student.h"
#include <iostream>

void Student::SetGPA(float input)
{
	GPA = input;
}

void Student::DisplayRecord()
{
	std::cout << "Student: " << GetName() << std::endl;
	std::cout << "GPA: " << GPA << std::endl;
}

Student::Student() : GPA(0) //constructor
{

}

Student::~Student() //destructor
{
	Base::~Base();
}

Student& Student::operator=(Student & _student) //assignment operator
{
	if (this != &_student)
	{
		this->SetName(_student.GetName());
		this->SetGPA(_student.GPA);
	}

	return *this;
}

Student::Student(Student& _student) : GPA((float)0) //copy constructor
{
	/*SetName(nullptr);
	SetGPA(0);*/

	if (this != &_student)
	{
		this->SetName(_student.GetName());
		this->SetGPA(_student.GPA);
	}
}