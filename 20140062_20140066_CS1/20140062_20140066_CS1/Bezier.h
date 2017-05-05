#pragma once
#include "Command.h"
class Bezier :
	public Command
{
public:

	Bezier()
	{
	}

	void doIt(HDC hdc)
	{
		DrawCurveRecursiveBezier(hdc, &points[0], points.size(), color);
		//points.clear();
		//numOfInput = 0;
	}

	double BezierRecurse(double *p, int n, double t){
		if (n == 1)
			return p[0];
		return (1 - t)*BezierRecurse(p, n - 1, t) + t*BezierRecurse(p + 1, n - 1, t);
	}

	void DrawCurveRecursiveBezier(HDC hdc, POINT* points, int n, COLORREF color){
		double *pointsx = new double[n];
		double *pointsy = new double[n];
		double x, y;
		for (int i = 0; i < n; i++)
		{
			pointsx[i] = points[i].x;
			pointsy[i] = points[i].y;
		}
		for (double t = 0; t < 1; t += 0.001)
		{
			x = BezierRecurse(pointsx, n, t);
			y = BezierRecurse(pointsy, n, t);
			SetPixel(hdc, round(x), round(y), color);
		}
		free(pointsx);
		free(pointsy);
	}

	~Bezier()
	{
	}
};

