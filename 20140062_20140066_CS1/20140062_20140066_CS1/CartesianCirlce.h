#pragma once
#include "Command.h"
class CartesianCirlce :
	public Command
{
public:

	CartesianCirlce()
	{
	}

	void doIt(HDC hdc)
	{
		DrawCircleCartesianDirectMethod(hdc, points[0].x, points[0].y, distance(points[0], points[1]), color);
	}

	int distance(POINT p1, POINT p2)
	{
		return sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
	}

	int rounding(double x){
		return int(x + 0.5);
	}

	void Draw8Points(HDC hdc, int Xc, int Yc, int a, int b, COLORREF color){
		SetPixel(hdc, Xc + a, Yc + b, color);
		SetPixel(hdc, Xc - a, Yc + b, color);
		SetPixel(hdc, Xc + a, Yc - b, color);
		SetPixel(hdc, Xc - a, Yc - b, color);
		SetPixel(hdc, Xc + b, Yc + a, color);
		SetPixel(hdc, Xc - b, Yc + a, color);
		SetPixel(hdc, Xc + b, Yc - a, color);
		SetPixel(hdc, Xc - b, Yc - a, color);
	}

	void DrawCircleCartesianDirectMethod(HDC hdc, int Xc, int Yc, int r, COLORREF color){
		int x = 0;
		double y = r;
		while (x < y){
			Draw8Points(hdc, Xc, Yc, x, rounding(y), color);
			x += 1;
			y = sqrt((double)r*r - x*x);
		}
	}

	~CartesianCirlce()
	{
	}
};

