﻿#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include"resource.h"
#include"resource1.h"
#include<cstdio>

CONST CHAR g_sz_WINDOWS_CLASS[] = "My Calculator";

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

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

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
						WS_CHILDWINDOW | WS_VISIBLE | BS_PUSHBUTTON,
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
		CreateWindowEx
		(
			NULL, "BUTTON", "0",
			WS_CHILDWINDOW | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_BTN_START_x, g_i_BTN_START_y+ g_i_BTN_SIZE_WITH_INTERVAL*3,
			g_i_BTN_SIZE_DOUBLE,g_i_BTN_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_0,
			GetModuleHandle(NULL),
			NULL
		);
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
			if (strcmp(sz_buffer, "0") == 0)break;  // strcmp = строка, на конце стоит 0;
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
		case VK_OEM_PLUS:	SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_PLUS, 0); break;
		case VK_OEM_MINUS:	SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_MINUS, 0); break;
		case VK_MULTIPLY:	SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_ASTER, 0); break;
		case VK_OEM_2: 
		case VK_DIVIDE:		SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_SLASH, 0); break;
		case VK_RETURN:		SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_EQUAL, 0); break; 
		case VK_ESCAPE:		SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_CLEAR, 0); break; 
		case VK_BACK:		SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_BSP, 0); break;
		}
	}
		break;
	case WM_DESTROY: PostQuitMessage(0); break;
	case WM_CLOSE: DestroyWindow(hwnd); break; 
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return NULL;
}