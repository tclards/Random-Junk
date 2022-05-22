#include <iostream>
#include <string>
using namespace std;

#include "olcConsoleGameEngine.h"

struct sBall
{
	float px, py;
	float vx, vy;
	float ax, ay;
	float ox, oy;
	float radius;
	float mass;

	float fSimTimeRemaining;

	int id;
};

struct sLineSegment
{
	float sx, sy;
	float ex, ey;
	float radius;
};

class Tclards_CirclePhysics : public olcConsoleGameEngine
{
public:
	Tclards_CirclePhysics()
	{
		m_sAppName = L"Circle Physics";
	}

private:
	vector<pair<float, float>> modelCircle;
	vector<sBall> vecBalls;
	sBall* pSelectedBall = nullptr;

	vector<sLineSegment> vecLines;
	sLineSegment* pSelectedLine = nullptr;
	bool bSelectedLineStart = false;

	void AddBall(float x, float y, float r = 5.0f)
	{
		sBall b;
		b.px = x; b.py = y;
		b.vx = 0; b.vy = 0;
		b.ax = 0; b.ay = 0;
		b.radius = r;
		b.mass = r * 10.0f;

		b.id = vecBalls.size();
		vecBalls.emplace_back(b);
	}

public:
	// Called by olcConsoleGameEngine
	virtual bool OnUserCreate()
	{
		float fDefaultRad = 4.0f;

		// Generate Balls
		for (int i = 0; i < 75; i++)
		{
			AddBall(rand() % ScreenWidth(), rand() % ScreenHeight(), fDefaultRad);
		}

		float fLineRadius = 4.0f;
		vecLines.push_back({ 30.0f, 30.0f, 100.0f, 30.0f, fLineRadius });
		vecLines.push_back({ 30.0f, 50.0f, 100.0f, 50.0f, fLineRadius });
		vecLines.push_back({ 30.0f, 70.0f, 100.0f, 70.0f, fLineRadius });
		vecLines.push_back({ 30.0f, 90.0f, 100.0f, 90.0f, fLineRadius });

		return true;
	}

