#pragma once
#include "Base.h"
class Student :
    public Base
{
private:
    float GPA;

public:
    void SetGPA(float input);

    virtual void DisplayRecord();

    Student(); //constructor
    ~Student(); //deconstructor
    Student& operator=(Student& _other); //assignment operator
    Student(Student& _other); //copy constructor

};

