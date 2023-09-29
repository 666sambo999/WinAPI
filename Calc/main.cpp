#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include"resource.h"
#include"resource1.h"
//#include"button.h"
#include<cstdio>

CONST CHAR g_sz_WINDOWS_CLASS[] = "Calculator the best";
CONST CHAR g_sz_DEFAULT_THEME[] = "Calc"; 
// g- global 
// sz - String Zero; 
CONST INT g_i_START_x = 10; 
CONST INT g_i_START_y = 10;

CONST INT g_i_INTERVAL = 10; 
CONST INT g_i_BTN_SIZE = 60;
CONST INT g_i_DISPLAY_HEIDHT = 50;
CONST INT g_i_DISPLAY_WIDTH = g_i_BTN_SIZE * 5+ g_i_INTERVAL*4;

CONST INT g_i_BTN_SIZE_WITH_INTERVAL = g_i_BTN_SIZE + g_i_INTERVAL;
CONST INT g_i_BTN_SIZE_DOUBLE = g_i_BTN_SIZE*2+g_i_INTERVAL;

CONST INT g_i_BTN_START_x = g_i_START_x;
CONST INT g_i_BTN_START_y = g_i_START_y+ g_i_DISPLAY_HEIDHT + g_i_INTERVAL;

CONST INT g_i_WINDOWS_WIDTH = g_i_DISPLAY_WIDTH + g_i_BTN_START_x * 2+15;
CONST INT g_i_WINDOWS_HEIDTH = g_i_DISPLAY_HEIDHT + g_i_START_y*3 + g_i_BTN_SIZE_WITH_INTERVAL*4 +30;

CONST CHAR g_OPERATION[] = "+-*/";

CONST CHAR g_i_DISPLAY_FONT[] = "Alabama";
CONST INT g_i_DISPLAY_FONT_HEIGHT = g_i_DISPLAY_HEIDHT - 2; 
CONST INT g_i_DISPLAY_FONT_WIDTH = g_i_DISPLAY_FONT_HEIGHT/ 2.5; 

CONST COLORREF g_cr_BLACK = RGB(10, 10, 10);
CONST COLORREF g_cr_SQUARE = RGB(128, 128, 128);

CONST HBRUSH hBrushSquare = CreateSolidBrush(RGB(91, 91, 89));	// кисточки 
CONST HBRUSH hBrushBlack = CreateSolidBrush(RGB(10, 10, 10));

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//VOID SetTheme(HWND hwnd);
VOID SetTheme(HWND hwnd, CONST CHAR sz_theme[]);

