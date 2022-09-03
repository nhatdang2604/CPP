#pragma once

#include "resource.h"
#include <string>
//#include <commdlg.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

												// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

/*---------------------------*/
/*Self-define global variable*/
/*---------------------------*/

//get Param from WndProc() function in Paint.cpp
WPARAM _wParam;
LPARAM _lParam;

//Button and button's images size
#define IMAGE_WIDTH     18
#define IMAGE_HEIGHT    18
#define BUTTON_WIDTH    0
#define BUTTON_HEIGHT   0

//Type of figure which was drawn
#define TYPE_NULL 0
#define TYPE_ELLIPSE 1
#define TYPE_RECTANGLE 2
#define TYPE_LINE 3
#define TYPE_CIRCLE 4
#define TYPE_SQUARE 5

//Type of mode
#define MODE_NULL 0
#define MODE_PREVIEW 1
#define MODE_DRAW 2
#define MODE_SELECT 3
#define MODE_DRAG 4

//Drawing global variable
int typeFigure = TYPE_NULL;	//type of figure which is being drawn
int fromX;
int fromY;
int toX;
int toY;
int mode;
RECT rcHWND;			//the rectangle of drawn space
RECT rcSelect;			//the dash dot rectangle when using select
RECT rcSelectOriginal;	//the dash dot rectangle after finish select mode and before start drag mode

//New/Open/Save/Save As stuff
bool isSaved = false;
std::wstring filePath = L"Untilted";

//Edit stuff
int dx, dy;	//to calculate vector while moving figure
bool isDragAfterDraw = false;	// If drag figure after drawing => false
								// else, if drag normally by using select => true
	



/*
//Color while drawing
CHOOSECOLOR  cc;
COLORREF  acrCustClr[16];
DWORD  rgbCurrent = RGB(255, 0, 0); 
HBRUSH  hbrush;*/