//Lab - Bit Manipulation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdlib.h>

//declarations
#pragma region Declarations
void TurnOn(int bit);
void TurnOff(int bit);
void Toggle(int bit);
void Negate();
void LeftShift();
void RightShift();

int IntInputValidation();
void printBinaryNumber(unsigned int bitField, int size);
#pragma endregion

unsigned int bitField = 19;

int main()
{
	printBinaryNumber(bitField, 32);

	int bit;
	bool valid = false;
	int userChoice;

	while (valid == false)
	{
		std::cout << "\nTurnOn = 1, TurnOff = 2, Toggle = 3, Negate = 4, Left Shift = 5, RightShift = 6, Exit = 7";
		userChoice = IntInputValidation();

		if (userChoice > 8)
		{
			"\nInvalid Input. \n";
		}
		else if (userChoice == 0)
		{
			"\nInvalid Input. \n";
		}

		switch (userChoice)
		{
		case 1:
			std::cout << "\nChoose bit Index(0 to 32).";
			bit = IntInputValidation();
			TurnOn(bit);
			system("CLS");
			printBinaryNumber(bitField, 32);
			break;
		case 2:
			std::cout << "\nChoose bit Index(0 to 32).";
			bit = IntInputValidation();
			TurnOff(bit);
			system("CLS");
			printBinaryNumber(bitField, 32);
			break;
		case 3:
			std::cout << "\nChoose bit Index(0 to 32).";
			bit = IntInputValidation();
			Toggle(bit);
			system("CLS");
			printBinaryNumber(bitField, 32);
			break;
		case 4:
			Negate();
			system("CLS");
			printBinaryNumber(bitField, 32);
			break;
		case 5:
			LeftShift();
			system("CLS");
			printBinaryNumber(bitField, 32);
			break;
		case 6:
			RightShift();
			system("CLS");
			printBinaryNumber(bitField, 32);
			break;
		case 7:
			valid = true;
			break;
		}
	}

	//std::cout << "\n";
	//system("pause");
}

//functions
#pragma region Functions

void TurnOn(int bit)
{
	bitField = bitField | 1 << bit;
}

void TurnOff(int bit)
{
	bitField = bitField & ~1 << bit;
}

void Toggle(int bit)
{
	bitField = bitField ^ 1 << bit;
}

void Negate()
{
	bitField = ~bitField;
}

void LeftShift()
{
	bitField = bitField << 1;
}

void RightShift()
{
	bitField = bitField >> 1;
}

int IntInputValidation()
{
	int input;

	while (true)
	{
		std::cout << "\nInput: ";
		std::cin >> input;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "\nInvalid Input. \n";
		}
		else
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			break;
		}
	}

	return input;
}

void printBinaryNumber(unsigned int bitField, int size)
{
	char* text = new char[size + 1];
	text[size] = '\0';

	std::cout << "bitField: " << bitField << std::endl;

	for (int i = size - 1; i >= 0; i--)
	{
		if (bitField % 2 == 0)
		{
			text[i] = '0';
		}
		else
		{
			text[i] = '1';
		}
		bitField = bitField / 2;
	}

	std::cout << "\n" << text << std::endl;
	delete[] text;
}
#pragma endregion