INT WINAPI  WinMain(HINSTANCE hInstante, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1) Регистрация класса окна 
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));
	
	wc.cbSize = sizeof(wc);
	wc.cbWndExtra = 0;
	wc.style = 0;
	wc.cbWndExtra = 0;

	wc.hIcon = (HICON)LoadIcon(hInstante, MAKEINTRESOURCE(IDI_ICON_CALK));
	wc.hIconSm = (HICON)LoadImage(hInstante, "calculation.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hCursor = (HCURSOR)LoadImage(hInstante, "Busy.ani", IMAGE_CURSOR, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	//wc.hbrBackground = CreateSolidBrush(RGB(128, 128, 128));		// меняем цвет панели через класс
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW; 

	wc.hInstance = hInstante;
	wc.lpszMenuName = 0;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = g_sz_WINDOWS_CLASS; 
	
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	//2) Создание окна 
	HWND hwnd = CreateWindowEx
	(
		NULL,
		g_sz_WINDOWS_CLASS,
		g_sz_WINDOWS_CLASS,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		g_i_WINDOWS_WIDTH,g_i_WINDOWS_HEIDTH,  
		NULL,
		NULL,
		hInstante,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Windows creation failed", "Error", MB_OK | MB_ICONERROR);
		return 0; 
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	//3) Запуск цикла сообщений  
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static DOUBLE a = 0; // не сохраняем в переменную а, только в переменную b 
	static DOUBLE b = 0;		// static = будет храниться в области памяти(глобальной), инициализация переменной происходит только один раз  
	static INT operation = 0;
	static BOOL input = FALSE;
	static BOOL operation_input = false; 

	static HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 240));
	static CHAR sz_theme[FILENAME_MAX] = {};
	switch (uMsg)
	{
	case WM_CREATE:
	{
		HWND hDisplay = CreateWindowEx
		(
			NULL, "Static", "0",
			WS_CHILD | WS_VISIBLE | SS_RIGHT| SS_SUNKEN|SS_CENTERIMAGE,
			g_i_START_x, g_i_START_y,
			g_i_DISPLAY_WIDTH,g_i_DISPLAY_HEIDHT,
			hwnd, 
			(HMENU)IDC_STATIC,
			GetModuleHandle(NULL),
			NULL
		);
		//SendMessage(hDisplay, WM_SETTEXT, 0, (LPARAM)"Display");
		//LOGFONT lFont; 
		//ZeroMemory(&lFont, sizeof(lFont));
		//lFont.lfHeight = 24;
		//lFont.lfWidth = 14;
		//lFont.lfEscapement = 6;		// наклон 
		//lFont.lfOrientation = 0;
		//lFont.lfWeight = FW_DEMIBOLD;		// жирность шрифта 
		//lFont.lfItalic = FALSE;			// курсив 
		//lFont.lfUnderline = FALSE;		// подчеркивание 
		//lFont.lfStrikeOut = FALSE;		// перечеркнутый 
		//lFont.lfCharSet = DEFAULT_CHARSET; 	// 
		//lFont.lfOutPrecision = OUT_TT_PRECIS; 
		//lFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
		//lFont.lfQuality = ANTIALIASED_QUALITY;
		//lFont.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
		//strcpy (lFont.lfFaceName, "Arial");

		//HFONT hFont = CreateFontIndirect(&lFont);
		HFONT hFont = CreateFont
		(
			g_i_DISPLAY_HEIDHT,g_i_DISPLAY_FONT_WIDTH,
			GM_ADVANCED, 0, FW_DEMIBOLD,
			FALSE, 0, 0,
			DEFAULT_CHARSET,
			OUT_CHARACTER_PRECIS,
			CLIP_CHARACTER_PRECIS, 
			ANTIALIASED_QUALITY,
			DEFAULT_PITCH| FF_DONTCARE,
			g_i_DISPLAY_FONT
		);
		SendMessage(hDisplay, WM_SETFONT, (WPARAM)hFont, TRUE);

		INT i_digit = 1;
		CHAR sz_digit[2] = {};
		/*for (int i = 3; i > 0; i--)
		{
			for (int j = 0; j < 3; j++)
			{
				sz_digit[0] = i_digit + (char)48;
				CreateWindowEx
				(
					NULL, "BUTTON", sz_digit,
					WS_CHILDWINDOW | WS_VISIBLE|BS_PUSHBUTTON,
					g_i_START_x + g_i_BTN_SIZE_WITH_INTERVAL * j,
					g_i_START_y + g_i_BTN_SIZE_WITH_INTERVAL * i,
					g_i_BTN_SIZE, g_i_BTN_SIZE,
					hwnd,
					(HMENU)IDC_BUTTON_0 + i_digit,
					GetModuleHandle(NULL),
					NULL
				);
				i_digit++;
			}*/
			for (int i = 2; i >= 0; i--)
			{
				for (int j = 0; j < 3; j++)
				{
					sz_digit[0] = i_digit + (char)48;
					CreateWindowEx
					(
						NULL, "BUTTON", sz_digit,
						WS_CHILDWINDOW | WS_VISIBLE | BS_PUSHBUTTON| BS_BITMAP,
						g_i_BTN_START_x + g_i_BTN_SIZE_WITH_INTERVAL * j,
						g_i_BTN_START_y + g_i_BTN_SIZE_WITH_INTERVAL * i,
						g_i_BTN_SIZE, g_i_BTN_SIZE,
						hwnd,
						(HMENU)(IDC_BUTTON_0 + i_digit),
						GetModuleHandle(NULL),
						NULL
					);
					i_digit++;
				}
			}
		/////////////////////////////////////////////////////////////////
		CreateWindowEx
		(
			NULL, "BUTTON", "0",
			WS_CHILDWINDOW | WS_VISIBLE | BS_PUSHBUTTON |BS_BITMAP,
			g_i_BTN_START_x, g_i_BTN_START_y+ g_i_BTN_SIZE_WITH_INTERVAL*3,
			g_i_BTN_SIZE_DOUBLE,g_i_BTN_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_0,
			GetModuleHandle(NULL),
			NULL
		);
		//strcpy(sz_skin, g_sz_DEFAULT_SKIN);
		strcpy(sz_theme, g_sz_DEFAULT_THEME);
		SetTheme(hwnd, g_sz_DEFAULT_THEME);

		/////////////////////////////////////////////////////////////////////
		CreateWindowEx
		(
			NULL, "BUTTON", ".",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_BTN_START_x + g_i_BTN_SIZE_WITH_INTERVAL*2, // расположение по х
			g_i_BTN_START_y + g_i_BTN_SIZE_WITH_INTERVAL*3,
			g_i_BTN_SIZE,g_i_BTN_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_POINT,
			GetModuleHandle(NULL),
			NULL
		);
		INT i_operation = 0;
		CHAR sz_operation[2] = {};
		for (int i = 3; i >=0; i--)
		{
			sz_operation[0] = g_OPERATION[i];
			CreateWindowEx
			(
				NULL, "BUTTON", sz_operation,
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				g_i_BTN_START_x + g_i_BTN_SIZE_WITH_INTERVAL * 3, g_i_BTN_START_y+ g_i_BTN_SIZE_WITH_INTERVAL * (3-i),
				g_i_BTN_SIZE, g_i_BTN_SIZE,
				hwnd,
				(HMENU)(IDC_BUTTON_PLUS + i),
				GetModuleHandle(NULL),
				NULL
			);
		}
		//HWND hBtnPlus = GetDlgItem(hwnd, IDC_BUTTON_PLUS);
		//HBITMAP hBitMap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_PLUS)); // через ф-ю GetModuleHandle можно получить hInstante
		//SendMessage(hBtnPlus, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitMap); 
		

		CreateWindowEx
		(
			NULL,"BUTTON", "<-",
			WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
			g_i_BTN_START_x + g_i_BTN_SIZE_WITH_INTERVAL*4, g_i_BTN_START_y,
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd, 
			(HMENU)IDC_BUTTON_BSP,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "BUTTON", "C",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_BTN_START_x + g_i_BTN_SIZE_WITH_INTERVAL * 4, g_i_BTN_START_y+g_i_BTN_SIZE_WITH_INTERVAL,
			g_i_BTN_SIZE, g_i_BTN_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_CLEAR,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "BUTTON", "=",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_BTN_START_x + g_i_BTN_SIZE_WITH_INTERVAL * 4, g_i_BTN_START_y + g_i_BTN_SIZE_WITH_INTERVAL*2,
			g_i_BTN_SIZE, g_i_BTN_SIZE_DOUBLE, // расположение на консоле(размер кнопки)
			hwnd,
			(HMENU)IDC_BUTTON_EQUAL,
			GetModuleHandle(NULL),
			NULL
		);
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT hPaint;
		HDC hdc = BeginPaint(hwnd, &hPaint); 
		FillRect(hdc, &hPaint.rcPaint, hBrush);
	}
	break;
	case WM_CTLCOLORSTATIC:					// цвет шрифта на дисплее
	{
		if((HWND)lParam == GetDlgItem(hwnd, IDC_STATIC))
		{
			HDC hdc = (HDC)wParam;
			SetDCBrushColor(hdc, RGB(100, 100, 100));
			SetBkMode(hdc, OPAQUE);
			SetTextColor(hdc, RGB(100, 100, 100));
			return (INT)GetStockObject(DC_BRUSH);
		}
	}
	break; 
	case WM_CTLCOLOREDIT:
	{
		HDC hdc = (HDC)wParam;
		SetBkMode(hdc, OPAQUE);
		SetBkColor(hdc, RGB(0, 0, 200)); HBRUSH hBruch = CreateSolidBrush(RGB(0, 100, 250));
		SetTextColor(hdc, RGB(255, 0, 0));
		return (LRESULT)hBruch;
	}
	break; 
	case WM_COMMAND:
	{
		CONST INT SIZE = 256; 
		CHAR sz_buffer[SIZE] = {};
		HWND hStatic = GetDlgItem(hwnd, IDC_STATIC);
		SendMessage(hStatic, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
		if (LOWORD(wParam) >= IDC_BUTTON_0 && LOWORD(wParam) <= IDC_BUTTON_9|| LOWORD(wParam) == IDC_BUTTON_POINT)
		{
			DOUBLE d_buffer = atof(sz_buffer);
			if (d_buffer == a)
			{
				SendMessage(hStatic, WM_SETTEXT, SIZE, (LPARAM)"");
				sz_buffer[0] = 0;		// зануляем буффер 
			}
			CHAR sz_symbol[2] = {};
			sz_symbol[0] = CHAR(LOWORD(wParam) - IDC_BUTTON_0 + '0'); // в char прилетает значение, потом мы вычетаем IDC-button  и + ACII код 0(48)
			if (LOWORD(wParam) == IDC_BUTTON_POINT)			
			{
				if (strchr(sz_buffer,'.'))break;
				sz_symbol[0] = '.';
			}
			/*if (strcmp(sz_buffer, "0") == 0)
			{
				SendMessage(hStatic, WM_SETTEXT, 0, (LPARAM)"");
				sz_buffer[0] == CHAR(LOWORD(wParam) - IDC_BUTTON_0 + '0');
				SendMessage (hStatic, WM_SETTEXT, )
			}*/
			strcat(sz_buffer, sz_symbol);
			SendMessage(hStatic, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			input = TRUE;
		}
		if (LOWORD(wParam) == IDC_BUTTON_CLEAR)
		{
			SendMessage(hStatic, WM_SETTEXT, 0, (LPARAM)"");
			a = b = operation = 0;
			input = FALSE;
			operation_input = FALSE;
		}
		if (LOWORD(wParam) == IDC_BUTTON_BSP)
		{
			if (strcmp(sz_buffer, "0") == 0 || strlen (sz_buffer) == 0)break;  // strcmp = строка, на конце стоит 0;
			sz_buffer[strlen(sz_buffer) - 1] = 0;
			SendMessage(hStatic, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		if (LOWORD(wParam) >= IDC_BUTTON_PLUS && LOWORD(wParam) <= IDC_BUTTON_SLASH) // кнопки 
		{
			SendMessage(hStatic, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			if (input)
			{
				b = atof(sz_buffer);
				input = FALSE;
			}
			if (a == 0)a = b;
			SendMessage(hwnd, WM_COMMAND,IDC_BUTTON_EQUAL,0);
			operation = LOWORD(wParam);
			/*switch (LOWORD(wParam))
			{
			case IDC_BUTTON_PLUS: operation = '+';		break;
			case IDC_BUTTON_MINUS: operation = '-';		break;
			case IDC_BUTTON_ASTER: operation = '*';		break;
			case IDC_BUTTON_SLASH: operation = '/';		break;
			}*/
			operation_input = TRUE; 
		}
		if (LOWORD(wParam) == IDC_BUTTON_EQUAL)
		{
			if (input)
			{
				SendMessage(hStatic, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
				b = atof(sz_buffer);
				input = FALSE;
			}
			/*switch (operation)
			{
			case '+':  a += b;	break;
			case '-':  a -= b;	break;
			case '*':  a *= b;	break;
			case '/':  a /= b;	break;
			}*/
			switch (operation)
			{
			case IDC_BUTTON_PLUS:	a += b;		break;
			case IDC_BUTTON_MINUS:	a -= b;		break;
			case IDC_BUTTON_ASTER:	a *= b;		break;
			case IDC_BUTTON_SLASH:	a /= b;		break;
			}
			operation_input = FALSE;
			sprintf(sz_buffer, "%F", a);
			SendMessage(hStatic, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		SetFocus(hwnd);
	}
	break; 
	case WM_KEYDOWN:
	{
		if (GetKeyState(VK_SHIFT) < 0)
		{
			if (wParam == 0x38)SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_ASTER, 0);
		}
		else if (wParam >= 0x30 && wParam <= 0x39)	// цифры от 0 до 9 
		{
			SendMessage(hwnd, WM_COMMAND, wParam - 0x30 + 1000, 0); // мы отправляем сообщение нашему окну(WM_COMMAND) 0x30 - ноль в 16-системе(48)/ обратная формула 
		}// фокус - это часть окна, которая принимает команды с клавиатуры 
		if (LOWORD(wParam) >= 0x60 && LOWORD(wParam) <= 0x69)
		{
			SendMessage(hwnd, WM_COMMAND, wParam - 0x60 + 1000, 0);
		}
		switch (LOWORD(wParam))
		{
		case VK_OEM_PLUS:	SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_PLUS, 0);	break;
		case VK_OEM_MINUS:	SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_MINUS, 0); break;
		case VK_MULTIPLY:	SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_ASTER, 0); break;
		case VK_OEM_2: 
		case VK_DIVIDE:		SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_SLASH, 0); break;
		case VK_RETURN:		SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_EQUAL, 0); break; 
		case VK_ESCAPE:		SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_CLEAR, 0); break; 
		case VK_BACK:		SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_BSP, 0);	break;
		case VK_OEM_PERIOD: SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_POINT, 0); break; 
		}
	}
		break;
	case WM_CONTEXTMENU:		// создание с помощью контексного меню
	{
		HMENU hMenu = CreatePopupMenu();			// пустое меню
		InsertMenu(hMenu, 0, MF_BYPOSITION | MF_STRING, IDC_EXIT, "Exit");
		InsertMenu(hMenu, 0, MF_BYPOSITION | MF_SEPARATOR, 0, NULL);			// появляется полоска, отделяет выход 
		InsertMenu(hMenu, 0, MF_BYPOSITION | MF_STRING, IDC_SQUARE, "Square button");
		InsertMenu(hMenu, 0, MF_BYPOSITION | MF_STRING, IDC_BLACK, "Black button");

		switch (TrackPopupMenuEx(hMenu, TPM_BOTTOMALIGN | TPM_LEFTALIGN | TPM_RETURNCMD, LOWORD(lParam), HIWORD(lParam), hwnd, NULL))
		{
		//case IDC_BLACK: SetTheme(hwnd, "Calc");  break;
		//case IDC_SQUARE: SetTheme(hwnd, "Button"); break;
		case IDC_BLACK: strcpy(sz_theme, "Calc"); hBrush = hBrushBlack; break;
		case IDC_SQUARE: strcpy(sz_theme, "Button"); hBrush = hBrushSquare; break;
		case IDC_EXIT: SendMessage(hwnd, IDC_EXIT, 0, 0); 
		}
		SetTheme(hwnd, sz_theme);
		//SendMessage(hwnd, WM_PAINT, 0, 0);
		//SetTheme(hwnd, sz_theme);
	}
	break;
	case WM_DESTROY: PostQuitMessage(0); break;
	case IDC_EXIT:
	case WM_CLOSE: DestroyWindow(hwnd); break; 
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return NULL;
}

