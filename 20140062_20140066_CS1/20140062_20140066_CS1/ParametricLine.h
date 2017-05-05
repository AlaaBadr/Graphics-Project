#pragma once
#include "Command.h"
class ParametricLine :
	public Command
{
public:

	ParametricLine()
	{
	}

	void doIt(HDC hdc)
	{
		DrawLineParametric(hdc, points[0].x, points[0].y, points[1].x, points[1].y, color);
		//points.clear();
		//numOfInput = 0;
	}

	int rounding(double x){
		return int(x + 0.5);
	}

	void DrawLineParametric(HDC hdc, int xs, int ys, int xe, int ye, COLORREF color){
		int n = max(abs(xe - xs), abs(ye - ys));
		double dt = 1.0 / n;
		double dx = dt * (xe - xs);
		double dy = dt * (ye - ys);
		double x = xs;
		double y = ys;
		for (int k = 0; k < n; k++){
			SetPixel(hdc, rounding(x), rounding(y), color);
			x = x + dx;
			y = y + dy;
		}
	}

	~ParametricLine()
	{
	}
};

