#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

#include "olcConsoleGameEngine.h"

class Tclards_PerlinNoise : public olcConsoleGameEngine
{

public:

    Tclards_PerlinNoise()
    {
        m_sAppName = L"Perlin Noise";
    }

private:

#pragma region Variables
    
    int iOctaveCount = 1;
    float fScalingBias = 2.0f;
    int iMode = 1;

    // 2D noise variables
    int iOutputWidth = 180;
    int iOutputHeight = 180;
    float* fNoiseSeed2D = nullptr;
    float* fPerlinNoise2D = nullptr;

    // 1D noise variables
    float* fNoiseSeed1D = nullptr;
    float* fPerlinNoise1D = nullptr;
    int iOutputSize = 180;

#pragma endregion

    virtual bool OnUserCreate()
    {
        iOutputSize = ScreenWidth();
        fNoiseSeed1D = new float[iOutputSize];
        fPerlinNoise1D = new float[iOutputSize];

        for (int i = 0; i < iOutputSize; i++) fNoiseSeed1D[i] = (float)rand() / (float)RAND_MAX;

        iOutputWidth = ScreenWidth();
        iOutputHeight = ScreenHeight();
        fNoiseSeed2D = new float[iOutputWidth * iOutputHeight];
        fPerlinNoise2D = new float[iOutputWidth * iOutputHeight];
        for (int i = 0; i < iOutputWidth * iOutputHeight; i++) fNoiseSeed2D[i] = (float)rand() / (float)RAND_MAX;

        return true;
    }

