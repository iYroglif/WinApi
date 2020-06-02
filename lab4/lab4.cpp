#include <Windows.h>
#include <tchar.h>
#include <string>
#include <atlstr.h>

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#pragma intrinsic(__rdtsc)


using namespace std;

static int widht, hight, r;
static HWND hWnd;
static HDC hdc;
static PAINTSTRUCT ps;
static HANDLE hThread2;
static BOOL bFin = true;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("MainFrame");

DWORD WINAPI Thread2(LPVOID);

int WINAPI _tWinMain(HINSTANCE This,		 // Дескриптор текущего приложения 
	HINSTANCE Prev, 	// В современных системах всегда 0 
	LPTSTR cmd, 		// Командная строка 
	int mode) 		// Режим отображения окна
{
	HWND hWnd;		// Дескриптор главного окна программы 
	MSG msg; 		// Структура для хранения сообщения 
	WNDCLASS wc; 	// Класс окна
	// Определение класса окна 
	wc.hInstance = This;
	wc.lpszClassName = WinName; 				// Имя класса окна 
	wc.lpfnWndProc = WndProc; 					// Функция окна 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// Стиль окна 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// Стандартная иконка 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// Стандартный курсор 
	wc.lpszMenuName = NULL; 					// Нет меню 
	wc.cbClsExtra = 0; 						// Нет дополнительных данных класса 
	wc.cbWndExtra = 0; 						// Нет дополнительных данных окна 
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); 	// Заполнение окна белым цветом 


	// Регистрация класса окна
	if (!RegisterClass(&wc)) return 0;

	// Создание окна 
	hWnd = CreateWindow(WinName,			// Имя класса окна 
		_T("Каркас Windows-приложения"), 		// Заголовок окна 
		WS_OVERLAPPEDWINDOW, 		// Стиль окна 
		CW_USEDEFAULT,				// x 
		CW_USEDEFAULT, 				// y	 Размеры окна 
		CW_USEDEFAULT, 				// width 
		CW_USEDEFAULT, 				// Height 
		HWND_DESKTOP, 				// Дескриптор родительского окна 
		NULL, 						// Нет меню 
		This, 						// Дескриптор приложения 
		NULL); 					// Дополнительной информации нет 

	ShowWindow(hWnd, mode); 				// Показать окно

	// Цикл обработки сообщений 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 		// Функция трансляции кодов нажатой клавиши 
		DispatchMessage(&msg); 		// Посылает сообщение функции WndProc() 
	}
	return 0;
}

// Оконная функция вызывается операционной системой
// и получает сообщения из очереди для данного приложения

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	DWORD dwIDThread;
	switch (message)		 // Обработчик сообщений
	{

	case WM_CREATE:
	{
		bFin = true;
		hdc = GetDC(hWnd);
		hThread2 = CreateThread(NULL, 0, Thread2, (void*)hdc, 0, &dwIDThread);
		RECT rc;
		GetClientRect(hWnd, &rc);
		hight = rc.bottom;
		widht = rc.right;
	}
	break;

	case WM_SIZE:
	{
		RECT rc;
		GetClientRect(hWnd, &rc);
		hight = rc.bottom;
		widht = rc.right;
	}
	break;

	case WM_PAINT:
	{
		
		hdc = BeginPaint(hWnd, &ps);

		HPEN hPen1 = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
		SelectObject(hdc, hPen1);
		HBRUSH hBrush1 = (HBRUSH)GetStockObject(BLACK_BRUSH);
		HBRUSH hBrush2 = (HBRUSH)GetStockObject(GRAY_BRUSH);
		HBRUSH hBrush3 = (HBRUSH)GetStockObject(WHITE_BRUSH);
		r = rand() % 3;
		
		if (r == 0) {
			SelectObject(hdc, hBrush1);
		}
		else if (r == 1) {
			SelectObject(hdc, hBrush2);
		}
		else {
			SelectObject(hdc, hBrush3);
		}
		Ellipse(hdc, (widht / 2) - (hight / 4), 0, (widht / 2) + (hight / 4), hight / 2);

		/*
		DWORD start;
		start = timeGetTime();
		wstring b = to_wstring(start);
		TextOutW(hdc, (widht / 2) - 30, hight / 4, b.c_str(), 9);
		*/

		
		unsigned __int64 i;
		i = __rdtsc();
		char q[100];
		snprintf(q, 100, "%I64d ticks\n", i);
		wstring b(&q[0], &q[99]);
		TextOutW(hdc, (widht / 2) - 70, hight / 4, b.c_str(), 21);
		

		/*
		wstring b = to_wstring(GetCurrentProcessorNumber());
		TextOutW(hdc, (widht / 2) - 60, hight / 4, b.c_str(), 15);
		*/

		EndPaint(hWnd, &ps);
	}
	break;

	case WM_DESTROY:
		bFin = false;
		PostQuitMessage(0);
		break; 			// Завершение программы 
	default: 			// Обработка сообщения по умолчанию 
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

DWORD WINAPI Thread2(LPVOID hdcc) {
	HDC hdc = (HDC)hdcc;
	SetTextColor(hdc, RGB(255, 0, 0));
	SetTextAlign(hdc, TA_BOTTOM);
	SYSTEMTIME lpSystemTime;
	LOGFONT lgf;
	HFONT fn;
	memset(&lgf, 0, sizeof(LOGFONT));
	lgf.lfHeight = 72;
	StrCpy(lgf.lfFaceName, _T("OCR A Extended"));
	fn = CreateFontIndirect(&lgf);
	SelectObject(hdc, fn);
	while (bFin) {
		GetLocalTime(&lpSystemTime);
		wstring a = to_wstring(lpSystemTime.wHour) + L":" + to_wstring(lpSystemTime.wMinute) + L":" + to_wstring(lpSystemTime.wSecond);
		TextOutW(hdc, widht / 2 - 160, hight - (hight / 4), a.c_str(), 8);
		Sleep(10);
	}
	return 0;
}