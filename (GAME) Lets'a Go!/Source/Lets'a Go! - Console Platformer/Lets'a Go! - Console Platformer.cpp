#include <iostream>
#include <string>
#include "olcConsoleGameEngine.h"

using namespace std;

class Tclards_Platformer : public olcConsoleGameEngine
{
public:
	Tclards_Platformer()
	{
		m_sAppName = L"Lets'a Go!";
	}

private:
	// Level Storage
	wstring sLevel;
	int nLevelWidth;
	int nLevelHeight;

	// Player Properties
	float fPlayerPosX = 0.0f;
	float fPlayerPosY = 0.0f;
	float fPlayerVelX = 0.0f;
	float fPlayerVelY = 0.0f;
	bool bPlayerOnGround = false;

	// Camera Properties
	float fCameraPosX = 0.0f;
	float fCameraPosY = 0.0f;

	// Sprite Resources
	olcSprite *spriteTiles = nullptr;
	olcSprite *spriteMan = nullptr;

	// Sprite selection flags
	int nDirModX = 0;
	int nDirModY = 0;

protected:
	// Called by olcConsoleGameEngine
	virtual bool OnUserCreate()
	{
		nLevelWidth = 64;
		nLevelHeight = 16;
		sLevel += L"................................................................";
		sLevel += L"................................................................";
		sLevel += L".......ooooo....................................................";
		sLevel += L"........ooo.....................................................";
		sLevel += L".......................########.................................";
		sLevel += L".....BB?BBBB?BB.......###..............#.#......................";
		sLevel += L"....................###................#.#......................";
		sLevel += L"...................####.........................................";
		sLevel += L"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG.##############.....########";
		sLevel += L"...................................#.#...............###........";
		sLevel += L"........................############.#............###...........";
		sLevel += L"........................#............#.........###..............";
		sLevel += L"........................#.############......###.................";
		sLevel += L"........................#................###....................";
		sLevel += L"........................#################.......................";
		sLevel += L"................................................................";

		spriteTiles = new olcSprite(L"JarioSprites/leveljario.spr");
		spriteMan = new olcSprite(L"JarioSprites/minijario.spr");

		return true;
	}

