#pragma once
#include "Command.h"
#include "DDALine.h"
class LineClip :
	public Command
{
private:
	DDALine d;
public:

	LineClip()
	{
	}

	void doIt(HDC hdc)
	{
		d.DrawLineDDA(hdc, points[2].x, points[4].y, points[3].x, points[4].y, RGB(180, 180, 180));
		d.DrawLineDDA(hdc, points[2].x, points[5].y, points[3].x, points[5].y, RGB(180, 180, 180));
		d.DrawLineDDA(hdc, points[2].x, points[4].y, points[2].x, points[5].y, RGB(180, 180, 180));
		d.DrawLineDDA(hdc, points[3].x, points[4].y, points[3].x, points[5].y, RGB(180, 180, 180));

		cohenSuth(hdc, points[0].x, points[0].y, points[1].x, points[1].y, points[2].x, points[3].x, points[4].y, points[5].y, color);
		//points.clear();
		//numOfInput = 0;
	}

	union outCode{
		unsigned all : 4;
		struct{
			unsigned left : 1,
		right : 1,
			buttom : 1,
				 top : 1;
		};
	};

	outCode getOutCode(double x, double y, int xleft, int xright, int ybuttom, int ytop)
	{
		outCode res;
		res.all = 0;
		if (x < xleft)
			res.left = 1;
		else if (x > xright)
			res.right = 1;
		if (y > ybuttom)
			res.buttom = 1;
		else if (y < ytop)
			res.top = 1;
		return res;
	}

	POINT vIntersect(double xs, double ys, double xe, double ye, int xedge)
	{
		POINT v;
		v.x = xedge;
		v.y = (v.x - xs) * (ye - ys) / (xe - xs) + ys;
		return v;
	}

	POINT hIntersect(double xs, double ys, double xe, double ye, int yedge)
	{
		POINT v;
		v.y = yedge;
		v.x = (v.y - ys) * (xe - xs) / (ye - ys) + xs;
		return v;
	}

	void cohenSuth(HDC hdc, double xs, double ys, double xe, double ye, int xleft, int xright, int ybuttom, int ytop, COLORREF color)
	{
		outCode out1 = getOutCode(xs, ys, xleft, xright, ybuttom, ytop);
		outCode out2 = getOutCode(xe, ye, xleft, xright, ybuttom, ytop);

		while ((out1.all || out2.all) && !(out1.all & out2.all))
		{
			POINT v;
			if (out1.all)
			{
				if (out1.left)
					v = vIntersect(xs, ys, xe, ye, xleft);
				else if (out1.right)
					v = vIntersect(xs, ys, xe, ye, xright);
				else if (out1.buttom)
					v = hIntersect(xs, ys, xe, ye, ybuttom);
				else if (out1.top)
					v = hIntersect(xs, ys, xe, ye, ytop);
				xs = v.x;
				ys = v.y;
				out1 = getOutCode(xs, ys, xleft, xright, ybuttom, ytop);
			}
			else if (out2.all)
			{
				if (out2.left)
					v = vIntersect(xs, ys, xe, ye, xleft);
				else if (out2.right)
					v = vIntersect(xs, ys, xe, ye, xright);
				else if (out2.buttom)
					v = hIntersect(xs, ys, xe, ye, ybuttom);
				else if (out2.top)
					v = hIntersect(xs, ys, xe, ye, ytop);
				xe = v.x;
				ye = v.y;
				out2 = getOutCode(xe, ye, xleft, xright, ybuttom, ytop);
			}
		}
		if (!out1.all && !out2.all)
			d.DrawLineDDA(hdc, xs, ys, xe, ye, color);
	}

	~LineClip()
	{
	}
};

