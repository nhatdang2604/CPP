#pragma once
#ifndef _HANDLE_EVENT_H_
#define _HANDLE_EVENT_H_


#include "stdafx.h"

#include "Paint.h"
#include "Pen.h"
#include "Helper.h"
#include "HandleDraw.h"
#include "HandleFile.h"

#include <windowsx.h>
#include <commctrl.h>
#pragma comment(lib, "Comctl32.lib")


class HandleEvent {
public:
	static BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct) {

		//Get font from system
		LOGFONT lf;
		GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
		HFONT hFont = CreateFont(lf.lfHeight, lf.lfWidth,
			lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
			lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
			lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
			lf.lfPitchAndFamily, lf.lfFaceName
		);

		//Create dialog
		InitCommonControls();

		//Add new, open and save button (3 default buttons)
		TBBUTTON tbButtons[] =
		{
			{ STD_FILENEW,	ID_FILE_NEW, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
			{ STD_FILEOPEN,	ID_FILE_OPEN, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
			{ STD_FILESAVE,	ID_FILE_SAVE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 }
		};

		HWND hToolBarWnd = CreateToolbarEx(hwnd,
			WS_CHILD | WS_VISIBLE | CCS_ADJUSTABLE | TBSTYLE_TOOLTIPS,
			ID_TOOLBAR, sizeof(tbButtons) / sizeof(TBBUTTON), HINST_COMMCTRL,
			0, tbButtons, sizeof(tbButtons) / sizeof(TBBUTTON),
			BUTTON_WIDTH, BUTTON_HEIGHT, IMAGE_WIDTH, IMAGE_HEIGHT,
			sizeof(TBBUTTON));
		
		/*
		TBBUTTON buttonsToAdd[] =
		{
			{ 0, 0,	TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0 }, // Nút phân cách
			{ STD_CUT,	ID_EDIT_CUT, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
			{ STD_COPY,	ID_EDIT_COPY, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
			{ STD_PASTE, ID_EDIT_PASTE,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
			{ STD_DELETE, ID_EDIT_DELETE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 }
		};
		SendMessage(hToolBarWnd, TB_ADDBUTTONS, (WPARAM) sizeof(buttonsToAdd) / sizeof(TBBUTTON),
			(LPARAM)(LPTBBUTTON)&buttonsToAdd);
		*/
		
		//Add shape draw buttons
		TBBUTTON userButtons[] =
		{

			{ 0, 0,	TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0 },
			{ 0, ID_DRAW_UNDO,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
			{ 1, ID_DRAW_REDO,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
			{ 2, ID_DRAW_ELLIPSE,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
			{ 3, ID_DRAW_RECTANGLE,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
			{ 4, ID_DRAW_LINE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
			{ 5, ID_DRAW_SELECT, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 }
		};
		
		
		TBADDBITMAP	tbBitmap = { hInst, IDB_BITMAP1 };
		
		int idx = SendMessage(hToolBarWnd, TB_ADDBITMAP, (WPARAM) sizeof(tbBitmap) / sizeof(TBADDBITMAP),
			(LPARAM)(LPTBADDBITMAP)&tbBitmap);
		
		userButtons[1].iBitmap += idx;
		userButtons[2].iBitmap += idx;
		userButtons[3].iBitmap += idx;
		userButtons[4].iBitmap += idx;
		userButtons[5].iBitmap += idx;
		userButtons[6].iBitmap += idx;

		SendMessage(hToolBarWnd, TB_ADDBUTTONS, (WPARAM) sizeof(userButtons) / sizeof(TBBUTTON),
			(LPARAM)(LPTBBUTTON)&userButtons);

		return TRUE;

	}


	static void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify) {

		if (IDM_ABOUT == id) {
			DialogBoxW(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hwnd, About);
			return;
		}

		if (IDM_FILE_EXIT == id) {
			DestroyWindow(hwnd);
			return;
		}

		if (ID_DRAW_ELLIPSE == id) {
			if (isDragAfterDraw) {
				HandleDraw::finishToDrag(states);
				isDragAfterDraw = false;
			}
			mode = MODE_NULL;
			typeFigure = TYPE_ELLIPSE;
			return;
		} 

		if (ID_DRAW_RECTANGLE == id) {
			if (isDragAfterDraw) {
				HandleDraw::finishToDrag(states);
				isDragAfterDraw = false;
			}
			mode = MODE_NULL;
			typeFigure = TYPE_RECTANGLE;
			return;
			}
			
		if (ID_DRAW_LINE == id) {
			if (isDragAfterDraw) {
				HandleDraw::finishToDrag(states);
				isDragAfterDraw = false;
			}
			mode = MODE_NULL;
			typeFigure = TYPE_LINE;
			return;
		}

		if (ID_DRAW_SELECT == id) {
			//typeFigure = TYPE_RECTANGLE;
			if (isDragAfterDraw) {
				HandleDraw::finishToDrag(states);
				isDragAfterDraw = false;
			}
			typeFigure = TYPE_NULL;
			mode = MODE_SELECT;
			return;
		}

		if (ID_FILE_NEW == id || IDM_FILE_NEW == id) {
			HandleFile::New(hwnd);
			return;
		}

		if (ID_FILE_OPEN == id || IDM_FILE_OPEN == id) {
			HandleFile::Open(hwnd);
			return;
		}

		if (ID_FILE_SAVE == id || IDM_FILE_SAVE == id) {
			HandleFile::Save(hwnd);
			return;
		}

		if (IDM_FILE_SAVEAS == id) {
			HandleFile::SaveAs(hwnd);
			return;
		}

		if (IDM_CHOOSE_COLOR == id) {
			
			HandleDraw::getColor(hwnd);
			//if (MODE_DRAG == mode) {
			//	RedrawWindow(hwnd, &rcHWND, NULL, RDW_UPDATENOW);
			//}
			return;
		}
	}

	static void OnKey(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags) {
		
		if (GetKeyState(VK_CONTROL) < 0) {
				if ('S' == vk) HandleFile::Save(hwnd);	//Ctrl + S => Save
		   else if ('O' == vk) HandleFile::Open(hwnd);	//Ctrl + O => Open
		   else if ('N' == vk) HandleFile::New(hwnd);	//Ctrl + N => New
				return;
			}
		
		if (VK_F12 == vk) HandleFile::SaveAs(hwnd);		//F12 => Save As
	}

	static void OnDestroy(HWND hwnd) {
		PostQuitMessage(0);
	}

	/*On pain :<*/
	static void OnPaint(HWND hwnd) {
		HandleDraw::draw(hwnd);
	}

	static void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags) {
		if (MODE_DRAG == mode) {

			//If cursor isn't in the rcSelect
			//	=> Finish to drag 
			if (!(rcSelect.left <= x && x <= rcSelect.right &&
				rcSelect.top <= y && y <= rcSelect.bottom)) {
				
				//If there are no figures in rcSelectOriginal => drag nothing
				HandleDraw::finishToDrag(states);

				
				if (!isDragAfterDraw) mode = MODE_SELECT;	//Setup to begin mode select (when in normal drag mode)
				else {
					mode = MODE_PREVIEW;					//Setup to begin preview select (when dragging after draw)
					isDragAfterDraw = false;
				}
			}
		}

		//Activate preview mode
		if (MODE_NULL == mode ) mode = MODE_PREVIEW;
		else if (MODE_SELECT == mode) typeFigure = TYPE_RECTANGLE;

		//Get the mouse's start position
		fromX = x;
		fromY = y;
		toX = x;
		toY = y;

		//If we are selecting
		//	=> Initialize the selecting rectangle cordinates 
		if (MODE_SELECT == mode) {
			rcSelect.left = x;
			rcSelect.top = y;
			rcSelect.right = x;
			rcSelect.bottom = y;
		}

		HDC hdc = GetDC(hwnd);
		MoveToEx(hdc, fromX, fromY, NULL);
	}

	static void OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags) {
		if (TYPE_NULL == typeFigure) return;

		//After preview mode
		if (MODE_PREVIEW == mode) {

			//Activate draw mode
			mode = MODE_DRAW;
		}

		InvalidateRect(hwnd, &rcHWND, FALSE);
		UpdateWindow(hwnd);

		//After draw mode
		if (MODE_DRAW == mode) {

			//Activate Drag mode
			mode = MODE_SELECT;

			//Save the 4 corner of a figure after draw it
			rcSelect.left = fromX;
			rcSelect.top = fromY;
			rcSelect.right = toX;
			rcSelect.bottom = toY;

			//Swap left, top, right, bottom of rcSelect to correct position
			Helper::standardlizeRect(rcSelect);

			//Update the original position of rcSelect
			rcSelectOriginal = rcSelect;
			
			//Save the current type of figure
			int saved = typeFigure;

			//Set the type of figure for rcSelect
			typeFigure = TYPE_RECTANGLE;

			//Draw rcSelect (Cause we are in select mode)
			InvalidateRect(hwnd, &rcHWND, FALSE);
			UpdateWindow(hwnd);
			
			//End Select mode, activate drag mode
			mode = MODE_DRAG;

			//Restore type of figure
			typeFigure = saved;

			isDragAfterDraw = true;
			return;
		}

		//After select mode
		if (MODE_SELECT == mode) {

			//Swap left, top, right, bottom of rcSelect to correct position
			Helper::standardlizeRect(rcSelect);

			//Save the original position of rcSelect
			rcSelectOriginal = rcSelect;

			//Activate drag mode
			mode = MODE_DRAG;
			return;
		}

	}

	static void OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags) {
		if (TYPE_NULL == typeFigure) return;

		//Hold SHIFT while chosing Ellipse (or Rectangle)
		//	=> Draw Circle (or Square)
		if (_wParam & MK_SHIFT) {
			if (TYPE_ELLIPSE == typeFigure) typeFigure = TYPE_CIRCLE;
			else if (TYPE_RECTANGLE == typeFigure) typeFigure = TYPE_SQUARE;
		}
		else {

			//Release SHIFT while drawing Circle (or Square)
			//	=> Return to Ellipse (or Rectangle)
			if (TYPE_CIRCLE == typeFigure) typeFigure = TYPE_ELLIPSE;
			else if (TYPE_SQUARE == typeFigure) typeFigure = TYPE_RECTANGLE;
		}

		//Every moment, delete the preview object 
		//(this make every moment, there is only 1 preview object existing)
		if (MODE_PREVIEW == mode || MODE_SELECT == mode) {

			//Get the mouse current position
			toX = x;
			toY = y;

			//If we are selecting
			//	=>Update the cordinates of the selecting cordinates
			if (MODE_SELECT == mode) {
				rcSelect.right = x;
				rcSelect.bottom = y;
			}

			InvalidateRect(hwnd, &rcHWND, FALSE);
			return;
		}

		//In drag mode
		if (MODE_DRAG == mode) {

			//Hold left mouse button
			if (GetKeyState(VK_LBUTTON) < 0) {
				toX = x;
				toY = y;

				dx = toX - fromX;
				dy = toY - fromY;

				rcSelect.left += dx;
				rcSelect.top += dy;
				rcSelect.right += dx;
				rcSelect.bottom += dy;

				InvalidateRect(hwnd, &rcHWND, FALSE);

				fromX = x;
				fromY = y;
			}

		}
	}


};



#endif // !_HANDLE_EVENT_H_

