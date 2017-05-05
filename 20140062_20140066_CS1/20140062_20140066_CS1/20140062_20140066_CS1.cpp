// 20140062_20140066_CS1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "DDALine.h"
#include "MidPointLine.h"
#include "ParametricLine.h"
#include "CartesianCirlce.h"
#include "PolarCircle.h"
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
#include "20140062_20140066_CS1.h"
#include "Mapper.h"
#include <fstream>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
Mapper mapper;
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY20140062_20140066_CS1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY20140062_20140066_CS1));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY20140062_20140066_CS1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY20140062_20140066_CS1);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
void Save(vector<Command*> history)
{
	fstream file("history.txt",ios::out);
	for (int i = 0; i < history.size(); i++)
	{
		file << history[i]->getId() << endl;
		file << history[i]->getNumOfInput() << endl;
		vector<POINT> points = history[i]->getPoints();

		for (int j = 0; j <points.size(); j++)
		{
			file << points[j].x << " " << points[j].y << endl;
		}
		file << history[i]->getColor()<<endl;
	}
	file.close();
		
}
void Load(HDC hdc)
{
	fstream file("History.txt", ios::in);
	Command* current;
	int id;
	while (!file.eof())
	{
		file >> id;
		if (file.eof())
			break;
		current = mapper.getCommand(id);
		int numberofInput;
		file >> numberofInput;
		current->setNumOfInput(numberofInput);
		for (int i = 0; i < numberofInput; i++)
		{
			POINT tmp;
			file >> tmp.x >> tmp.y;
			current->input(tmp);
		}
		COLORREF color;
		file >> color;
		current->setColor(color);
		current->doIt(hdc);
	}
	file.close();
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	static Command *current;
	static COLORREF drawingcolor = RGB(0,0,0);
	static COLORREF backgroundcolor= RGB(255,255,255);
	static int currentID;
	static vector<Command*> history;
	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		if (wmId == IDM_ABOUT)
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		}
		else if (wmId == IDM_EXIT)
		{
			DestroyWindow(hWnd);
		}
		else if (wmId == ID_FILE_SAVE)
		{
			Save(history);
		}
		else if (wmId == ID_FILE_LOAD)
		{
			hdc = GetDC(hWnd);
			Load(hdc);
			ReleaseDC(hWnd, hdc);
		}
		else if (wmId >= ID_DRAWINGCOLOR_RED && wmId <= ID_DRAWINGCOLOR_WHITE)
		{
			drawingcolor = mapper.getcolor(wmId);
		}
		else if (wmId >= ID_BACKGROUNDCOLOR_RED && wmId <= ID_BACKGROUNDCOLOR_WHITE)
		{
			backgroundcolor = mapper.getcolor(wmId);
			Command* current = mapper.getCommand(ID_FILLING_CONVEXFILLING);
			current->setColor(backgroundcolor);
			RECT window;
			GetClientRect(hWnd, &window);
			POINT tmp;
			tmp.x = window.left;
			tmp.y = window.top;
			current->input(tmp);
			current->increment();

			tmp.x = window.right;
			tmp.y = window.top;
			current->input(tmp);
			current->increment();

			tmp.x = window.right;
			tmp.y = window.bottom;
			current->input(tmp);
			current->increment();

			tmp.x = window.left;
			tmp.y = window.bottom;
			current->input(tmp);
			current->increment();

			Save(history);
			hdc = GetDC(hWnd);
			current->doIt(hdc);
			Load(hdc);
			ReleaseDC(hWnd, hdc);

		}
		else
		{
			current = mapper.getCommand(wmId);
			currentID = current->getId();
		}
		break;
	//case WM_PAINT:
	//	hdc = BeginPaint(hWnd, &ps);
	//	// TODO: Add any drawing code here...
	//	EndPaint(hWnd, &ps);
	//	break;
	case WM_LBUTTONDOWN:
		POINT p;
		p.x = LOWORD(lParam);
		p.y = HIWORD(lParam);
		current->input(p);
		current->increment();
		break;
	case WM_RBUTTONDOWN:
		hdc = GetDC(hWnd);
		current->setColor(drawingcolor);
		current->doIt(hdc);
		ReleaseDC(hWnd, hdc);
		history.push_back(current);
		current = mapper.getCommand(currentID);
		break;
	case WM_DESTROY:
		//for (int i = 0; i < history.size(); i++)
		//{
		//	free(history[i]);
		//}
		//free(&history[0]);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