VOID SetTheme(HWND hwnd, CONST CHAR sz_theme[])
{
	CONST INT SIZE = 10;
	HWND hButton[SIZE] = {};
	//HBITMAP hBitmap[SIZE] = {};
	for (int i = 0; i < SIZE; i++)
	{
		hButton[i] = GetDlgItem(hwnd, i + IDC_BUTTON_0);
		//hBitmap[i] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(i + IDB_BITMAP_0));
		//SendMessage(hButton[i], BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap[i]);
		CHAR sz_filename[FILENAME_MAX] = {};
		sprintf(sz_filename, "Theme\\%s\\%i.bmp",sz_theme, i);
		HBITMAP hBitmap = (HBITMAP)LoadImage
		(
			GetModuleHandle(NULL),
			sz_filename,
			IMAGE_BITMAP,
			i > 0 ? g_i_BTN_SIZE : g_i_BTN_SIZE_DOUBLE, g_i_BTN_SIZE,
			LR_LOADFROMFILE
		);
		/*DWORD dwErrorMessageID = GetLastError();
		LPSTR lpMessageBuffer = NULL;
		DWORD dwSize = FormatMessage
		(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			dwErrorMessageID,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_RUSSIAN_RUSSIA),
			(LPSTR)&lpMessageBuffer,
			0,
			NULL
		);*/
		//MessageBox(hwnd, lpMessageBuffer, "Error", MB_OK | MB_ICONERROR);
		SendMessage(hButton[i], BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
	}
	//if (strcmp(sz_theme, "Calc")==0)SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG_PTR)hBrushBlack);
	//if (strcmp(sz_theme, "Button")==0)SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG_PTR)hBrushSquare);
	HDC hdc = GetDC(hwnd);
	if (strcmp(sz_theme, "Calc") == 0) SetDCBrushColor(hdc, g_cr_BLACK);
	if (strcmp(sz_theme, "Button")==0) SetDCBrushColor(hdc, g_cr_SQUARE);
	ReleaseDC(hwnd, hdc);
}