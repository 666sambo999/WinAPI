#include <Windows.h>
#include "resource.h"

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
		SetFocus(hEditLogin); // выделяем окно для печати 
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
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