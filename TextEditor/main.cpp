#include<Windows.h>
#include"resource.h"
#include<Richedit.h>

CONST CHAR g_sz_Windows_Class[] = "My Text Editor";

LRESULT CALLBACK WndProg(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL LoadTextFileEdit(HWND hEdit, LPCSTR lpszFileName);
BOOL SaveTextFileEdit(HWND hEdit, LPCSTR lpszFileName);

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
		LoadLibrary("riched20.dll");
		
		RECT rect;			// коорданаты, создаем прямоугольник клиентской области, окна
		GetClientRect(hwnd, &rect); 
		// Клиентская область окна - это все окна, кроме строки меню, строка заголовка 
		// строки состояния меню: Те это рабочая область приложения 
		
		HWND hEdit = CreateWindowEx
		(
			NULL, RICHEDIT_CLASS, "Text Editor", 
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE,
			//rect.left, rect.top,
			0,0,
			//rect.right - rect.left, rect.bottom-rect.top, // размер и положения окна 
			rect.right, rect.bottom, // размер и положения окна 
			hwnd, 
			(HMENU)IDC_EDIT,
			GetModuleHandle(NULL), // в процедуре окна берем hInstance
			NULL
		);
	}
		break; 
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_FILE_OPEN:
		{
			CHAR szFileName[MAX_PATH]{};	
			OPENFILENAME ofn;
			ZeroMemory(&ofn, sizeof(ofn));

			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hwnd;		// Owner - владелец, родительское окно
			ofn.lpstrFilter = "Text files: (*.txt)\0*.txt\0All files (*.*)\0*.*\0";
			ofn.lpstrFile = szFileName;
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
			ofn.lpstrDefExt = "txt"; // Default Extension - расширение по умолчанию 

			if (GetOpenFileName(&ofn))
			{
				HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
				LoadTextFileEdit(hEdit, szFileName);
			}
		}
		break;
		case ID_FILE_SAVEAS:
		{
			CHAR szFileName[MAX_PATH] = {};
			OPENFILENAME ofn;
			ZeroMemory(&ofn, sizeof(ofn));

			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hwnd;
			ofn.lpstrFilter = "Text files (*.txt)\0*.txt\0All files (*.*)\0*.*\0";	//Double NULL-Terminated line
			ofn.lpstrFile = szFileName;
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
			ofn.lpstrDefExt = "txt";
			
			if (GetSaveFileName(&ofn))
			{
				HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
				SaveTextFileEdit(hEdit, szFileName);
			}
		}
		break;
		}
	}
	break; 
	case WM_DESTROY: PostQuitMessage(0); break;
	case WM_CLOSE: DestroyWindow(hwnd); break;
	default:		return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	}

}

BOOL LoadTextFileEdit(HWND hEdit, LPCSTR lpszFileName)
{
	BOOL bSuccess = FALSE;
	HANDLE hFile = CreateFile(lpszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwFileSize = GetFileSize(hFile, NULL); 
		if (dwFileSize != UINT_MAX)
		{
			LPSTR lpszFileText = (LPSTR)GlobalAlloc(GPTR, dwFileSize + 1);
			if (lpszFileText)
			{
				DWORD dwRead;
				if (ReadFile(hFile, lpszFileText, dwFileSize, &dwRead, NULL))
				{
					lpszFileText[dwFileSize] = 0; //Null Terminator
					if (SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)lpszFileText))bSuccess = TRUE;
				}
				GlobalFree(lpszFileText);
			}
			CloseHandle(hFile);
		}
	}
	return bSuccess;
}
BOOL SaveTextFileEdit(HWND hEdit, LPCSTR lpszFileName)
{
	BOOL bSuccess = FALSE;
	HANDLE hFile = CreateFile(lpszFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwTextLength = GetWindowTextLength(hEdit);
		if (dwTextLength > 0) 
		{
			LPSTR lpszText = (LPSTR)GlobalAlloc(GPTR, dwTextLength + 1);
			if (lpszText != NULL) // читаем файл
			{
				if (GetWindowText(hEdit, lpszText, dwTextLength + 1))
				{
					DWORD dwWritten;
					if(WriteFile(hFile, lpszText, dwTextLength, &dwWritten, NULL))bSuccess = TRUE;
				}
				GlobalFree(lpszText);
			}
		}
		CloseHandle(hFile);
	}
	return bSuccess;
}