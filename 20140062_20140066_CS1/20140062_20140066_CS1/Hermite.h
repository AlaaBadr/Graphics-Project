#pragma once
#include "Command.h"

typedef double vect4[4];
typedef double mat4[4][4];

class Hermite :
	public Command
{
public:

	Hermite()
	{
	}

	void doIt(HDC hdc)
	{
		DrawCurveThirdDegreeHermite(hdc, points[0], points[1], points[2], points[3], color);
	}

	void mul(mat4 a, vect4 b, vect4 c)
	{
		for (int i = 0; i < 4; i++)
		{
			c[i] = 0;
			for (int j = 0; j < 4; j++)
			{
				c[i] += a[i][j] * b[j];
			}
		}
	}

	double dot(vect4 a, vect4 b)
	{
		double sum = 0;
		for (int i = 0; i < 4; i++)
		{
			sum += a[i] * b[i];
			//3ashan enta mot3eb
		}
		return sum;
	}

	void DrawCurveThirdDegreeHermite(HDC hdc, POINT p1, POINT t1, POINT p2, POINT t2, COLORREF color)
	{
		static mat4 H = { { 2, 1, -2, 1 }, { -3, -2, 3, -1 }, { 0, 1, 0, 0 }, { 1, 0, 0, 0 } };
		vect4 vx = { p1.x, t1.x, p2.x, t2.x };
		vect4 vy = { p1.y, t1.y, p2.y, t2.y };
		vect4 gx, gy;
		mul(H, vx, gx);
		mul(H, vy, gy);

		int n = max(abs(p2.x - p1.x), abs(p2.y - p1.y));
		double dt = 1.0 / n;
		double t = 0;
		for (int i = 0; i < n; i++)
		{
			double t2 = t * t;
			double t3 = t2 * t;
			vect4 vt = { t3, t2, t, 1 };
			double x = dot(gx, vt);
			double y = dot(gy, vt);
			SetPixel(hdc, round(x), round(y), color);
			t += dt;
		}
	}

	~Hermite()
	{
	}
};

