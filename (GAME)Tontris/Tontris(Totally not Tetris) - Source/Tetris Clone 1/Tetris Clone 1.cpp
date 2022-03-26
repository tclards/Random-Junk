// Tetris Clone 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <Windows.h>
using namespace std;

wstring tetromino[7];
int nFieldWidth = 12;
int nFieldHeight = 18;
unsigned char* pField = nullptr;

int nScreenWidth = 120;	//Console Screen Size X (columns)
int nScreenHeight = 30;	//Console Screen Size Y (rows)

// Functions:
#pragma region functions

int Rotate(int px, int py, int r)
{
	switch (r % 4)
	{
	case 0: return py * 4 + px;			// 0 degrees
	case 1: return 12 + py - (px * 4);	// 90 degrees
	case 2: return 15 - (py * 4) - px;	// 180 degrees
	case 3: return 3 - py + (px * 4);	// 270 degrees
	}
	return 0;
}

bool DoesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY)
{
	for (int px = 0; px < 4; px++)
	{
		for (int py = 0; py < 4; py++)
		{
			// Get index into piece
			int pi = Rotate(px, py, nRotation);

			// Get index into field
			int fi = (nPosY + py) * nFieldWidth + (nPosX + px);

			if (nPosX + px >= 0 && nPosX + px < nFieldWidth)
			{
				if (nPosY + py >= 0 && nPosY + py < nFieldHeight)
				{
					if (tetromino[nTetromino][pi] == L'X' && pField[fi] != 0)
					{
						return false; // Fail on first hit
					}
				}
			}

		}
	}

	return true;
}

#pragma endregion

