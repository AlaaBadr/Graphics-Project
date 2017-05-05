#pragma once
#include "Command.h"
class ConvexFill :
	public Command
{
private:
	DDALine d;
public:

	ConvexFill()
	{
	}

	void doIt(HDC hdc)
	{
		ConvexFilling(hdc, &points[0], points.size(), color);
		//points.clear();
		//numOfInput = 0;
	}

	struct EdgeRecord
	{
		int xleft, xright;
		EdgeRecord(){}
		EdgeRecord(int x, int y)
		{
			xleft = x;
			xright = y;
		}
	};

	void InitEdgeRec(EdgeRecord *table, int n)
	{
		for (int i = 0; i < n; i++)
		{
			table[i].xleft = 2048;
			table[i].xright = 0;
		}
	}

	void FromEdgeToEdgeTable(POINT p1, POINT p2, EdgeRecord *table)
	{
		if (p1.y == p2.y)
			return;
		if (p1.y>p2.y)
			swap(p1, p2);

		int y = p1.y;
		double x = p1.x;
		double m = (p2.x - p1.x) / double(p2.y - p1.y);
		while (y < p2.y)
		{
			if (x < table[y].xleft)
				table[y].xleft = x;
			if (x>table[y].xright)
				table[y].xright = x;
			x += m;
			y++;
		}
	}

	void FromPolygonToEdgeTable(POINT *p, int n, EdgeRecord *table)
	{
		POINT v1 = p[n - 1];
		for (int i = 0; i < n; i++)
		{
			POINT v2 = p[i];
			FromEdgeToEdgeTable(v1, v2, table);
			v1 = p[i];
		}
	}

	void ConvexFilling(HDC hdc, POINT *p, int n, COLORREF color)
	{
		EdgeRecord *table = new EdgeRecord[800];
		InitEdgeRec(table, 800);
		FromPolygonToEdgeTable(p, n, table);
		for (int i = 0; i < 800; i++)
		{
			if (table[i].xleft <= table[i].xright)
			{
				d.DrawLineDDA(hdc, table[i].xleft, i, table[i].xright, i, color);
			}
		}
	}

	~ConvexFill()
	{
	}
};