	// Called by olcConsoleGameEngine
	virtual bool OnUserUpdate(float fElapsedTime)
	{
		// Lambda function for testing overlap
		auto DoCirclesOverlap = [](float x1, float y1, float r1, float x2, float y2, float r2)
		{
			return fabs((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) <= (r1 + r2) * (r1 + r2);
		};

		// Lambda function for testing mouse click 
		auto IsPointInCircle = [](float x1, float y1, float r1, float px, float py)
		{
			return fabs((x1 - px) * (x1 - px) + (y1 - py) * (y1 - py)) < (r1 * r1);
		};

		// User Input Handling
		#pragma region User Input

		// Right Mouse Press or Left Mouse Press
		if (m_mouse[0].bPressed || m_mouse[1].bPressed)
		{
			// Check for selected ball
			pSelectedBall = nullptr;
			for (auto& ball : vecBalls)
			{
				if (IsPointInCircle(ball.px, ball.py, ball.radius, m_mousePosX, m_mousePosY))
				{
					pSelectedBall = &ball;
					break;
				}
			}

			// Check for selected line segment
			pSelectedLine = nullptr;
			for (auto& line : vecLines)
			{
				if (IsPointInCircle(line.sx, line.sy, line.radius, m_mousePosX, m_mousePosY))
				{
					pSelectedLine = &line;
					bSelectedLineStart = true;
					break;
				}

				if (IsPointInCircle(line.ex, line.ey, line.radius, m_mousePosX, m_mousePosY))
				{
					pSelectedLine = &line;
					bSelectedLineStart = false;
					break;
				}
			}
		}

		// Right Mouse Hold
		if (m_mouse[0].bHeld)
		{
			if (pSelectedBall != nullptr)
			{
				pSelectedBall->px = m_mousePosX;
				pSelectedBall->py = m_mousePosY;
			}

			if (pSelectedLine != nullptr)
			{
				if (bSelectedLineStart)
				{
					pSelectedLine->sx = GetMouseX();
					pSelectedLine->sy = GetMouseY();
				}
				else
				{
					pSelectedLine->ex = GetMouseX();
					pSelectedLine->ey = GetMouseY();
				}
			}
		}

		// Right Mouse Released
		if (m_mouse[0].bReleased)
		{
			pSelectedBall = nullptr;
			pSelectedLine = nullptr;
		}

		// Left Mouse Released
		if (m_mouse[1].bReleased)
		{
			if (pSelectedBall != nullptr)
			{
				// Apply Velocity
				pSelectedBall->vx = 5.0f * ((pSelectedBall->px) - (float)m_mousePosX);
				pSelectedBall->vy = 5.0f * ((pSelectedBall->py) - (float)m_mousePosY);
			}

			pSelectedBall = nullptr;
		}

#pragma endregion

		vector<pair<sBall*, sBall*>> vecCollidingPairs;
		vector<sBall*> vecFakeBalls;

		int iSimulationUpdates = 4;
		float fSimElapsedTime = fElapsedTime / (float)iSimulationUpdates;

		int iMaxSimulationSteps = 15;

		// Main simulation loop
		for (int i = 0; i < iSimulationUpdates; i++)
		{
			// Set all balls time to maximum for this epoch
			for (auto& ball : vecBalls)
			{
				ball.fSimTimeRemaining = fSimElapsedTime;
			}

			for (int j = 0; j < iMaxSimulationSteps; j++)
			{
				// Update ball positions
				for (auto& ball : vecBalls)
				{
					if (ball.fSimTimeRemaining > 0.0f)
					{
						// Store original position
						ball.ox = ball.px;
						ball.oy = ball.py;

						// Add Drag to emulate rolling friction
						ball.ax = -ball.vx * 0.8f;
						ball.ay = -ball.vy * 0.8f + 100.0f;

						// Update ball physics
						ball.vx += ball.ax * ball.fSimTimeRemaining;
						ball.vy += ball.ay * ball.fSimTimeRemaining;
						ball.px += ball.vx * ball.fSimTimeRemaining;
						ball.py += ball.vy * ball.fSimTimeRemaining;

						// Wrap the balls around screen
						if (ball.px < 0) ball.px += (float)ScreenWidth();
						if (ball.px >= ScreenWidth()) ball.px -= (float)ScreenWidth();
						if (ball.py < 0) ball.py += (float)ScreenHeight();
						if (ball.py >= ScreenHeight()) ball.py -= ScreenHeight();

						// Clamp velocity near zero
						if (fabs(ball.vx * ball.vx + ball.vy * ball.vy) < 0.01f)
						{
							ball.vx = 0;
							ball.vy = 0;
						}
					}
				}

				// Static Collision Resolution (i.e. overlap)
				for (auto& ball : vecBalls)
				{

					// Edge Collision Checking
					for (auto& edge : vecLines)
					{
						float fLineX1 = edge.ex - edge.sx;
						float fLineY1 = edge.ey - edge.sy;

						float fLineX2 = ball.px - edge.sx;
						float fLineY2 = ball.py - edge.sy;

						float fEdgeLength = fLineX1 * fLineX1 + fLineY1 * fLineY1;

						float t = max(0, min(fEdgeLength, (fLineX1 * fLineX2 + fLineY1 * fLineY2))) / fEdgeLength;

						float fClosestPointX = edge.sx + t * fLineX1;
						float fClosestPointY = edge.sy + t * fLineY1;

						float fDistance = sqrtf((ball.px - fClosestPointX) * (ball.px - fClosestPointX) + (ball.py - fClosestPointY) * (ball.py - fClosestPointY));

						if (fDistance <= (ball.radius + edge.radius))
						{
							// Static collision has occurred
							sBall* fakeBall = new sBall();
							fakeBall->radius = edge.radius;
							fakeBall->mass = ball.mass * 1.0f;
							fakeBall->px = fClosestPointX;
							fakeBall->py = fClosestPointY;
							fakeBall->vx = -ball.vx;
							fakeBall->vy = -ball.vy;

							vecFakeBalls.push_back(fakeBall);
							vecCollidingPairs.push_back({ &ball, fakeBall });

							float fOverlap = 1.0f * (fDistance - ball.radius - fakeBall->radius);

							// Displace current ball away from collision
							ball.px -= fOverlap * (ball.px - fakeBall->px) / fDistance;
							ball.py -= fOverlap * (ball.py - fakeBall->py) / fDistance;
						}
					}

					for (auto& target : vecBalls)
					{
						if (ball.id != target.id)
						{
							if (DoCirclesOverlap(ball.px, ball.py, ball.radius, target.px, target.py, target.radius))
							{
								// Collission has occured
								vecCollidingPairs.push_back({ &ball, &target });

								// Distance between ball centers
								float fDistance = sqrtf((ball.px - target.px) * (ball.px - target.px) + (ball.py - target.py) * (ball.py - target.py));

								float fOverlap = 0.5f * (fDistance - ball.radius - target.radius);

								// Displace Current Ball
								ball.px -= fOverlap * (ball.px - target.px) / fDistance;
								ball.py -= fOverlap * (ball.py - target.py) / fDistance;

								// Displace Target Ball
								target.px += fOverlap * (ball.px - target.px) / fDistance;
								target.py += fOverlap * (ball.py - target.py) / fDistance;
							}
						}
					}

					// Time Displacement
					float fIntendedSpeed = sqrtf(ball.vx * ball.vx + ball.vy * ball.vy);
					float fIntededDistance = fIntendedSpeed * ball.fSimTimeRemaining;
					float fActualDistance = sqrtf((ball.px - ball.ox)*(ball.px - ball.ox) + (ball.py - ball.oy)*(ball.py - ball.oy));
					float fActualTime = fActualDistance / fIntendedSpeed;

					ball.fSimTimeRemaining = ball.fSimTimeRemaining - fActualDistance;

				}

				// Work out Dynamic Collisions
				for (auto c : vecCollidingPairs)
				{
					sBall* b1 = c.first;
					sBall* b2 = c.second;

					// Distance between balls
					float fDistance = sqrtf((b1->px - b2->px) * (b1->px - b2->px) + (b1->py - b2->py) * (b1->py - b2->py));

					// Normal
					float nx = (b2->px - b1->px) / fDistance;
					float ny = (b2->py - b1->py) / fDistance;

					// Tangent
					float tx = -ny;
					float ty = nx;

					// Dot Product Tangent
					float dpTan1 = b1->vx * tx + b1->vy * ty;
					float dpTan2 = b2->vx * tx + b2->vy * ty;

					// Dot Product Normal
					float dpNorm1 = b1->vx * nx + b1->vy * ny;
					float dpNorm2 = b2->vx * nx + b2->vy * ny;

					// Conservation of momentum in 1D
					float m1 = (dpNorm1 * (b1->mass - b2->mass) + 2.0f * b2->mass * dpNorm2) / (b1->mass + b2->mass);
					float m2 = (dpNorm2 * (b2->mass - b1->mass) + 2.0f * b1->mass * dpNorm1) / (b1->mass + b2->mass);

					// Update ball velocities
					b1->vx = tx * dpTan1 + nx * m1;
					b1->vy = ty * dpTan1 + ny * m1;
					b2->vx = tx * dpTan2 + nx * m2;
					b2->vy = ty * dpTan2 + ny * m2;
				}

				// Remove fake balls
				for (auto& b : vecFakeBalls) delete b;
				vecFakeBalls.clear();

				// Remove collisions
				vecCollidingPairs.clear();
			}
		}

		// Drawing
		#pragma region Drawing
		
		// Clear Screen
		Fill(0, 0, ScreenWidth(), ScreenHeight(), ' ');

		// Draw Lines
		for (auto line : vecLines)
		{
			FillCircle(line.sx, line.sy, line.radius, PIXEL_HALF, FG_WHITE);
			FillCircle(line.ex, line.ey, line.radius, PIXEL_HALF, FG_WHITE);

			float nx = -(line.ey - line.sy);
			float ny = (line.ex - line.sx);
			float d = sqrt(nx * nx + ny * ny);
			nx /= d;
			ny /= d;

			DrawLine((line.sx + nx * line.radius), (line.sy + ny * line.radius), (line.ex + nx * line.radius), (line.ey + ny * line.radius));
			DrawLine((line.sx - nx * line.radius), (line.sy - ny * line.radius), (line.ex - nx * line.radius), (line.ey - ny * line.radius));

		}

		// Draw Balls
		for (auto ball : vecBalls)
		{
			FillCircle(ball.px, ball.py, ball.radius, PIXEL_SOLID, FG_RED);
		}

		// Draw Red Line to indicate collision
		for (auto c : vecCollidingPairs)
		{
			DrawLine(c.first->px, c.first->py, c.second->px, c.second->py, PIXEL_SOLID, FG_RED);
		}

		// Draw Blue Line to Indicate velocity vector
		if (pSelectedBall != nullptr)
		{
			// Draw Cue
			DrawLine(pSelectedBall->px, pSelectedBall->py, m_mousePosX, m_mousePosY, PIXEL_SOLID, FG_BLUE);
		}

#pragma endregion

		return true;
	}
};

int main()
{
	// Use olcConsoleGameEngine derived app
	Tclards_CirclePhysics Sim;

	// Create console
	if (Sim.ConstructConsole(320, 240, 4, 4))
	{
		// Start the engine
		Sim.Start();
	}
	else if (Sim.ConstructConsole(160, 120, 8, 8))
	{
		// Start the engine
		Sim.Start();
	}
	else
	{
		wcout << L"Could not construct console" << endl;
	}

	return 0;
}