    virtual bool OnUserUpdate(float fElapsedTime)
    {
        Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');

#pragma region User Input
        // Cycle through possible Octaves 1 to 8 with Space Bar
        if (m_keys[VK_SPACE].bReleased)
        {
            iOctaveCount++;
        }

        if (iOctaveCount == 9)
        {
            iOctaveCount = 1;
        }

        // Change Scaling Bias with Q(Increase) and A(Decrease)
        if (m_keys[L'Q'].bReleased)
        {
            fScalingBias += 0.2f;
        }

        if (m_keys[L'A'].bReleased)
        {
            fScalingBias -= 0.2f;
        }

        if (fScalingBias < 0.2f)
        {
            fScalingBias = 0.2f;
        }

        // Change Mode (1D, 2D, or 2D Colorized) with 1, 2, and 3 keys
        if (m_keys[L'1'].bReleased)
        {
            iMode = 1;
        }

        if (m_keys[L'2'].bReleased)
        {
            iMode = 2;
        }

        if (m_keys[L'3'].bReleased)
        {
            iMode = 3;
        }
#pragma endregion

        // 1D Perlin Noise Handling
        if (iMode == 1) 
        {
            // Reroll 1D Noise Seed with Z Key
            if (m_keys[L'Z'].bReleased) // Noise Between 0 and +1
            {
                for (int i = 0; i < iOutputSize; i++)
                {
                    fNoiseSeed1D[i] = (float)rand() / (float)RAND_MAX;
                }
            }

            // Generate 1D Perlin Noise
            PerlinNoise1D(iOutputSize, fNoiseSeed1D, iOctaveCount, fScalingBias, fPerlinNoise1D);

            // Draw 1D Perlin Noise
            for (int x = 0; x < iOutputSize; x++)
            {
                int y = -(fPerlinNoise1D[x] * (float)ScreenHeight() / 2.0f) + (float)ScreenHeight() / 2.0f;
                for (int f = y; f < ScreenHeight() / 2; f++)
                {
                    Draw(x, f, PIXEL_SOLID, FG_GREEN);
                }
            }
        }

        // 2D Perlin Noise Handling
        if (iMode == 2) // 2D Noise
        {
            // Reroll 2D Noise Seed with Z Key
            if (m_keys[L'Z'].bReleased) // Noise Between 0 and +1
            {
                for (int i = 0; i < iOutputWidth * iOutputHeight; i++)
                {
                    fNoiseSeed2D[i] = (float)rand() / (float)RAND_MAX;
                }
            }

            // Generate 2D Perlin Noise
            PerlinNoise2D(iOutputWidth, iOutputHeight, fNoiseSeed2D, iOctaveCount, fScalingBias, fPerlinNoise2D);

            // Draw 2D Perlin Noise
            for (int x = 0; x < iOutputWidth; x++)
            {
                for (int y = 0; y < iOutputHeight; y++)
                {
                    short bg_col, fg_col;
                    wchar_t sym;
                    int pixel_bw = (int)(fPerlinNoise2D[y * iOutputWidth + x] * 12.0f);
                    switch (pixel_bw)
                    {
                    case 0: bg_col = BG_BLACK; fg_col = FG_BLACK; sym = PIXEL_SOLID; break;

                    case 1: bg_col = BG_BLACK; fg_col = FG_DARK_GREY; sym = PIXEL_QUARTER; break;
                    case 2: bg_col = BG_BLACK; fg_col = FG_DARK_GREY; sym = PIXEL_HALF; break;
                    case 3: bg_col = BG_BLACK; fg_col = FG_DARK_GREY; sym = PIXEL_THREEQUARTERS; break;
                    case 4: bg_col = BG_BLACK; fg_col = FG_DARK_GREY; sym = PIXEL_SOLID; break;

                    case 5: bg_col = BG_DARK_GREY; fg_col = FG_GREY; sym = PIXEL_QUARTER; break;
                    case 6: bg_col = BG_DARK_GREY; fg_col = FG_GREY; sym = PIXEL_HALF; break;
                    case 7: bg_col = BG_DARK_GREY; fg_col = FG_GREY; sym = PIXEL_THREEQUARTERS; break;
                    case 8: bg_col = BG_DARK_GREY; fg_col = FG_GREY; sym = PIXEL_SOLID; break;

                    case 9:  bg_col = BG_GREY; fg_col = FG_WHITE; sym = PIXEL_QUARTER; break;
                    case 10: bg_col = BG_GREY; fg_col = FG_WHITE; sym = PIXEL_HALF; break;
                    case 11: bg_col = BG_GREY; fg_col = FG_WHITE; sym = PIXEL_THREEQUARTERS; break;
                    case 12: bg_col = BG_GREY; fg_col = FG_WHITE; sym = PIXEL_SOLID; break;
                    }

                    Draw(x, y, sym, fg_col | bg_col);
                }
            }

        }

        // 2D COLORIZED perlin Noise Handling
        if (iMode == 3) // 2D Noise - colourised
        {
            if (m_keys[L'Z'].bReleased) // Noise Between 0 and +1
                for (int i = 0; i < iOutputWidth * iOutputHeight; i++) fNoiseSeed2D[i] = (float)rand() / (float)RAND_MAX;


            PerlinNoise2D(iOutputWidth, iOutputHeight, fNoiseSeed2D, iOctaveCount, fScalingBias, fPerlinNoise2D);

            for (int x = 0; x < iOutputWidth; x++)
            {
                for (int y = 0; y < iOutputHeight; y++)
                {
                    short bg_col, fg_col;
                    wchar_t sym;
                    int pixel_bw = (int)(fPerlinNoise2D[y * iOutputWidth + x] * 16.0f);
                    switch (pixel_bw)
                    {
                    case 0: bg_col = BG_DARK_BLUE; fg_col = FG_DARK_BLUE; sym = PIXEL_SOLID; break;

                    case 1: bg_col = BG_DARK_BLUE; fg_col = FG_BLUE; sym = PIXEL_QUARTER; break;
                    case 2: bg_col = BG_DARK_BLUE; fg_col = FG_BLUE; sym = PIXEL_HALF; break;
                    case 3: bg_col = BG_DARK_BLUE; fg_col = FG_BLUE; sym = PIXEL_THREEQUARTERS; break;
                    case 4: bg_col = BG_DARK_BLUE; fg_col = FG_BLUE; sym = PIXEL_SOLID; break;

                    case 5: bg_col = BG_BLUE; fg_col = FG_GREEN; sym = PIXEL_QUARTER; break;
                    case 6: bg_col = BG_BLUE; fg_col = FG_GREEN; sym = PIXEL_HALF; break;
                    case 7: bg_col = BG_BLUE; fg_col = FG_GREEN; sym = PIXEL_THREEQUARTERS; break;
                    case 8: bg_col = BG_BLUE; fg_col = FG_GREEN; sym = PIXEL_SOLID; break;

                    case 9:  bg_col = BG_GREEN; fg_col = FG_DARK_GREY; sym = PIXEL_QUARTER; break;
                    case 10: bg_col = BG_GREEN; fg_col = FG_DARK_GREY; sym = PIXEL_HALF; break;
                    case 11: bg_col = BG_GREEN; fg_col = FG_DARK_GREY; sym = PIXEL_THREEQUARTERS; break;
                    case 12: bg_col = BG_GREEN; fg_col = FG_DARK_GREY; sym = PIXEL_SOLID; break;

                    case 13: bg_col = BG_DARK_GREY; fg_col = FG_WHITE; sym = PIXEL_QUARTER; break;
                    case 14: bg_col = BG_DARK_GREY; fg_col = FG_WHITE; sym = PIXEL_HALF; break;
                    case 15: bg_col = BG_DARK_GREY; fg_col = FG_WHITE; sym = PIXEL_THREEQUARTERS; break;
                    case 16: bg_col = BG_DARK_GREY; fg_col = FG_WHITE; sym = PIXEL_SOLID; break;
                    }

                    Draw(x, y, sym, fg_col | bg_col);
                }
            }
        }

        return true;
    }

#pragma region Functions

