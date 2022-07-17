// Written by Tyler Clardy (github @ tclards) on 7/17/2022

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ROCKPAPERSCISSORS
{
    class Program
    {
        static void Main(string[] args)
        {
            string sPlayerInput;
            string sComputerInput;

            bool bValidInput = false;
            bool bPlayerWin = false;
            bool bPlayerTied = false;
            bool bKeepPlaying = true;

            int iRandomRoll;

            do //Main Game Loop
            {
                // reset game variables at start of game loop
                bValidInput = false;
                bPlayerWin = false;
                bPlayerTied = false;
                bKeepPlaying = true;

                do // Player input loop
                {
                    Console.Clear();
                    
                    Console.WriteLine("\n------------------------------------------------------------------------------------"); // Divider Line

                    Console.WriteLine("\nChoose an option below" + "\n\nA) Rock" + "\n\nB) Paper" + "\n\nC) Scissors");

                    Console.WriteLine("\n------------------------------------------------------------------------------------"); // Divider Line

                    Console.Write("\nPlayer Input: ");

                    // player input
                    sPlayerInput = Console.ReadLine();

                    Console.WriteLine("\n------------------------------------------------------------------------------------"); // Divider Line

                    // Player Input Processing
                    if (sPlayerInput == "A")
                    {
                        sPlayerInput = "Rock";
                        Console.WriteLine("\nPlayer chose Rock");
                        bValidInput = true;
                    }
                    else if (sPlayerInput == "B")
                    {
                        sPlayerInput = "Paper";
                        Console.WriteLine("\nPlayer chose Paper");
                        bValidInput = true;
                    }
                    else if (sPlayerInput == "C")
                    {
                        sPlayerInput = "Scissors";
                        Console.WriteLine("\nPlayer chose Scissors");
                        bValidInput = true;
                    }
                    else
                    {
                        Console.WriteLine("\n\nInvalid Input - Press Any Key to Try Again.");
                        Console.ReadKey();
                    }
                } while (!bValidInput);

                // computer input
                Random rand = new Random();
                iRandomRoll = rand.Next(1, 4);

                // process computer input and display results
                switch (iRandomRoll)
                {
                    case 1:
                        sComputerInput = "Rock";
                        Console.WriteLine("\n\nComputer chose Rock");
                        if (sPlayerInput == "Rock")
                        {
                            bPlayerWin = false;
                            bPlayerTied = true;
                        }
                        else if (sPlayerInput == "Paper")
                        {
                            bPlayerWin = true;
                        }
                        else if (sPlayerInput == "Scissors")
                        {
                            bPlayerWin = false;
                        }
                        break;
                    case 2:
                        sComputerInput = "Paper";
                        Console.WriteLine("\n\nComputer chose Paper");
                        if (sPlayerInput == "Rock")
                        {
                            bPlayerWin = false;
                        }
                        else if (sPlayerInput == "Paper")
                        {
                            bPlayerWin = false;
                            bPlayerTied = true;
                        }
                        else if (sPlayerInput == "Scissors")
                        {
                            bPlayerWin = true;
                        }
                        break;
                    case 3:
                        sComputerInput = "Scissors";
                        Console.WriteLine("\n\nComputer chose Scissors");
                        if (sPlayerInput == "Rock")
                        {
                            bPlayerWin = true;
                        }
                        else if (sPlayerInput == "Paper")
                        {
                            bPlayerWin = false;
                        }
                        else if (sPlayerInput == "Scissors")
                        {
                            bPlayerWin = false;
                            bPlayerTied = true;
                        }
                        break;
                    default:
                        Console.WriteLine("\n\nInvalid Entry");
                        break;
                }

                Console.WriteLine("\n------------------------------------------------------------------------------------"); // Divider Line

                // End Game
                if (bPlayerTied == true)
                {
                    Console.WriteLine("\n\nYou Tied!");
                }
                else if (bPlayerTied == false)
                {
                    if (bPlayerWin == true)
                    {
                        Console.WriteLine("\n\nYou Win! :D");
                    }
                    else if (bPlayerWin == false)
                    {
                        Console.WriteLine("\n\nYou Lose. :(");
                    }
                    else
                    {
                        Console.WriteLine("\n\nERROR");
                    }
                }

                Console.WriteLine("\n\nPress any key if you would like to play again.");
                Console.ReadKey();
            } while (bKeepPlaying);
        }
    }
}