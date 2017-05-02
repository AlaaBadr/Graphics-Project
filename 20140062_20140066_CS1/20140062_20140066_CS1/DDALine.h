#pragma once
#include "Command.h"
class DDALine :
	public Command
{
public:

	DDALine()
	{
	}

	void doIt(HDC hdc)
	{
		DrawLineDDA(hdc, points[0].x, points[0].y, points[1].x, points[1].y, RGB(0, 0, 0));
	}

	void swapNum(int &x1, int &x2, int &y1, int&y2){
		int temp = x1;
		x1 = x2;
		x2 = temp;
		temp = y1;
		y1 = y2;
		y2 = temp;
	}

	void DrawLineDDA(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color) {
		//optimized 3la wad3o, eltany yuuckkyyy..
		double dx = x2 - x1;
		double dy = y2 - y1;
		double m, mi, x, y;
		if (abs(dy) < abs(dx)){		//slope < 1
			m = dy / dx;
			if (x1 > x2)
			{
				swapNum(x1, x2, y1, y2);
			}
			x = x1;
			y = y1;
			SetPixel(hdc, x, y, color);
			while (x < x2)
			{
				x = x + 1;
				y = y + m;
				SetPixel(hdc, x, round(y), color);
			}
		}
		else
		{
			mi = dx / dy;
			if (y1 > y2)
			{
				swapNum(x1, x2, y1, y2);
			}
			x = x1;
			y = y1;
			SetPixel(hdc, x, y, color);
			while (y < y2)
			{
				y = y + 1;
				x = x + mi;
				SetPixel(hdc, round(x), y, color);
			}
		}
	}

	~DDALine()
	{
	}
};

