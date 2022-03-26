#include "Base.h"
#include <iostream>

void Base::SetName(const char* input) //setter
{
	delete[] name; //delete name if already existing

	size_t len = strlen(input) + 1; //account for null temrinator
	name = new char[len]; //allocate space and create new name
	strcpy_s(name, len, input); //copy input to name
}

Base::Base() : name(nullptr) //constructor
{

}

Base::~Base() //destructor
{
	/*delete[] this->name;
	this->name = nullptr;*/
}

Base& Base::operator=(Base& _other) //assignment operator
{
	if (this != &_other)
	{
		SetName(_other.name);
	}

	return *this;
}

Base::Base(Base& _other) //copy constructor
{
	SetName(_other.name);
}