#pragma once
#include "Command.h"
class SecondDegreeHalfCurve :
	public Command
{
public:

	SecondDegreeHalfCurve()
	{
	}

	void doIt(HDC hdc)
	{
		DrawCurveSecondDegreeHalfPoint(hdc, points[0], points[1], points[2], color);
		//points.clear();
		//numOfInput = 0;
	}

	void DrawCurveSecondDegreeHalfPoint(HDC hdc, POINT p1, POINT p2, POINT p3, COLORREF color){
		double x, y;
		double alphax = -4 * p2.x + 2 * p3.x + 2 * p1.x;
		double alphay = -4 * p2.y + 2 * p3.y + 2 * p1.y;
		double betax = 4 * p2.x - p3.x - 3 * p1.x;
		double betay = 4 * p2.y - p3.y - 3 * p1.y;
		double gammax = p1.x;
		double gammay = p1.y;
		for (double t = 0; t < 1; t += 0.0001)
		{
			x = alphax*t*t + betax*t + gammax;
			y = alphay*t*t + betay*t + gammay;
			SetPixel(hdc, round(x), round(y), color);
		}
	}

	~SecondDegreeHalfCurve()
	{
	}
};

