#include <Windows.h>
#include"resource.h"

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//HWND -  окно(Handler to Windows - обработчик окна)
// uMsg - сooбщение которое передаетс€ окну 
// wParam - парaметры сообщени€ 

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
	// модальное окно - это окноЅ которое блокирует родительское окно;

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);
	return 0;
}
// процедура окна 
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG: break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK: MessageBox(hwnd, "Ѕыла нажата кнопка OK", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL: EndDialog(hwnd, 0);
		}
		break;
	case WM_CLOSE: EndDialog(hwnd, 0);
	}
	return FALSE;
}