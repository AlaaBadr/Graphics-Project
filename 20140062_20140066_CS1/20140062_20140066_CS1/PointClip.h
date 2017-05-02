#pragma once
#include "Command.h"
class PointClip :
	public Command
{
public:

	PointClip()
	{
	}

	void doIt(HDC hdc)
	{
		PointClipping(hdc, points[0].x, points[0].y, points[1].x, points[2].x, points[3].y, points[4].y, RGB(0, 0, 0));
	}

	void PointClipping(HDC hdc, int x, int y, int xleft, int xright, int ytop, int ybottom, COLORREF color)
	{
		if (x >= xleft && x <= xright && y >= ytop && y <= ybottom)
			SetPixel(hdc, x, y, color);
	}

	~PointClip()
	{
	}
};