	// Called by olcConsoleGameEngine
	virtual bool OnUserUpdate(float fElapsedTime)
	{
		// Utility Lambda Functions
		auto GetTile = [&](int x, int y)
		{
			if (x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight)
				return sLevel[y * nLevelWidth + x];
			else
				return L' ';
		};

		auto SetTile = [&](int x, int y, wchar_t c)
		{
			if (x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight)
				sLevel[y * nLevelWidth + x] = c;
		};

		// Handle Input
		if (IsFocused())
		{

			if (GetKey(VK_UP).bHeld)
			{
				fPlayerVelY = -6.0f;
			}

			if (GetKey(VK_DOWN).bHeld)
			{
				fPlayerVelY = 6.0f;
			}

			if (GetKey(VK_LEFT).bHeld)
			{
				fPlayerVelX += (bPlayerOnGround ? -25.0f : -15.0f) * fElapsedTime;
				nDirModY = 1;
			}

			if (GetKey(VK_RIGHT).bHeld)
			{
				fPlayerVelX += (bPlayerOnGround ? 25.0f : 15.0f) * fElapsedTime;
				nDirModY = 0;
			}

			if (GetKey(VK_SPACE).bPressed)
			{
				if (fPlayerVelY == 0)
				{
					fPlayerVelY = -12.0f;
					nDirModX = 1;
				}
			}
		}

		// Gravity
		fPlayerVelY += 20.0f * fElapsedTime;

		// Drag
		if (bPlayerOnGround)
		{
			fPlayerVelX += -3.0f * fPlayerVelX * fElapsedTime;
			if (fabs(fPlayerVelX) < 0.01f)
				fPlayerVelX = 0.0f;
		}

		// Clamp velocities
		if (fPlayerVelX > 10.0f)
			fPlayerVelX = 10.0f;

		if (fPlayerVelX < -10.0f)
			fPlayerVelX = -10.0f;

		if (fPlayerVelY > 100.0f)
			fPlayerVelY = 100.0f;

		if (fPlayerVelY < -100.0f)
			fPlayerVelY = -100.0f;


		float fNewPlayerPosX = fPlayerPosX + fPlayerVelX * fElapsedTime;
		float fNewPlayerPosY = fPlayerPosY + fPlayerVelY * fElapsedTime;

		// Check for pickups
		if (GetTile(fNewPlayerPosX + 0.0f, fNewPlayerPosY + 0.0f) == L'o')
			SetTile(fNewPlayerPosX + 0.0f, fNewPlayerPosY + 0.0f, L'.');

		if (GetTile(fNewPlayerPosX + 0.0f, fNewPlayerPosY + 1.0f) == L'o')
			SetTile(fNewPlayerPosX + 0.0f, fNewPlayerPosY + 1.0f, L'.');

		if (GetTile(fNewPlayerPosX + 1.0f, fNewPlayerPosY + 0.0f) == L'o')
			SetTile(fNewPlayerPosX + 1.0f, fNewPlayerPosY + 0.0f, L'.');

		if (GetTile(fNewPlayerPosX + 1.0f, fNewPlayerPosY + 1.0f) == L'o')
			SetTile(fNewPlayerPosX + 1.0f, fNewPlayerPosY + 1.0f, L'.');

		// Collision
		if (fPlayerVelX <= 0) // Moving Left
		{
			if (GetTile(fNewPlayerPosX + 0.0f, fPlayerPosY + 0.0f) != L'.' || GetTile(fNewPlayerPosX + 0.0f, fPlayerPosY + 0.9f) != L'.')
			{
				fNewPlayerPosX = (int)fNewPlayerPosX + 1;
				fPlayerVelX = 0;
			}
		}
		else // Moving Right
		{
			if (GetTile(fNewPlayerPosX + 1.0f, fPlayerPosY + 0.0f) != L'.' || GetTile(fNewPlayerPosX + 1.0f, fPlayerPosY + 0.9f) != L'.')
			{
				fNewPlayerPosX = (int)fNewPlayerPosX;
				fPlayerVelX = 0;
			}
		}

		bPlayerOnGround = false;
		if (fPlayerVelY <= 0) // Moving Up
		{
			if (GetTile(fNewPlayerPosX + 0.0f, fNewPlayerPosY) != L'.' || GetTile(fNewPlayerPosX + 0.9f, fNewPlayerPosY) != L'.')
			{
				fNewPlayerPosY = (int)fNewPlayerPosY + 1;
				fPlayerVelY = 0;
			}
		}
		else // Moving Down
		{
			if (GetTile(fNewPlayerPosX + 0.0f, fNewPlayerPosY + 1.0f) != L'.' || GetTile(fNewPlayerPosX + 0.9f, fNewPlayerPosY + 1.0f) != L'.')
			{
				fNewPlayerPosY = (int)fNewPlayerPosY;
				fPlayerVelY = 0;
				bPlayerOnGround = true;
				nDirModX = 0;
			}
		}

		// Update player position once collision detection has been resolved
		fPlayerPosX = fNewPlayerPosX;
		fPlayerPosY = fNewPlayerPosY;

		// Link camera to player position
		fCameraPosX = fPlayerPosX;
		fCameraPosY = fPlayerPosY;

		// Draw Level
		int nTileWidth = 16; 
		int nTileHeight = 16; 
		int nVisibleTilesX = ScreenWidth() / nTileWidth;
		int nVisibleTilesY = ScreenHeight() / nTileHeight;

		// Calculate Top-Leftmost visible tile
		float fOffsetX = fCameraPosX - (float)nVisibleTilesX / 2.0f;
		float fOffsetY = fCameraPosY - (float)nVisibleTilesY / 2.0f;

		// Clamp camera to game boundaries
		if (fOffsetX < 0) fOffsetX = 0;
		if (fOffsetY < 0) fOffsetY = 0;
		if (fOffsetX > nLevelWidth - nVisibleTilesX) fOffsetX = nLevelWidth - nVisibleTilesX;
		if (fOffsetY > nLevelHeight - nVisibleTilesY) fOffsetY = nLevelHeight - nVisibleTilesY;

		// Get offsets for smooth movement
		float fTileOffsetX = (fOffsetX - (int)fOffsetX) * nTileWidth;
		float fTileOffsetY = (fOffsetY - (int)fOffsetY) * nTileHeight;

		// Draw visible tile map
		for (int x = -1; x < nVisibleTilesX + 1; x++)
		{
			for (int y = -1; y < nVisibleTilesY + 1; y++)
			{
				wchar_t sTileID = GetTile(x + fOffsetX, y + fOffsetY);
				switch (sTileID)
				{
				case L'.': // Sky
					Fill(x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY, (x + 1) * nTileWidth - fTileOffsetX, (y + 1) * nTileHeight - fTileOffsetY, PIXEL_SOLID, FG_CYAN);
					break;
				case L'#': // Solid Block
					DrawPartialSprite(x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY, spriteTiles, 2 * nTileWidth, 0 * nTileHeight, nTileWidth, nTileHeight);
					break;
				case L'G': // Ground Block
					DrawPartialSprite(x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY, spriteTiles, 0 * nTileWidth, 0 * nTileHeight, nTileWidth, nTileHeight);
					break;
				case L'B': // Brick Block
					DrawPartialSprite(x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY, spriteTiles, 0 * nTileWidth, 1 * nTileHeight, nTileWidth, nTileHeight);
					break;
				case L'?': // Question Block
					DrawPartialSprite(x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY, spriteTiles, 1 * nTileWidth, 1 * nTileHeight, nTileWidth, nTileHeight);
					break;
				case L'o': // Coin
					Fill(x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY, (x + 1) * nTileWidth - fTileOffsetX, (y + 1) * nTileHeight - fTileOffsetY, PIXEL_SOLID, FG_CYAN);
					DrawPartialSprite(x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY, spriteTiles, 3 * nTileWidth, 0 * nTileHeight, nTileWidth, nTileHeight);
					break;
				default:
					Fill(x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY, (x + 1) * nTileWidth - fTileOffsetX, (y + 1) * nTileHeight - fTileOffsetY, PIXEL_SOLID, FG_BLACK);
					break;
				}
			}
		}

		// Draw Player
		DrawPartialSprite((fPlayerPosX - fOffsetX) * nTileWidth, (fPlayerPosY - fOffsetY) * nTileWidth, spriteMan, nDirModX * nTileWidth, nDirModY * nTileHeight, nTileWidth, nTileHeight);

		return true;
	}


};

int main()
{
	/*HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_SHOWMAXIMIZED);*/

	// Use olcConsoleGameEngine derived app
	Tclards_Platformer game;

	// Create a console with resolution 160x100 characters
	// Each character occupies 8x8 pixels
	game.ConstructConsole(256, 100, 4, 4);

	// Start the engine!
	game.Start();

	return 0;
}