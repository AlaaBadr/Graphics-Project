#pragma once
#include "Command.h"
class FirstDegreeCurve :
	public Command
{
public:

	FirstDegreeCurve()
	{
	}

	void doIt(HDC hdc)
	{
		DrawCurveFirstDegree(hdc, points[0], points[1], RGB(0, 0, 0));
	}

	void DrawCurveFirstDegree(HDC hdc, POINT p1, POINT p2, COLORREF color)
	{
		double x, y;
		double alphax = p2.x - p1.x, alphay = p2.y - p1.y, betax = p1.x, betay = p1.y;
		for (double t = 0; t < 1; t += 0.0001)
		{
			x = alphax*t + betax;
			y = alphay*t + betay;
			SetPixel(hdc, round(x), round(y), RGB(0, 0, 0));
		}
	}

	~FirstDegreeCurve()
	{
	}
};

