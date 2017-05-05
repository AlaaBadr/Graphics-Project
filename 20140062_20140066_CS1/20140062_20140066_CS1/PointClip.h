#pragma once
#include "Command.h"
class PointClip :
	public Command
{
private:
	DDALine d;
public:

	PointClip()
	{
	}

	void doIt(HDC hdc)
	{
		d.DrawLineDDA(hdc, points[1].x, points[3].y, points[2].x, points[3].y, RGB(180, 180, 180));
		d.DrawLineDDA(hdc, points[1].x, points[4].y, points[2].x, points[4].y, RGB(180, 180, 180));
		d.DrawLineDDA(hdc, points[1].x, points[3].y, points[1].x, points[4].y, RGB(180, 180, 180));
		d.DrawLineDDA(hdc, points[2].x, points[3].y, points[2].x, points[4].y, RGB(180, 180, 180));

		PointClipping(hdc, points[0].x, points[0].y, points[1].x, points[2].x, points[3].y, points[4].y, color);
		//points.clear();
		//numOfInput = 0;
	}

	void PointClipping(HDC hdc, int x, int y, int xleft, int xright, int ybottom, int ytop, COLORREF color)
	{
		if (x >= xleft && x <= xright && y >= ytop && y <= ybottom)
			SetPixel(hdc, x, y, color);
	}

	~PointClip()
	{
	}
};

