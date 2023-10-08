#define  _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include"resource.h"
#include<Richedit.h>
#include<CommCtrl.h>
#include<cstdio>

CONST CHAR g_sz_Windows_Class[] = "My Text Editor";

LRESULT CALLBACK WndProg(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL LoadTextFileEdit(HWND hEdit, LPSTR lpszFileName);
BOOL SaveTextFileEdit(HWND hEdit, LPSTR lpszFileName);
BOOL FileWasChanger(HWND hEdit, LPSTR lpszFileText, LPSTR lpszText);

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
	static CHAR szFileName[MAX_PATH]{};	
	static LPSTR lpszFileText = NULL;
	static LPSTR lpszText = NULL;
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
			NULL, RICHEDIT_CLASS, "", 
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
		HWND hStatus = CreateWindowEx
		(
			NULL, STATUSCLASSNAME,
			NULL, WS_CHILD | WS_VISIBLE,
			0, 0, 
			0, 0, 
			hwnd, 
			(HMENU)IDC_STATUS, 
			GetModuleHandle(NULL),
			NULL
			);
	}
		break; 
	case WM_SIZE:
	{
		HWND hStatus = GetDlgItem(hwnd, IDC_STATUS);
		RECT reStatus;
		SendMessage(hStatus, WM_SIZE, 0, 0);
		GetWindowRect(hStatus, &reStatus);
		int iStatusHeight = reStatus.bottom - reStatus.top;
		RECT reClient;
		HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
		GetClientRect(hwnd, &reClient);
		int iEditHeight = reClient.bottom - iStatusHeight;
		SetWindowPos(hEdit, NULL, 0, 0, reClient.right - reClient.left, iEditHeight, SWP_NOZORDER);
	}
		break; 
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_FILE_NEW:
		{
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
			DWORD dwTextLength = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
			LPSTR lpszText = (LPSTR)GlobalAlloc(GPTR, dwTextLength + 1);
			SendMessage(hEdit, WM_GETTEXT, dwTextLength + 1, (LPARAM)lpszText);
			if (lpszFileText && strcmp(lpszFileText, lpszText) || lpszFileText == 0 && lpszText[0])
			{
				switch (MessageBox(hwnd, "Сохранить в файле изменения?", "Вопрос :-)", MB_YESNOCANCEL | MB_ICONQUESTION))
				{
				case IDYES: SendMessage(hwnd, WM_COMMAND, ID_FILE_SAVE, 0);
				case IDNO: 
					lpszFileText = NULL;
					szFileName[0] = 0;
					SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)"");
				case IDCANCEL: break; 
				}
			}
			else
			{
				lpszFileText = NULL;
				szFileName[0] = 0;
				SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)"");
			}
		}
		break; 
		case ID_FILE_OPEN:
		{
			BOOL cancel = FALSE;
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
			DWORD dwTextLength = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
			LPSTR lpszText = (LPSTR)GlobalAlloc(GPTR, dwTextLength + 1);
			SendMessage(hEdit, WM_GETTEXT, dwTextLength + 1, (LPARAM)lpszText);
			if (lpszFileText && strcmp(lpszFileText, lpszText) || lpszFileText == 0 && lpszText[0])
			{
				switch (MessageBox(hwnd, "Сохранить в файле изменения?", "Вопрос :-)", MB_YESNOCANCEL | MB_ICONQUESTION))
				{
				case IDYES: SendMessage(hwnd, WM_COMMAND, ID_FILE_SAVE, 0); break;
				case IDNO:
				case IDCANCEL: cancel = TRUE;
				}
				if (cancel)break;
			}
			//CHAR szFileName[MAX_PATH]{};	
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
				HWND hStatus = GetDlgItem(hwnd, IDC_STATUS); // статус бара
				LoadTextFileEdit(hEdit, szFileName);
				DWORD dwTextLength = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
				lpszFileText = (LPSTR)GlobalAlloc(GPTR, dwTextLength + 1);
				SendMessage(hEdit, WM_GETTEXT, dwTextLength + 1, (LPARAM)lpszFileText);
				
				CHAR szTitle[FILENAME_MAX]{};
				sprintf(szTitle, "%s - %s", g_sz_Windows_Class, strrchr(szFileName, '\\') + 1);
				SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)szTitle);
				SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)szTitle);
			}
		}
		break;
		case ID_FILE_SAVE:
		{
			if (szFileName[0])
			{
				SaveTextFileEdit(GetDlgItem(hwnd, IDC_EDIT), szFileName);
				HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
				DWORD dwTextLength = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
				lpszFileText = (LPSTR)GlobalAlloc(GPTR, dwTextLength + 1);
				SendMessage(hEdit, WM_GETTEXT, dwTextLength + 1, (LPARAM)lpszFileText);
				break;
			}
		}
		case ID_FILE_SAVEAS:
		{
			//CHAR szFileName[MAX_PATH] = {};
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
				HWND hStatus = GetDlgItem(hwnd, IDC_STATUS);
				SaveTextFileEdit(hEdit, szFileName);

				CHAR szTitle[FILENAME_MAX]{};
				sprintf(szTitle, "%s - %s", g_sz_Windows_Class, strrchr(szFileName, '\\')+1);
				SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)szTitle);
				SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)szTitle);
			}
		}
		break;
		}
	}
	break; 
	case WM_DESTROY: PostQuitMessage(0); break;
	case WM_CLOSE: 
	{
		BOOL close = FALSE;
		HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
		DWORD dwTextLength = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
		LPSTR lpszText = (LPSTR)GlobalAlloc(GPTR, dwTextLength + 1);
		
		if (lpszText != NULL)
		{
			SendMessage(hEdit, WM_GETTEXT, dwTextLength + 1, (LPARAM)lpszText);
			//if (FileWasChanger(GetDlgItem(hwnd, IDC_EDIT), lpszText, lpszFileText))
			if (lpszFileText && strcmp(lpszFileText, lpszText)|| lpszFileText == NULL && lpszText[0])
			{
				switch (MessageBox(hwnd, "Сохранить изменения в файле?", "Question", MB_YESNOCANCEL | MB_ICONQUESTION))
				{
				case IDYES: SendMessage(hwnd, WM_COMMAND, ID_FILE_SAVE, 0);
				case IDNO: close = TRUE;
				case IDCANCEL: break;
				}
			}
			else
			{
				close = TRUE;
			}
		}
		if (close)DestroyWindow(hwnd);
	}
		break;
	default:		return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	}

}

