#include <Windows.h>
#include "resource.h"

CONST CHAR g_sz_INVITE[] = "Введите имя пользователя";

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//HWND -  окно(Handler to Windows - обработчик окна)
// uMsg - сooбщение которое передается окну 
// wParam - парaметры сообщения 

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//MessageBox(NULL, "Hello World!", "Dronic", MB_YESNOCANCEL | MB_ICONINFORMATION);
	//MessageBox
	//(
	//	NULL,			// родительское окно, если его нет - параметр  NULL
	//	"Hello World!", 
	//	"Info", 
	//	MB_YESNOCANCEL | MB_ICONERROR | MB_HELP| MB_DEFBUTTON3| MB_APPLMODAL 
	//);
	//return 0;
	// модальное окно - это окноБ которое блокирует родительское окно;
	// каждый элемент интерфейса является окном 
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);
	return 0;

}
// процедура окна 
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG: 
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
		HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		//SetFocus(hEditLogin); // выделяем окно для печати, это часть окна которая принимает команды с клавиатуры    
		SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)g_sz_INVITE);
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_EDIT_LOGIN:
		{
			CONST INT SIZE = 256; // считываем текст в буфер, потом сравниваем с пустой строкой
			CHAR sz_buffer[SIZE] = {};
			SendMessage(GetDlgItem(hwnd, IDC_EDIT_LOGIN), WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			if (HIWORD(wParam)== EN_SETFOCUS) // WORD -2 байта памяти, DWORD - это double word ( 4 байта памяти)
			// которое делется на HIWORD(старшее) and LOWORD(младшее) 
				if (strcmp (sz_buffer, g_sz_INVITE) == 0)SendMessage(GetDlgItem(hwnd, IDC_EDIT_LOGIN), WM_SETTEXT, 0, (LPARAM)"");
			if (HIWORD(wParam) == EN_KILLFOCUS)
			{
				//SendMessage(GetDlgItem(hwnd, IDC_EDIT_LOGIN), WM_SETTEXT, 0, (LPARAM)g_sz_INVITE);
				if (strcmp(sz_buffer, "") == 0)
				{
					SendMessage(GetDlgItem(hwnd, IDC_EDIT_LOGIN), WM_SETTEXT, 0, (LPARAM)g_sz_INVITE);
				}
			}
		}
			break;
		case IDC_BUTTON_COPY: 
		{
			CONST INT SIZE = 256;
			CHAR  sz_buffer[SIZE] = {};
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		break; 
		case IDOK: MessageBox(hwnd, "Была нажата кнопка OK", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL: EndDialog(hwnd, 0);
		}
		break;
	case WM_CLOSE: EndDialog(hwnd, 0);
	}
	return FALSE;
}