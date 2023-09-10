#include<Windows.h>
#include<stdio.h>
//#include"resource.h"

CONST CHAR g_sz_WINDOWS_CLASS[] = "My Windows Class";
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMng, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR IpCmdLine, INT nCmdShow)
{
	//1) Регистрация класса окна 
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.style = 0;

	wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);	// Иконка в панеле задач 
	wc.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);	// Икона отображаемая в строке заголовка 
	wc.hCursor = LoadCursor(hInstance, IDC_ARROW);		// указатель мыши, при наведении окна, курсор 
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);		// цвет и фон окна 

	wc.hInstance = hInstance;				// экземпляр запущенной программы 
	wc.lpfnWndProc = WndProc;				//указатель на процедуру окна 
	wc.lpszMenuName = NULL;					
	wc.lpszClassName = g_sz_WINDOWS_CLASS; // Имя класса окна, абсолютно любое окно, принадлежт к какомуто классу
											// т.е любое окна к какому то типа(Кнопка, Текстовое поле)
	if (!RegisterClassEx(&wc))
	{
		//MessageBox(NULL, "Что-то пошло не так", "Error", MB_OK | MB_ICONERROR);
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
	
	//2) Создание окна
	HWND hwnd = CreateWindowExA
	(
		NULL,
		g_sz_WINDOWS_CLASS,		// Имя класса окна 
		g_sz_WINDOWS_CLASS,		// Заголовок окна 
		WS_OVERLAPPEDWINDOW,	// Главное окно программы, еще назыв TopLevelWindows
		CW_USEDEFAULT, CW_USEDEFAULT, // координаты 
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,						// Parent - родителькое окно 
		NULL,						// имя меню, для главного окна 
									// для элемента окна - ID ресурса, этого элемента (IDC_EDIT, IDC_BUTTON)
		hInstance,			//Еслии нет прямого доспупа к hInstance, например потому что не подключилир его к параметру 
							// то его всегда можно получить при помощи функции GetModulHandle(NULL)
		NULL
	);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Окно не открывается, поэтому откроем хотя бы форточку", "Полезная информация", MB_OK | MB_ICONINFORMATION);
		return 0; 
	}

	ShowWindow(hwnd, nCmdShow); // Задаем режим отображения окна 
	UpdateWindow(hwnd);			// Выполняет прорисовку окна
	
	//3) Запуск цикла сообщений 
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
