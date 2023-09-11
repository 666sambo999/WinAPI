#include<Windows.h>
#include<stdio.h>
#include "resource.h"

CONST CHAR g_sz_WINDOWS_CLASS[] = "My Windows Class";
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMng, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR IpCmdLine, INT nCmdShow)
{
	//1) ����������� ������ ���� 
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.style = 0;

	//wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_CONSOLE));	// ������ � ������ ����� 
	//wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_STAR));	// ����� ������������ � ������ ��������� 
	wc.hIconSm = (HICON)LoadImage(hInstance, "starbucks.ico", IMAGE_ICON, LR_DEFAULTSIZE,LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hIcon = (HICON)LoadImage(hInstance, "console_gamer.ico", IMAGE_ICON, LR_DEFAULTSIZE,LR_DEFAULTSIZE, LR_LOADFROMFILE);
	
	//wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));		// ��������� ����, ��� ��������� ����, ������ 
	wc.hCursor = (HCURSOR)LoadImage(hInstance, "Darth", IMAGE_CURSOR, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);		// ���� � ��� ���� 

	wc.hInstance = hInstance;				// ��������� ���������� ��������� 
	wc.lpfnWndProc = WndProc;				//��������� �� ��������� ���� 
	wc.lpszMenuName = NULL;					
	wc.lpszClassName = g_sz_WINDOWS_CLASS; // ��� ������ ����, ��������� ����� ����, ���������� � �������� ������
											// �.� ����� ���� � ������ �� ����(������, ��������� ����)
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "���-�� ����� �� ���", "Error", MB_OK | MB_ICONERROR);
		//MessageBox(NULL, "Something went wrong", "Error", MB_OK | MB_ICONERROR);
		return 0; 
	}
	
	//2) �������� ����
	HWND hwnd = CreateWindowExA
	(
		NULL,
		g_sz_WINDOWS_CLASS,		// ��� ������ ���� 
		g_sz_WINDOWS_CLASS,		// ��������� ���� 
		WS_OVERLAPPEDWINDOW,	// ������� ���� ���������, ��� ����� TopLevelWindows
		CW_USEDEFAULT, CW_USEDEFAULT, // ���������� 
		CW_USEDEFAULT, CW_USEDEFAULT, // ������ ���� 
		NULL,						// Parent - ����������� ���� 
		NULL,						// ��� ����, ��� �������� ���� 
									// ��� �������� ���� - ID �������, ����� �������� (IDC_EDIT, IDC_BUTTON)
		hInstance,			//����� ��� ������� ������� � hInstance, �������� ������ ��� �� ����������� ��� � ��������� 
							// �� ��� ������ ����� �������� ��� ������ ������� GetModulHandle(NULL)
		NULL
	);

	DWORD dwErrorMessageID = GetLastError();

	if (hwnd == NULL)
	{
		MessageBox(NULL, "���� �� �����������, ������� ������� ���� �� ��������", "�������� ����������", MB_OK | MB_ICONINFORMATION);
		
		LPSTR lpszMessageBuffer = NULL;
		DWORD dwSize =
			FormatMessage
			(
				FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				dwErrorMessageID,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_RUSSIAN_RUSSIA),
				(LPSTR)&lpszMessageBuffer,
				0,
				NULL
			);
		MessageBox(NULL, lpszMessageBuffer, "Error", MB_OK | MB_ICONERROR);
		LocalFree(lpszMessageBuffer);
		return 0; 
	}

	ShowWindow(hwnd, nCmdShow); // ������ ����� ����������� ���� 
	UpdateWindow(hwnd);			// ��������� ���������� ����
	
	//3) ������ ����� ��������� 
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0; 

}

// ��������� ���� 
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMng, WPARAM wParam, LPARAM lParam)
{
	switch (uMng)
	{
	case WM_CREATE:
	{
		CHAR sz_static_text[] = "���� static control ������ ��� ������ ������� CreateWindowsEx()  :)";
		CreateWindowEx
		(
			0,
			"Static", sz_static_text,
			WS_CHILD | WS_VISIBLE,
			100, 100,
			strlen(sz_static_text)*7.3,20,
			hwnd,
			(HMENU)IDC_STATIC,
			GetModuleHandle(0),
			NULL
		);
		CreateWindowEx // �������� ������ 
		(
			0,
			"Button", "Ok",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			600,400,
			40,20,
			hwnd, 
			(HMENU)IDC_BUTTON,
			GetModuleHandle(0),
			NULL
		);
		CreateWindowEx // �������� ���� ��� ����� 
		(
			0, "Edit", "������� ����� ���������:",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			350,250,
			300,25,
			hwnd,
			(HMENU)IDC_EDIT_CONTROL,
			GetModuleHandle(0),
			NULL
		);
	
	}
	
	break;
	case WM_COMMAND:
		switch LOWORD(wParam)
		{
		case IDC_BUTTON:
		{
			CONST INT SIZE = 256;
			CHAR sz_byffer[SIZE] = {};
			SendMessage(GetDlgItem(hwnd, IDC_EDIT_CONTROL), WM_GETTEXT, SIZE, (LPARAM)sz_byffer);
			SendMessage(GetDlgItem(hwnd, IDC_STATIC), WM_SETTEXT, 0, (LPARAM)sz_byffer);
		}
		break;
		}
		break;
	case WM_DESTROY:	PostQuitMessage(0); break;
	case WM_CLOSE:		DestroyWindow(hwnd);	break;
	default:			return DefWindowProc(hwnd, uMng, wParam, lParam);
	}
	return FALSE;
}
