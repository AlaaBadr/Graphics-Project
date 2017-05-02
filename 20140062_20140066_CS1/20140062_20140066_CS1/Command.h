#include <string>
#include <vector>
#include <Windows.h>

#pragma once

using namespace std;

class Command
{
protected:
	string name;
	int numOfInput;
	vector<POINT> points;

public:

	Command()
	{
	}
	void setName(string name)
	{
		this->name = name;
	}
	string getName()
	{
		return name;
	}
	void setNumOfInput(int num)
	{
		numOfInput = num;
	}
	int getNumOfInput()
	{
		return numOfInput;
	}
	void input(POINT p)
	{
		points.push_back(p);
	}
	void doIt(HDC hdc)
	{

	}
	~Command()
	{
	}
};

