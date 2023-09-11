#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<cstdio>
#include"resource.h"

CONST CHAR* g_sz_VALUES[] = { "This", "is", "my", "first", "List", "Box"};

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProcAddElement(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hList = GetDlgItem(hwnd, IDC_LIST1);
		for (int i = 0; i < ARRAYSIZE(g_sz_VALUES); i++)
		{
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)g_sz_VALUES[i]);
		}
		SetFocus(hwnd);
	}
	break;
		case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_ADD: DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD), hwnd, DlgProcAddElement, 0);
			break;
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			HWND hList = GetDlgItem(hwnd, IDC_LIST1);
			int i = SendMessage(hList, LB_GETCURSEL, 0, 0);
			SendMessage(hList, LB_GETTEXT, i, (LPARAM)sz_buffer);
			if (i < 0)
			{
				MessageBox(hwnd, "�� ������ �� �������", "Info", MB_OK | MB_ICONINFORMATION);
			}
			else
			{
				CHAR sz_message[SIZE] = {};
				i++;
				sprintf(sz_message, "��� ������ � %i, �� ��������� \"%s\"", i, sz_buffer);
				MessageBox(hwnd, sz_message, "Info", MB_OK | MB_ICONINFORMATION);
			}
		}
		break;
		case IDCANCEL: EndDialog(hwnd, 0);
		}
		break;
	break; 
	case WM_CLOSE: EndDialog(hwnd, 0); 
	}
	return FALSE;
}

BOOL CALLBACK DlgProcAddElement(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		
		case WM_COMMAND:
		switch (LOWORD(wParam))
		{

		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_byffer[SIZE] = {};
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_NEW);
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_byffer);
			HWND hParent = GetParent(hwnd);
			HWND hList = GetDlgItem(hParent, IDC_LIST1);
			if (SendMessage(hList, LB_FINDSTRING, 0, (LPARAM)sz_byffer) == LB_ERR)
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)sz_byffer);
		}
		case IDCANCEL:EndDialog(hwnd, 0);
		}
		break;
	case WM_CLOSE: EndDialog(hwnd, 0);
	}
	return FALSE;
}