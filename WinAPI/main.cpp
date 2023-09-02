#include <Windows.h>
#include"resource.h"

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//HWND -  ����(Handler to Windows - ���������� ����)
// uMsg - �oo������ ������� ���������� ���� 
// wParam - ���a����� ��������� 

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//MessageBox(NULL, "Hello World!", "Dronic", MB_YESNOCANCEL | MB_ICONINFORMATION);
	//MessageBox
	//(
	//	NULL,			// ������������ ����, ���� ��� ��� - ��������  NULL
	//	"Hello World!", 
	//	"Info", 
	//	MB_YESNOCANCEL | MB_ICONERROR | MB_HELP| MB_DEFBUTTON3| MB_APPLMODAL
	//);
	//return 0;
	// ��������� ���� - ��� ����� ������� ��������� ������������ ����;

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);
	return 0;
}
// ��������� ���� 
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG: break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK: MessageBox(hwnd, "���� ������ ������ OK", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL: EndDialog(hwnd, 0);
		}
		break;
	case WM_CLOSE: EndDialog(hwnd, 0);
	}
	return FALSE;
}