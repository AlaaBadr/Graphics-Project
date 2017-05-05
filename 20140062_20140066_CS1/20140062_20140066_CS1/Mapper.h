#pragma once
#include "DDALine.h"
#include "MidPointLine.h"
#include "ParametricLine.h"
#include "CartesianCirlce.h"
#include "PolarCircle.h"
#include "IterativePolarCircle.h"
#include "MidPointCircle.h"
#include "FirstDegreeCurve.h"
#include "SecondDegreeHalfCurve.h"
#include "SecondDegreeSlopeCurve.h"
#include "Hermite.h"
#include "Bezier.h"
#include "Splines.h"
#include "LineClip.h"
#include "PointClip.h"
#include "ConvexFill.h"
#include "resource.h"
class Mapper
{
public:

	Mapper()
	{
	}

	~Mapper()
	{
	}
	Command* getCommand(int id)
	{
		Command* current;
		switch (id)
		{
		case ID_DRAWLINE_DDA:
			current = new DDALine();
			current->setId(ID_DRAWLINE_DDA);
			break;
		case ID_DRAWLINE_PARAMETRIC:
			current = new ParametricLine();
			current->setId(ID_DRAWLINE_PARAMETRIC);
			break;
		case ID_DRAWLINE_MIDPOINT:
			current = new MidPointLine();
			current->setId(ID_DRAWLINE_MIDPOINT);
			break;
		case ID_DRAWCIRCLE_CARTESIAN:
			current = new CartesianCirlce();
			current->setId(ID_DRAWCIRCLE_CARTESIAN);
			break;
		case ID_DRAWCIRCLE_POLAR:
			current = new PolarCircle();
			current->setId(ID_DRAWCIRCLE_POLAR);
			break;
		case ID_DRAWCIRCLE_ITERATIVEPOLAR:
			current = new IterativePolarCircle();
			current->setId(ID_DRAWCIRCLE_ITERATIVEPOLAR);
			break;
		case ID_DRAWCIRCLE_MIDPOINT:
			current = new MidPointCircle();
			current->setId(ID_DRAWCIRCLE_MIDPOINT);
			break;
		case ID_DRAWCURVES_FIRSTDEGREE:
			current = new FirstDegreeCurve();
			current->setId(ID_DRAWCURVES_FIRSTDEGREE);
			break;
		case ID_SECONDDEGREE_HALFPOINT:
			current = new SecondDegreeHalfCurve();
			current->setId(ID_SECONDDEGREE_HALFPOINT);
			break;
		case ID_SECONDDEGREE_SLOPE:
			current = new SecondDegreeSlopeCurve();
			current->setId(ID_SECONDDEGREE_SLOPE);
			break;
		case ID_THIRDDEGREE_HERMITE:
			current = new Hermite();
			current->setId(ID_THIRDDEGREE_HERMITE);
			break;
		case ID_THIRDDEGREE_BEZIER:
			current = new Bezier();
			current->setId(ID_THIRDDEGREE_BEZIER);
			break;
		case ID_DRAWCURVES_SPLINES:
			current = new Splines();
			current->setId(ID_DRAWCURVES_SPLINES);
			break;
		case ID_CLIPPING_POINT:
			current = new PointClip();
			current->setId(ID_CLIPPING_POINT);
			break;
		case ID_CLIPPING_LINE:
			current = new LineClip();
			current->setId(ID_CLIPPING_LINE);
			break;
		case ID_FILLING_CONVEXFILLING:
			current = new ConvexFill();
			current->setId(ID_FILLING_CONVEXFILLING);
			break;
		default:
			current = new ConvexFill();
			break;
		}
		return current;
	}
	COLORREF getcolor(int id)
	{
		if (id == ID_DRAWINGCOLOR_RED || id == ID_BACKGROUNDCOLOR_RED)
			return RGB(255, 0, 0);
		if (id == ID_DRAWINGCOLOR_ORANGE || id == ID_BACKGROUNDCOLOR_ORANGE)
			return RGB(255, 125, 0);
		if (id == ID_DRAWINGCOLOR_YELLOW || id == ID_BACKGROUNDCOLOR_YELLOW)
			return RGB(255, 255, 0);
		if (id == ID_DRAWINGCOLOR_GREEN || id == ID_BACKGROUNDCOLOR_GREEN)
			return RGB(0, 255, 0);
		if (id == ID_DRAWINGCOLOR_CYAN || id == ID_BACKGROUNDCOLOR_CYAN)
			return RGB(0, 255, 255);
		if (id == ID_DRAWINGCOLOR_BLUE || id == ID_BACKGROUNDCOLOR_BLUE)
			return RGB(0, 0, 255);
		if (id == ID_DRAWINGCOLOR_VIOLET || id == ID_BACKGROUNDCOLOR_VIOLET)
			return RGB(125, 0, 255);
		if (id == ID_DRAWINGCOLOR_MAGENTA || id == ID_BACKGROUNDCOLOR_MAGENTA)
			return RGB(255, 0, 255);
		if (id == ID_DRAWINGCOLOR_BLACK || id == ID_BACKGROUNDCOLOR_BLACK)
			return RGB(0, 0, 0);
		if (id == ID_DRAWINGCOLOR_WHITE || id == ID_BACKGROUNDCOLOR_WHITE)
			return RGB(255, 255, 255);

	}
};

