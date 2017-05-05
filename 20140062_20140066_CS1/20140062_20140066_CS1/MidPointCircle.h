#pragma once
#include "Command.h"
class MidPointCircle :
	public Command
{
public:

	MidPointCircle()
	{
	}

	void doIt(HDC hdc)
	{
		DrawCircleMidPoint(hdc, points[0].x, points[0].y, distance(points[0], points[1]), color);
		//points.clear();
		//numOfInput = 0;
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

	void DrawCircleMidPoint(HDC hdc, int Xc, int Yc, int r, COLORREF color){
		int x = 0;
		int y = r;
		Draw8Points(hdc, Xc, Yc, x, y, color);
		int d = 1 - r;
		int d1 = 3;
		int d2 = 5 - 2 * r;
		while (x < y){
			if (d < 0){
				d += d1;
				d2 += 2;
			}
			else{
				d += d2;
				d2 += 4;
				y--;
			}
			x++;
			d1 += 2;
			Draw8Points(hdc, Xc, Yc, x, y, color);
		}
	}

	~MidPointCircle()
	{
	}
};

