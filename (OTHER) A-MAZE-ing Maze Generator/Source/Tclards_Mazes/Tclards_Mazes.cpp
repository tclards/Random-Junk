#include <iostream>
#include <stack>
#include "olcConsoleGameEngine.h"

using namespace std;

class Tclards_Maze : public olcConsoleGameEngine
{
public:
    Tclards_Maze()
    {
        m_sAppName = L"A-MAZE-ing Game";
    }

private:
    int iMazeWidth;
    int iMazeHeight;
    int* iMaze;

    // Some bit fields for convenience
    enum
    {
        CELL_PATH_N = 0x01,
        CELL_PATH_E = 0x02,
        CELL_PATH_S = 0x04,
        CELL_PATH_W = 0x08,
        CELL_VISITED = 0x10,
    };

    // Algorithm variables
    int iVisitedCells;
    stack<pair<int, int>> iStack; // (x, y) coordinate pairs
    int iPathWidth;

protected:
    // Called by olcConsoleGameEngine
    virtual bool OnUserCreate()
    {
        // Maze Parameters
        iMazeWidth = 40;
        iMazeHeight = 25;
        iMaze = new int[iMazeWidth * iMazeHeight];
        memset(iMaze, 0x00, iMazeWidth * iMazeHeight * sizeof(int));
        iPathWidth = 3;

        // Choose a starting cell
        int x = rand() % iMazeWidth;
        int y = rand() % iMazeHeight;
        iStack.push(make_pair(x, y));
        iMaze[y * iMazeWidth + x] = CELL_VISITED;
        iVisitedCells = 1;

        return true;
    }

    // Called by olcConsoleGameEngine
    virtual bool OnUserUpdate(float fElapsedTime)
    {
        // Slow down for animation effect
        this_thread::sleep_for(10ms);

        // Lambda Helper Function
        auto offset = [&](int x, int y)
        {
            return (iStack.top().second + y) * iMazeWidth + (iStack.top().first + x);
        };

        // Do Maze Algorithm
        if (iVisitedCells < iMazeWidth * iMazeHeight)
        {
            // Create a set of the unvisited neighbors
            vector<int> vecNeighbors;

            // North Neighbor
            if (iStack.top().second > 0 && (iMaze[offset(0, -1)] & CELL_VISITED) == 0)
            {
                vecNeighbors.push_back(0);
            }
            // East Neighbor
            if (iStack.top().first < iMazeWidth - 1 && (iMaze[offset(1, 0)] & CELL_VISITED) == 0)
            {
                vecNeighbors.push_back(1);
            }
            // South Neighbor
            if (iStack.top().second < iMazeHeight - 1 && (iMaze[offset(0, 1)] & CELL_VISITED) == 0)
            {
                vecNeighbors.push_back(2);
            }
            // West Neighbor
            if (iStack.top().first > 0 && (iMaze[offset(-1, 0)] & CELL_VISITED) == 0)
            {
                vecNeighbors.push_back(3);
            }
              
            // Are there any neighbors available?
            if (!vecNeighbors.empty())
            {
                // Choose one available neighbor at random
                int iNextCell_Dir = vecNeighbors[rand() % vecNeighbors.size()];

                // Create a path between the neighbor and the current cell
                switch (iNextCell_Dir)
                {
                case 0: // North
                    iMaze[offset(0, -1)] |= CELL_VISITED | CELL_PATH_S;
                    iMaze[offset(0, 0)] |= CELL_PATH_N;
                    iStack.push(make_pair((iStack.top().first + 0), (iStack.top().second - 1)));
                    break;

                case 1: // East
                    iMaze[offset(+1, 0)] |= CELL_VISITED | CELL_PATH_W;
                    iMaze[offset(0, 0)] |= CELL_PATH_E;
                    iStack.push(make_pair((iStack.top().first + 1), (iStack.top().second + 0)));
                    break;

                case 2: // South
                    iMaze[offset(0, +1)] |= CELL_VISITED | CELL_PATH_N;
                    iMaze[offset(0, 0)] |= CELL_PATH_S;
                    iStack.push(make_pair((iStack.top().first + 0), (iStack.top().second + 1)));
                    break;

                case 3: // West
                    iMaze[offset(-1, 0)] |= CELL_VISITED | CELL_PATH_E;
                    iMaze[offset(0, 0)] |= CELL_PATH_W;
                    iStack.push(make_pair((iStack.top().first - 1), (iStack.top().second + 0)));
                    break;
                }

                iVisitedCells++;
            }
            else
            {
                iStack.pop(); // no available neighbors so backtrack!
            }

        }

        // === DRAWING STUFF ===

        // Clear Screen by drawing 'spaces' everywhere
        Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');

        // Draw Maze
        for (int x = 0; x < iMazeWidth; x++)
        {
            for (int y = 0; y < iMazeHeight; y++)
            {
                // Each cell is inflated by m_nPathWidth, so fill it in
                for (int py = 0; py < iPathWidth; py++)
                    for (int px = 0; px < iPathWidth; px++)
                    {
                        if (iMaze[y * iMazeWidth + x] & CELL_VISITED)
                            Draw(x * (iPathWidth + 1) + px, y * (iPathWidth + 1) + py, PIXEL_SOLID, FG_WHITE); // Draw Cell
                        else
                            Draw(x * (iPathWidth + 1) + px, y * (iPathWidth + 1) + py, PIXEL_SOLID, FG_BLUE); // Draw Cell
                    }

                // Draw passageways between cells
                for (int p = 0; p < iPathWidth; p++)
                {
                    if (iMaze[y * iMazeWidth + x] & CELL_PATH_S)
                        Draw(x * (iPathWidth + 1) + p, y * (iPathWidth + 1) + iPathWidth); // Draw South Passage

                    if (iMaze[y * iMazeWidth + x] & CELL_PATH_E)
                        Draw(x * (iPathWidth + 1) + iPathWidth, y * (iPathWidth + 1) + p); // Draw East Passage
                }
            }
        }

        // Draw Unit - the top of the stack
        for (int py = 0; py < iPathWidth; py++)
            for (int px = 0; px < iPathWidth; px++)
                Draw(iStack.top().first * (iPathWidth + 1) + px, iStack.top().second * (iPathWidth + 1) + py, 0x2588, FG_GREEN); // Draw Cell


        return true;
    }
};

int main()
{
    // Seed random number generator
    srand(clock());

    // Use olcConsoleGameEngine derived app
    Tclards_Maze game;

    // Create console
    game.ConstructConsole(160, 100, 8, 8);

    // Start the engine
    game.Start();

    return 0;
}