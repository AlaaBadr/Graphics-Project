#pragma once
#include "Command.h"
class PolarCircle :
	public Command
{
public:

	PolarCircle()
	{
	}

	void doIt(HDC hdc)
	{
		DrawCirclePolar(hdc, points[0].x, points[0].y, distance(points[0], points[1]), color);
	}

	int distance(POINT p1, POINT p2)
	{
		return sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
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

	void DrawCirclePolar(HDC hdc, int Xc, int Yc, int r, COLORREF color)
	{
		double dtheta = 1.0 / r;
		for (double theta = 0; theta <= 45; theta += dtheta)
		{
			double x = r * cos(theta);
			double y = r * sin(theta);
			Draw8Points(hdc, Xc, Yc, round(x), round(y), color);
		}
	}

	~PolarCircle()
	{
	}
};

