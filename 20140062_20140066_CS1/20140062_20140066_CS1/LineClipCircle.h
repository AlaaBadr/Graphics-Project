#pragma once
#include "Command.h"
#include "DDALine.h"
#include "CartesianCirlce.h"
class LineClipCircle :
	public Command
{
private:
	DDALine d;
	CartesianCirlce c;
public:

	LineClipCircle()
	{
	}

	void doIt(HDC hdc)
	{
		CircleLineClipping(hdc, points[0].x, points[0].y, distance(points[0], points[1]), points[2].x, points[2].y, points[3].x, points[3].y, color);
	}

	int distance(POINT p1, POINT p2)
	{
		return sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
	}

	void CircleLineClipping(HDC hdc, int xc, int yc, double R, int xs, int ys, int xe, int ye, COLORREF color)
	{
		c.DrawCircleCartesianDirectMethod(hdc, xc, yc, R, RGB(180, 180, 180));
		double d1 = ((xs - xc)*(xs - xc)) + ((ys - yc)*(ys - yc)) - (R*R);
		double d2 = ((xe - xc)*(xe - xc)) + ((ye - yc)*(ye - yc)) - (R*R);
		if (d1 <= 0 && d2 <= 0)
		{
			d.DrawLineDDA(hdc, xs, ys, xe, ye, color);
			return;
		}
		double m = (ye - ys) / (double)(xe - xs);
		double c = ys - m*xs;
		double A, B, C;
		A = (1 + (m*m));
		B = 2 * ((m*c) - (m*yc) - (xc));
		C = (xc*xc) + ((c - yc)*(c - yc)) - (R*R);
		if ((B*B) - (4.0 * A*C) >= 0)
		{
			double x1 = ((-1 * B) - (sqrt((B*B) - (4.0 * A*C)))) / (2.0*A);
			double y1 = (m*x1) + c;
			double x2 = ((-1 * B) + (sqrt((B*B) - (4.0 * A*C)))) / (2.0*A);
			double y2 = (m*x2) + c;
			if (d1 <= 0 && d2 > 0)
			{
				if (x2 >= min(xs, xe) && x2 <= max(xs, xe))
					d.DrawLineDDA(hdc, xs, ys, x2, y2, color);
				else if (x1 >= min(xs, xe) && x1 <= max(xs, xe))
					d.DrawLineDDA(hdc, xs, ys, x1, y1, color);
			}
			else if (d1 > 0 && d2 <= 0)
			{
				if (x2 >= min(xs, xe) && x2 <= max(xs, xe))
					d.DrawLineDDA(hdc, x2, y2, xe, ye, color);
				else if (x1 >= min(xs, xe) && x1 <= max(xs, xe))
					d.DrawLineDDA(hdc, x1, y1, xe, ye, color);
			}
			else
			{
				if (x1 >= min(xs, xe) && x1 <= max(xs, xe))
					d.DrawLineDDA(hdc, x1, y1, x2, y2, color);
			}
		}

	}

	~LineClipCircle()
	{
	}
};