    void PerlinNoise1D(int iCount, float* fSeed, int iOctaves, float fBias, float* fOutput)
    {
        // Used 1D Perlin Noise
        for (int x = 0; x < iCount; x++)
        {
            float fNoise = 0.0f;
            float fScale = 1.0f;
            float fScaleAcc = 0.0f;

            for (int o = 0; o < iOctaves; o++)
            {
                int iPitch = iCount >> o;
                int iSample1 = (x / iPitch) * iPitch;
                int iSample2 = (iSample1 + iPitch) % iCount;

                float fBlend = (float)(x - iSample1) / (float)iPitch;
                float fSample = (1.0f - fBlend) * fSeed[iSample1] + fBlend * fSeed[iSample2];
                fNoise += fSample * fScale;
                fScaleAcc += fScale;
                fScale = fScale / fBias;
            }

            // Scale to seed range
            fOutput[x] = fNoise / fScaleAcc;
        }
    }

    void PerlinNoise2D(int iWidth, int iHeight, float* fSeed, int iOctaves, float fBias, float* fOutput)
    {
        // Used 2D Perlin Noise
        for (int x = 0; x < iWidth; x++)
        {
            for (int y = 0; y < iHeight; y++)
            {
                float fNoise = 0.0f;
                float fScale = 1.0f;
                float fScaleAcc = 0.0f;

                for (int o = 0; o < iOctaves; o++)
                {
                    int iPitch = iWidth >> o;
                    int iSampleX1 = (x / iPitch) * iPitch;
                    int iSampleY1 = (y / iPitch) * iPitch;

                    int iSampleX2 = (iSampleX1 + iPitch) % iWidth;
                    int iSampleY2 = (iSampleY1 + iPitch) % iHeight;

                    float fBlendX = (float)(x - iSampleX1) / (float)iPitch;
                    float fBlendY = (float)(y - iSampleY1) / (float)iPitch;

                    float fSampleT = (1.0f - fBlendX) * fSeed[iSampleY1 * iWidth + iSampleX1] + fBlendX * fSeed[iSampleY1 * iWidth + iSampleX2];
                    float fSampleB = (1.0f - fBlendX) * fSeed[iSampleY2 * iWidth + iSampleX1] + fBlendX * fSeed[iSampleY2 * iWidth + iSampleX2];

                    fNoise += (fBlendY * (fSampleB - fSampleT) + fSampleT) * fScale;
                    fScaleAcc += fScale;
                    fScale = fScale / fBias;
                }

                // Scale to seed range
                fOutput[y * iWidth + x] = fNoise / fScaleAcc;
            }
        }
    }

#pragma endregion

};

int main()
{
    Tclards_PerlinNoise program;
    program.ConstructConsole(180, 180, 3, 3);
    program.Start();
    return 0;
}