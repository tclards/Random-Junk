#pragma once
class Base
{
private:
	char* name;

public:

	Base(); //constructor
	~Base(); //deconstructor
	Base& operator=(Base & _other); //assignment operator
	Base(Base& _other); //copy constructor

	void SetName(const char* input); //setter

	const char* GetName() const { return name; } //getter

	virtual void DisplayRecord() = 0;

};

