// Lab - Inheritance.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "CheckingAccount.h"
#include "CreditAccount.h"
#include "SavingsAccount.h"

int main()
{
    CheckingAccount* Checking = new CheckingAccount;
    SavingsAccount* Saving = new SavingsAccount;
    CreditAccount* Credit = new CreditAccount;

    std::ifstream ifs("accBalances.txt");

    if (ifs.is_open())
    {
        float checkData;
        float saveData;
        float credData;

        ifs >> checkData >> saveData >> credData;

        Checking->Deposit(checkData);
        Saving->Deposit(saveData);
        Credit->Deposit(credData);
    }
    else
    {
        Checking->Deposit(1000);
        Saving->Deposit(750);
        Credit->Deposit(250);
    }

    //menu loop:
    bool looping = true;
    while (looping == true)
    {
        int acc;
        int choice;
        float checkingTemp = Checking->GetBalance();
        float SavingTemp = Saving->GetBalance();
        float creditTemp = Credit->GetBalance();

        system("CLS");
        std::cout << "Account Home\n---------------------------\nPlease make a selection:" << std::endl;
        std::cout << "1. Get Balance\n2. Withdrawal\n3. Deposit\n4. Rules\n5. Exit" << std::endl;
        std::cin >> choice;

        switch (choice)
        {
        case 1: //Get Balance
            system("CLS");
            std::cout << "Choose account:\n---------------------------\n" << std::endl;
            std::cout << "1. Checkings\n2. Savings\n3. Credit" << std::endl;
            std::cin >> acc;
            switch (acc)
            {
            case 1:
                std::cout << "Checking Account Balance: " << checkingTemp << std::endl;
                std::cout << "\n";
                system("pause");
                break;
            case 2:
                std::cout << "Savings Account Balance: " << SavingTemp << std::endl;
                std::cout << "\n";
                system("pause");
                break;
            case 3:
                std::cout << "Credit Account Balance: " << creditTemp << std::endl;
                std::cout << "\n";
                system("pause");
                break;
            default:
                std::cout << "Invalid Selection!" << std::endl;
                std::cout << "\n";
                system("pause");
                system("CLS");
                break;
            }
            break;
        case 2: //Withdrawals
            system("CLS");
            std::cout << "Choose account:" << std::endl;
            std::cout << "1. Checkings\n2. Savings\n3. Credit" << std::endl;
            std::cin >> acc;
            std::cout << "Enter withdrawal amount: " << std::endl;
            float amt;
            std::cin >> amt;
            switch (acc)
            {
            case 1:
                Checking->Withdraw(amt);
                std::cout << amt << " withdrawn from Checkings!" << std::endl;
                std::cout << "\n";
                system("pause");
                system("CLS");
                break;
            case 2:
                Saving->Withdraw(amt);
                if (Saving->overWithdrawals == true)
                {
                    std::cout << "\nWithdrawal failed! Too many withdrawals." << std::endl;
                    std::cout << "\n";
                    system("pause");
                    system("CLS");
                    break;
                }
                std::cout << amt << " withdrawn from Savings!" << std::endl;
                std::cout << "\n";
                system("pause");
                system("CLS");
                break;
            case 3:
                Credit->Withdraw(amt);
                if (amt > 40)
                {
                    std::cout << "WARNING: Over spending limit. Fee imposed.\n" << std::endl;
                }
                std::cout << amt << " withdrawn from Credit!" << std::endl;
                std::cout << "\n";
                system("pause");
                system("CLS");
                break;
            default:
                std::cout << "Invalid Selection!" << std::endl;
                std::cout << "\n";
                system("pause");
                system("CLS");
                break;
            }
            break;
        case 3: //Deposits
            system("CLS");
            std::cout << "Choose account:" << std::endl;
            std::cout << "1. Checkings\n2. Savings\n3. Credit" << std::endl;
            std::cin >> acc;
            std::cout << "Enter deposit amount" << std::endl;
            float depoAmt;
            std::cin >> depoAmt;
            switch (acc)
            {
            case 1:
                Checking->Deposit(depoAmt);
                std::cout << depoAmt << " deposited into Checkings!" << std::endl;
                std::cout << "\n";
                system("pause");
                system("CLS");
                break;
            case 2:
                Saving->Deposit(depoAmt);
                std::cout << depoAmt << " deposited into Savings!" << std::endl;
                std::cout << "\n";
                system("pause");
                system("CLS");
                break;
            case 3:
                Credit->Deposit(depoAmt);
                std::cout << depoAmt << " deposited into Credit!" << std::endl;
                std::cout << "\n";
                system("pause");
                system("CLS");
                break;
            default:
                std::cout << "Invalid Selection!" << std::endl;
                std::cout << "\n";
                system("pause");
                system("CLS");
                break;
            }
            break;
        case 4: //rules
            system("CLS");
            std::cout << "Rules\n---------------------------\n1. Checking applies $5 fee if more than 10 withdrawals are made.\n2. Savings does not allow more than 3 withdrawals.\n3. Credit has a $40 withdrawal limit with a $5000 fee if rule is broken." << std::endl;
            std::cout << "\n";
            system("pause");
            system("CLS");
            break;
        case 5: //exit
            std::cout << "\nGoodbye!" << std::endl;
            looping = false;
            break;
        default:
            std::cout << "Invalid Selection!" << std::endl;
            system("CLS");
            break;
        }
    }

    float check = Checking->GetBalance();
    float save = Saving->GetBalance();
    float cred = Credit->GetBalance();

    std::ofstream myFile;
    myFile.open("accBalances.txt");
    myFile << check << "\n";
    myFile << save << "\n";
    myFile << cred << "\n";
    myFile.close();

    delete Checking;
    delete Saving;
    delete Credit;
}