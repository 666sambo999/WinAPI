#include<Windows.h>
#include"resource.h"
CONST CHAR g_sz_Windows_Class[] = "My Text Editor";

LRESULT CALLBACK WndProg(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1) регистрация класса окна 
	WNDCLASSEX ws; 
	ZeroMemory(&ws, sizeof(ws));
	ws.cbClsExtra = 0;
	ws.cbWndExtra = 0;
	ws.cbSize = sizeof(ws);
	ws.style = 0;

	ws.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	ws.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);
	ws.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	ws.hCursor = LoadCursor(hInstance, IDC_ARROW);

	ws.hInstance = hInstance;
	ws.lpszClassName = g_sz_Windows_Class; // ошибка на мультибайт 
	ws.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); 
	ws.lpfnWndProc = WndProg; 
	if (!RegisterClassEx(&ws))
	{
		MessageBox(NULL, "Class registeration failed", "Error", MB_OK | MB_ICONERROR);
		return 0; 
	}
	//2) создание окна
	HWND hwnd = CreateWindowEx
	(
		NULL, 
		g_sz_Windows_Class,g_sz_Windows_Class,
		WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, 
		NULL,
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Info", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	//3) запук цикла сообщений 
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}


LRESULT CALLBACK WndProg(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		RECT rect;			// коорданаты, создаем прямоугольник клиентской области, окна
		GetClientRect(hwnd, &rect); 
		// Клиентская область окна - это все окна, кроме строки меню, строка заголовка 
		// строки состояния меню: Те это рабочая область приложения 
		
		HWND hEdit = CreateWindowEx
		(
			NULL, "Edit", "Text Editor", 
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE,
			rect.left, rect.top,
			rect.right - rect.left, rect.bottom-rect.top, // размер и положения окна 
			hwnd, 
			(HMENU)IDC_EDIT,
			GetModuleHandle(NULL), // в процедуре окна берем hInstance
			NULL
		);
	}
		break; 
	case WM_COMMAND:
		break; 
	case WM_DESTROY: PostQuitMessage(0); break;
	case WM_CLOSE: DestroyWindow(hwnd); break;
	default:		return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	}

}