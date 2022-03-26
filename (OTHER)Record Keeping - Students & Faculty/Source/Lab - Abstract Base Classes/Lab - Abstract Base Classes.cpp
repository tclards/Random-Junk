// Lab - Abstract Base Classes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//todo: fix crash on exit

#include <iostream>
#include <vector>
#include "Base.h"
#include "Employee.h"
#include "Student.h"

//functions:
void ClearInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');
}

void AddRecord(std::vector<Base*>& v)
{
    bool selectionLoop = true;

    while (selectionLoop == true)
    {
        system("CLS");
        std::cout << "What would you like to add?: " << std::endl;
        std::cout << "1. Student\n2. Employee" << std::endl;
        int input;
        std::cin >> input;
        ClearInputBuffer();

        Employee* tempEmployee = new Employee;
        char* tempEmpName = new char[CHAR_MAX];
        int tempSalary;

        Student* tempStudent = new Student;
        char* tempStuName = new char[CHAR_MAX];
        float tempGPA;

        switch (input)
        {
        case 1: //add student
            system("CLS");
            std::cout << "ADD STUDENT\n-----------------------" << std::endl;
            std::cout << "Enter student name: " << std::endl;
            std::cin >> tempStuName;
            ClearInputBuffer();
            std::cout << "\nEnter student GPA: " << std::endl;
            std::cin >> tempGPA;
            ClearInputBuffer();

            tempStudent->SetName(tempStuName);
            tempStudent->SetGPA(tempGPA);

            v.push_back(tempStudent);

            std::cout << "\nStudent added successfully!" << std::endl;
            selectionLoop = false;
            system("pause");
            system("CLS");
            break;

        case 2: //add employee
            system("CLS");
            std::cout << "ADD EMPLOYEE\n-----------------------" << std::endl;
            std::cout << "Enter employee name: " << std::endl;
            std::cin >> tempEmpName;
            ClearInputBuffer();
            std::cout << "\nEnter employee salary: " << std::endl;
            std::cin >> tempSalary;
            ClearInputBuffer();

            tempEmployee->SetName(tempEmpName);
            tempEmployee->SetSalary(tempSalary);

            v.push_back(tempEmployee);

            std::cout << "\nEmployee added successfully!" << std::endl;
            selectionLoop = false;
            system("pause");
            system("CLS");
            break;

        default:
            std::cout << "\nInvalid choice!" << std::endl;
            system("pause");
            system("CLS");
            break;
        }

        //delete tempStudent;
        //delete[] tempStuName;
        /*delete tempGPA;*/

        //delete tempEmployee;
        //delete[] tempEmpName;
        /*delete tempSalary;*/
    }
}

void DisplayRecords(std::vector<Base*>& v)
{
    system("CLS");
    std::cout << "ALL RECORDS\n-----------------------" << std::endl;

    for (size_t i = 0; i < v.size(); i++)
    {
        std::cout << "\n" << (i+1) << ": " << std::endl;
        v[i]->DisplayRecord();
        std::cout << "\n";
    }

    system("pause");
}

void DuplicateRecord(std::vector<Base*>& v)
{
    bool indexLoop = true;

    while (indexLoop == true)
    {
        system("CLS");
        std::cout << "DUPLICATE RECORD\n-----------------------" << std::endl;
        std::cout << "Please enter the integer index(Display Records index - 1) for the record to be duplicated: " << std::endl;
        int index;
        std::cin >> index;
        ClearInputBuffer();

        if (index < 0 || index > (int)v.size())
        {
            std::cout << "Invalid index! Please try again." << std::endl;
            system("pause");
            system("CLS");
            indexLoop = false;
            break;
        }
        /*else if (index < 0)
        {
            std::cout << "Invalid index! Please try again." << std::endl;
            system("pause");
            system("CLS");
        }*/
        else
        {
            Base* b1 = v[index];

            //student dynamic_cast        
            Student* stuTest = dynamic_cast<Student*>(b1);

            if (stuTest != NULL)
            {
                Student* DupelicateStu = new Student(*stuTest);
                v.push_back(DupelicateStu);

                std::cout << "Record duplicated successfully!" << std::endl;
                system("pause");
                system("CLS");
                indexLoop = false;
                break;
            }

            //employee dynamic_cast
            Employee* empTest = dynamic_cast<Employee*>(b1);

            if (empTest != NULL)
            {
                Employee* DupelicateEmp = new Employee(*empTest);
                v.push_back(empTest);

                std::cout << "Record duplicated successfully!" << std::endl;
                system("pause");
                system("CLS");
                indexLoop = false;
                break;
            }

            delete stuTest;
            delete empTest;

        }
    }
}

int main()
{
    std::vector<Base*> v;

    //menu loop
    bool looping = true;
    int choice;
    while (looping == true)
    {
        system("CLS");
        std::cout << "MAIN MENU\n-----------------------" << std::endl;
        std::cout << "Please make a selection: " << std::endl;
        std::cout << "1. Add a record\n2. Display all records\n3. Duplicate a record\n4. Exit" << std::endl;
        std::cin >> choice;
        ClearInputBuffer();

        switch (choice)
        {
        case 1: //add record
            AddRecord(v);
            break;
        case 2: //display all records
            DisplayRecords(v);
            break;
        case 3: //duplicate record
            DuplicateRecord(v);
            break;
        case 4: //exit
            std::cout << "\nThank you. Goodbye!" << std::endl;
            looping = false;
            system("pause");
            system("CLS");
            break;
        default:
            std::cout << "\nInvalid choice!" << std::endl;
            system("pause");
            system("CLS");
            break;
        }
    }

    //deleting all records in vector:
    for (size_t i = 0; i < v.size(); i++)
    {
        delete v[i];
    }

}