int main()
{
	// assets:	
	// I
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");

	// Z
	tetromino[1].append(L"..X.");
	tetromino[1].append(L".XX.");
	tetromino[1].append(L".X..");
	tetromino[1].append(L"....");

	// S
	tetromino[2].append(L".X..");
	tetromino[2].append(L".XX.");
	tetromino[2].append(L"..X.");
	tetromino[2].append(L"....");

	// O
	tetromino[3].append(L"....");
	tetromino[3].append(L".XX.");
	tetromino[3].append(L".XX.");
	tetromino[3].append(L"....");

	// J
	tetromino[4].append(L"..X.");
	tetromino[4].append(L"..X.");
	tetromino[4].append(L".XX.");
	tetromino[4].append(L"....");

	// L
	tetromino[5].append(L".X..");
	tetromino[5].append(L".X..");
	tetromino[5].append(L".XX.");
	tetromino[5].append(L"....");

	// T
	tetromino[6].append(L"..X.");
	tetromino[6].append(L".XX.");
	tetromino[6].append(L"..X.");
	tetromino[6].append(L"....");

	// Create play field buffer
	pField = new unsigned char[nFieldWidth * nFieldHeight]; 
	for (int x = 0; x < nFieldWidth; x++)
	{
		for (int y = 0; y < nFieldHeight; y++)
		{
			pField[y * nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;
		}
	}

	// Code for using Console window as graphics panel
	wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
	for (int i = 0; i < nScreenWidth * nScreenHeight; i++)
	{
		screen[i] = L' ';
	}
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	// Game Logic
	bool bGameOver = false;

	int nCurrentPiece = 0;
	int nCurrentRotation = 0;
	int nCurrentX = nFieldWidth / 2;
	int nCurrentY = 0;

	bool bKey[4];
	bool bRotateHold = false;

	int nSpeed = 20;
	int nSpeedCounter = 0;
	bool bForceDown = false;
	int nPieceCounter = 0;
	int nScore = 0;

	vector<int> vLines;

	while (!bGameOver)
	{

		// Game Timing ============================================
		this_thread::sleep_for(chrono::milliseconds(50));
		nSpeedCounter++;
		bForceDown = (nSpeedCounter == nSpeed);

		// Input ==================================================
		for (int k = 0; k < 4; k++)
		{														  //R  L    D Z
			bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28Z"[k]))) != 0;
		}

		// Game Logic =============================================
		nCurrentX += (bKey[0] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX + 1, nCurrentY)) ? 1 : 0;
		nCurrentX -= (bKey[1] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX - 1, nCurrentY)) ? 1 : 0;
		nCurrentY += (bKey[2] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1)) ? 1 : 0;

		if (bKey[3])
		{
			nCurrentRotation += (!bRotateHold && DoesPieceFit(nCurrentPiece, nCurrentRotation + 1, nCurrentX, nCurrentY)) ? 1 : 0;
			bRotateHold = true;
		}
		else
		{
			bRotateHold = false;
		}

		if (bForceDown)
		{
			if (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1))
			{
				nCurrentY++; // on force down of current piece, does it fit? if so, do it.
			}
			else // if piece does not fit, lock in place and create new falling piece
			{
				// Lock current piece into the field
				for (int px = 0; px < 4; px++)
				{
					for (int py = 0; py < 4; py++)
					{
						if (tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] == L'X')
						{
							pField[(nCurrentY + py) * nFieldWidth + (nCurrentX + px)] = nCurrentPiece + 1;
						}
					}
				}

				nPieceCounter++;
				if (nPieceCounter % 10 == 0)
				{
					if (nSpeed >= 10) nSpeed--;
				}

				// check if full line has been created
				for (int py = 0; py < 4; py++)
				{
					if (nCurrentY + py < nFieldHeight - 1)
					{
						bool bLine = true;
						for (int px = 1; px < nFieldWidth - 1; px++)
						{
							bLine &= (pField[(nCurrentY + py) * nFieldWidth + px]) != 0;
						}

						if (bLine)
						{
							// remove line, set to '='
							for (int px = 1; px < nFieldWidth - 1; px++)
							{
								pField[(nCurrentY + py) * nFieldWidth + px] = 8;
							}

							vLines.push_back(nCurrentY + py);

						}
					}
				}

				nScore += 25;
				if (!vLines.empty())
				{
					nScore += (1 << vLines.size() - 1) * 100;
				}

				// choose next piece
				nCurrentX = nFieldWidth / 2;
				nCurrentY = 0;
				nCurrentRotation = 0;
				nCurrentPiece = rand() % 7;

				// if piece does not fit
				bGameOver = !DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY);
			}

			nSpeedCounter = 0;

		}

		// Render Output ==========================================


		// Draw Field
		for (int x = 0; x < nFieldWidth; x++)
		{
			for (int y = 0; y < nFieldHeight; y++)
			{
				//screen[(y + 2) * nScreenWidth + (x + 2)] = L" ABCDEFG=#"[pField[y * nFieldWidth + x]];

				screen[(y + 2) * nScreenWidth + (x + 2)] = L" \u2588\u2588\u2588\u2588\u2588\u2588\u2588=#"[pField[y * nFieldWidth + x]];
			}
		}

		// Draw Current Piece
		for (int px = 0; px < 4; px++)
		{
			for (int py = 0; py < 4; py++)
			{
				if (tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] == L'X')
				{
					//screen[(nCurrentY + py + 2) * nScreenWidth + (nCurrentX + px + 2)] = nCurrentPiece + 65;

					screen[(nCurrentY + py + 2) * nScreenWidth + (nCurrentX + px + 2)] = 9608; //unicode full block

				}
			}
		}

		// Draw Score
		swprintf_s(&screen[2 * nScreenWidth + nFieldHeight + 6], 16, L"SCORE: %8d", nScore);

		if (!vLines.empty())
		{
			// Display Frame (to draw lines being cleared)
			WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
			this_thread::sleep_for(chrono::milliseconds(400)); //delay a bit

			for (auto &v : vLines)
			{
				for (int px = 1; px < nFieldWidth - 1; px++)
				{
					for (int py = v; py > 0; py--)
					{
						pField[py * nFieldWidth + px] = pField[(py - 1) * nFieldWidth + px];
						pField[px] = 0;
					}
				}
			}

			vLines.clear();
		}

		// Display Frame
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
	}

	// Game over
	CloseHandle(hConsole);
	cout << "Game Over! Score: " << nScore << endl;
	system("pause");

	return 0;
}