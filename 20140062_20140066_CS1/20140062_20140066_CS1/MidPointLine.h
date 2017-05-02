#pragma once
#include "Command.h"
class MidPointLine :
	public Command
{
public:

	MidPointLine()
	{
	}

	void doIt(HDC hdc)
	{
		DrawLineMidPoint(hdc, points[0].x, points[0].y, points[1].x, points[1].y, RGB(0, 0, 0));
	}

	void swapNum(int &x1, int &x2, int &y1, int&y2){
		int temp = x1;
		x1 = x2;
		x2 = temp;
		temp = y1;
		y1 = y2;
		y2 = temp;
	}

	void DrawLineMidPoint(HDC hdc, int Xs, int Ys, int Xe, int Ye, COLORREF color)
	{
		double dx, dy, d;
		int x, y;
		double m = (double)(Ye - Ys) / (Xe - Xs);
		if (Xs > Xe)
			swapNum(Xs, Xe, Ys, Ye);
		x = Xs;
		y = Ys;
		dx = Xe - Xs;
		dy = Ye - Ys;
		d = 0.5 * dx - dy;
		if (m >= 0 && m <= 1)
		{
			SetPixel(hdc, x, y, color);
			while (x < Xe)
			{
				if (d > 0)
				{
					x = x + 1;
					d += (-dy);
				}
				else
				{
					x = x + 1;
					y = y + 1;
					d += (dx - dy);
				}
				SetPixel(hdc, x, y, color);
			}
		}
		else if (m > 1)
		{
			SetPixel(hdc, x, y, color);
			while (x < Xe)
			{
				if (d > 0)
				{
					x = x + 1;
					y = y + 1;
					d += (dx - dy);
				}
				else
				{
					y = y + 1;
					d += dx;
				}
				SetPixel(hdc, x, y, color);
			}
		}
		else if (m >= -1)
		{
			while (x < Xe)
			{
				if (d > 0)
				{
					x = x + 1;
					y = y - 1;
					d += (-dx - dy);
				}
				else
				{
					x = x + 1;
					d += -dy;
				}
				SetPixel(hdc, x, y, color);
			}
		}
		else if (m < -1)
		{
			while (x < Xe)
			{
				if (d <= 0)
				{
					x = x + 1;
					y = y - 1;
					d += (-dx - dy);
				}
				else
				{
					y = y - 1;
					d += -dx;
				}
				SetPixel(hdc, x, y, color);
			}
		}
	}

	~MidPointLine()
	{
	}
};

