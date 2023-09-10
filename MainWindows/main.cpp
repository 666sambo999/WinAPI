#include<Windows.h>
#include<stdio.h>
//#include"resource.h"

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

	wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);	// ������ � ������ ����� 
	wc.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);	// ����� ������������ � ������ ��������� 
	wc.hCursor = LoadCursor(hInstance, IDC_ARROW);		// ��������� ����, ��� ��������� ����, ������ 
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);		// ���� � ��� ���� 

	wc.hInstance = hInstance;				// ��������� ���������� ��������� 
	wc.lpfnWndProc = WndProc;				//��������� �� ��������� ���� 
	wc.lpszMenuName = NULL;					
	wc.lpszClassName = g_sz_WINDOWS_CLASS; // ��� ������ ����, ��������� ����� ����, ���������� � �������� ������
											// �.� ����� ���� � ������ �� ����(������, ��������� ����)
	if (!RegisterClassEx(&wc))
	{
		//MessageBox(NULL, "���-�� ����� �� ���", "Error", MB_OK | MB_ICONERROR);
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
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,						// Parent - ����������� ���� 
		NULL,						// ��� ����, ��� �������� ���� 
									// ��� �������� ���� - ID �������, ����� �������� (IDC_EDIT, IDC_BUTTON)
		hInstance,			//����� ��� ������� ������� � hInstance, �������� ������ ��� �� ����������� ��� � ��������� 
							// �� ��� ������ ����� �������� ��� ������ ������� GetModulHandle(NULL)
		NULL
	);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "���� �� �����������, ������� ������� ���� �� ��������", "�������� ����������", MB_OK | MB_ICONINFORMATION);
		return 0; 
	}

	ShowWindow(hwnd, nCmdShow); // ������ ����� ����������� ���� 
	UpdateWindow(hwnd);			// ��������� ���������� ����
	
	//3) ������ ����� ��������� 
	return 0; 

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMng, WPARAM wParam, LPARAM lParam)
{
	switch (uMng)
	{
	case WM_CREATE:
		break;
	case WM_COMMAND:
		break;
	case WM_DESTROY: PostQuitMessage(0); break;
	case WM_CLOSE: DestroyWindow(hwnd);	break;
	default:  DefWindowProc(hwnd, uMng, wParam, lParam);
	}
	return FALSE;
}