BOOL LoadTextFileEdit(HWND hEdit, LPSTR lpszFileName)
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

BOOL SaveTextFileEdit(HWND hEdit, LPSTR lpszFileName)
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
				//LPSTR lpszFileText = (LPSTR)GlobalAlloc(GPTR, dwTextLength + 1);
				if (GetWindowText(hEdit, lpszText, dwTextLength + 1))
				{
					DWORD dwWritten;
					if(WriteFile(hFile, lpszText, dwTextLength, &dwWritten, NULL))bSuccess = TRUE;
				}
				GlobalFree(lpszText);
			}
		}
		CloseHandle(hFile);
		//strcpy(lpszFileText, lpszText);	// копируем строку 
	}
	return bSuccess;
}

BOOL FileWasChanger(HWND hEdit, LPSTR lpszFileText, LPSTR lpszText)
{
	BOOL fileChanger = FALSE; 
	DWORD dwTextLength = GetWindowTextLength(hEdit);
	if (dwTextLength == 0 && lpszText == NULL && lpszFileText == NULL)return FALSE;
	if (dwTextLength > 0)
	{
		lpszText = (LPSTR)GlobalAlloc(GPTR, dwTextLength + 1);
		if (lpszFileText == NULL)lpszFileText = (LPSTR)GlobalAlloc(GPTR, dwTextLength + 1);
		SendMessage(hEdit, WM_GETTEXT, dwTextLength, (LPARAM)lpszText);
		//if (lpszText != lpszFileText)
		{
			//if ()
			if (lpszFileText && strcmp(lpszFileText, lpszText))fileChanger = TRUE;
		}
	}
	return fileChanger;
}