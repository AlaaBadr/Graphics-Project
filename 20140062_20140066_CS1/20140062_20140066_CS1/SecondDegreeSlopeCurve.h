#pragma once
#include "Command.h"
class SecondDegreeSlopeCurve :
	public Command
{
public:

	SecondDegreeSlopeCurve()
	{
	}

	void doIt(HDC hdc)
	{
		DrawCurveSecondDegreeSlope(hdc, points[0], points[1], points[2], RGB(0, 0, 0));
	}

	void DrawCurveSecondDegreeSlope(HDC hdc, POINT p1, POINT p2, POINT t1, COLORREF color){
		double x, y;
		double alphax = p2.x - p1.x - t1.x;
		double alphay = p2.y - p1.y - t1.y;
		double betax = t1.x;
		double betay = t1.y;
		double gammax = p1.x;
		double gammay = p1.y;
		for (double t = 0; t < 1; t += 0.0001)
		{
			x = alphax*t*t + betax*t + gammax;
			y = alphay*t*t + betay*t + gammay;
			SetPixel(hdc, round(x), round(y), RGB(0, 0, 0));
		}
	}

	~SecondDegreeSlopeCurve()
	{
	}
};

