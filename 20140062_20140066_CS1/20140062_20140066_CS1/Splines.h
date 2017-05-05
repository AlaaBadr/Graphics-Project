#pragma once
#include "Command.h"
#include "Hermite.h"
#include "SecondDegreeSlopeCurve.h"
class Splines :
	public Command
{
private:
	Hermite h;
	SecondDegreeSlopeCurve s;
public:

	Splines()
	{
	}

	void doIt(HDC hdc)
	{
		DrawCurveCardinal(hdc, &points[0], points.size(), 0.5, color);
		//points.clear();
		//numOfInput = 0;
	}

	void DrawCurveCardinal(HDC hdc, POINT *p, int n, double c, COLORREF color){
		POINT* t = new POINT[n - 2];
		for (int i = 1; i < n - 1; i++)
		{
			t[i - 1].x = (p[i + 1].x - p[i - 1].x) * c / 2;
			t[i - 1].y = (p[i + 1].y - p[i - 1].y) * c / 2;
		}
		for (int i = 1; i < n - 1; i++)
			h.DrawCurveThirdDegreeHermite(hdc, p[i], t[i - 1], p[i + 1], t[i], color);

		s.DrawCurveSecondDegreeSlope(hdc, p[0], p[1], t[0], color);
		POINT tmp;
		tmp.x = -t[n - 3].x;
		tmp.y = -t[n - 3].y;
		s.DrawCurveSecondDegreeSlope(hdc, p[n - 1], p[n - 2], tmp, color);
		free(t);
	}

	~Splines()
	{
	}
};

