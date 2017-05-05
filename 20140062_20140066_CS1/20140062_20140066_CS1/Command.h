#include <string>
#include <vector>
#include <Windows.h>

#pragma once

using namespace std;

class Command
{
protected:
	int id;
	int numOfInput;
	vector<POINT> points;
	COLORREF color;

public:

	Command()
	{
		id = 0;
		numOfInput = 0;
		color = RGB(0, 0, 0);
	}
	void setId(int id)
	{
		this->id = id;
	}
	void setColor(COLORREF color)
	{
		this->color = color;
	}
	COLORREF getColor()
	{
		return color;
	}
	int getId()
	{
		return id;
	}
	void setPoints(vector<POINT> points)
	{
		this->points = points;
	}
	vector<POINT> getPoints()
	{
		return points;
	}
	void setNumOfInput(int num)
	{
		numOfInput = num;
	}
	int getNumOfInput()
	{
		return numOfInput;
	}
	void increment()
	{
		numOfInput++;
	}
	void input(POINT p)
	{
		points.push_back(p);
	}
	virtual void doIt(HDC hdc) = 0;
	~Command()
	{
	}
};

