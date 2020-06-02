#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <Windows.h>
#include <tchar.h>
#include <string>
#include <atlstr.h>

#define windowWidth 324
#define windowHeight 380
#define buttonWidth 78
#define buttonHeight 50

using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("MainFrame");

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
		_T("Калькулятор"), 		// Заголовок окна 
		WS_OVERLAPPEDWINDOW, 		// Стиль окна 
		CW_USEDEFAULT,				// x 
		CW_USEDEFAULT, 				// y	 Размеры окна 
		windowWidth + 16, 				// width 
		windowHeight + 40, 				// Height 
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
	static HWND sign, zero, point, equals, one, two, three, plus, four, five, six, minus, seven, eight, nine, multiplication, division, backspace, clearEntry, clear, hEdit, hStatic;
	static TCHAR buf[256];
	static TCHAR ttt[256];
	//memset(buf, 0, 256);
	static bool refresh = false;
	static int operation[2] = { 0 };
	static double leftOperand = NULL;

	switch (message)		 // Обработчик сообщений
	{
	case WM_CREATE:
	{
		sign = CreateWindow(
			_T("button"),
			_T("+/-"),
			WS_CHILD | WS_VISIBLE,
			3,
			windowHeight - buttonHeight - 3,
			buttonWidth,
			buttonHeight,
			hWnd,
			(HMENU)110,
			NULL,
			NULL
		);

		zero = CreateWindow(
			_T("button"),
			_T("0"),
			WS_CHILD | WS_VISIBLE,
			3 + buttonWidth + 2,
			windowHeight - buttonHeight - 3,
			buttonWidth,
			buttonHeight,
			hWnd,
			(HMENU)100,
			NULL,
			NULL
		);

		point = CreateWindow(
			_T("button"),
			_T(","),
			WS_CHILD | WS_VISIBLE,
			3 + 2 * buttonWidth + 2 * 2,
			windowHeight - buttonHeight - 3,
			buttonWidth,
			buttonHeight,
			hWnd,
			(HMENU)111,
			NULL,
			NULL
		);

		equals = CreateWindow(
			_T("button"),
			_T("="),
			WS_CHILD | WS_VISIBLE,
			3 + 3 * buttonWidth + 3 * 2,
			windowHeight - buttonHeight - 3,
			buttonWidth,
			buttonHeight,
			hWnd,
			(HMENU)112,
			NULL,
			NULL
		);

		one = CreateWindow(
			_T("button"),
			_T("1"),
			WS_CHILD | WS_VISIBLE,
			3,
			windowHeight - 2 - 2 * buttonHeight - 3,
			buttonWidth,
			buttonHeight,
			hWnd,
			(HMENU)101,
			NULL,
			NULL
		);

		two = CreateWindow(
			_T("button"),
			_T("2"),
			WS_CHILD | WS_VISIBLE,
			3 + buttonWidth + 2,
			windowHeight - 2 - 2 * buttonHeight - 3,
			buttonWidth,
			buttonHeight,
			hWnd,
			(HMENU)102,
			NULL,
			NULL
		);

		three = CreateWindow(
			_T("button"),
			_T("3"),
			WS_CHILD | WS_VISIBLE,
			3 + 2 * buttonWidth + 2 * 2,
			windowHeight - 2 - 2 * buttonHeight - 3,
			buttonWidth,
			buttonHeight,
			hWnd,
			(HMENU)103,
			NULL,
			NULL
		);

		plus = CreateWindow(
			_T("button"),
			_T("+"),
			WS_CHILD | WS_VISIBLE,
			3 + 3 * buttonWidth + 3 * 2,
			windowHeight - 2 - 2 * buttonHeight - 3,
			buttonWidth,
			buttonHeight,
			hWnd,
			(HMENU)113,
			NULL,
			NULL
		);

		four = CreateWindow(
			_T("button"),
			_T("4"),
			WS_CHILD | WS_VISIBLE,
			3,
			windowHeight - 2 * 2 - 3 * buttonHeight - 3,
			buttonWidth,
			buttonHeight,
			hWnd,
			(HMENU)104,
			NULL,
			NULL
		);

		five = CreateWindow(
			_T("button"),
			_T("5"),
			WS_CHILD | WS_VISIBLE,
			3 + buttonWidth + 2,
			windowHeight - 2 * 2 - 3 * buttonHeight - 3,
			buttonWidth,
			buttonHeight,
			hWnd,
			(HMENU)105,
			NULL,
			NULL
		);

		six = CreateWindow(
			_T("button"),
			_T("6"),
			WS_CHILD | WS_VISIBLE,
			3 + 2 * buttonWidth + 2 * 2,
			windowHeight - 2 * 2 - 3 * buttonHeight - 3,
			buttonWidth,
			buttonHeight,
			hWnd,
			(HMENU)106,
			NULL,
			NULL
		);

		minus = CreateWindow(
			_T("button"),
			_T("-"),
			WS_CHILD | WS_VISIBLE,
			3 + 3 * buttonWidth + 3 * 2,
			windowHeight - 2 * 2 - 3 * buttonHeight - 3,
			buttonWidth,
			buttonHeight,
			hWnd,
			(HMENU)114,
			NULL,
			NULL
		);

		seven = CreateWindow(
			_T("button"),
			_T("7"),
			WS_CHILD | WS_VISIBLE,
			3,
			windowHeight - 3 * 2 - 4 * buttonHeight - 3,
			buttonWidth,
			buttonHeight,
			hWnd,
			(HMENU)107,
			NULL,
			NULL
		);

		eight = CreateWindow(
			_T("button"),
			_T("8"),
			WS_CHILD | WS_VISIBLE,
			3 + buttonWidth + 2,
			windowHeight - 3 * 2 - 4 * buttonHeight - 3,
			buttonWidth,
			buttonHeight,
			hWnd,
			(HMENU)108,
			NULL,
			NULL
		);

		nine = CreateWindow(
			_T("button"),
			_T("9"),
			WS_CHILD | WS_VISIBLE,
			3 + 2 * buttonWidth + 2 * 2,
			windowHeight - 3 * 2 - 4 * buttonHeight - 3,
			buttonWidth,
			buttonHeight,
			hWnd,
			(HMENU)109,
			NULL,
			NULL
		);

		multiplication = CreateWindow(
			_T("button"),
			_T("x"),
			WS_CHILD | WS_VISIBLE,
			3 + 3 * buttonWidth + 3 * 2,
			windowHeight - 3 * 2 - 4 * buttonHeight - 3,
			buttonWidth,
			buttonHeight,
			hWnd,
			(HMENU)115,
			NULL,
			NULL
		);

		backspace = CreateWindow(
			_T("button"),
			_T("⟵"),
			WS_CHILD | WS_VISIBLE,
			3,
			windowHeight - 4 * 2 - 5 * buttonHeight - 3,
			buttonWidth,
			buttonHeight,
			hWnd,
			(HMENU)116,
			NULL,
			NULL
		);

		clearEntry = CreateWindow(
			_T("button"),
			_T("CE"),
			WS_CHILD | WS_VISIBLE,
			3 + 1 * buttonWidth + 1 * 2,
			windowHeight - 4 * 2 - 5 * buttonHeight - 3,
			buttonWidth,
			buttonHeight,
			hWnd,
			(HMENU)117,
			NULL,
			NULL
		);

		clear = CreateWindow(
			_T("button"),
			_T("C"),
			WS_CHILD | WS_VISIBLE,
			3 + 2 * buttonWidth + 2 * 2,
			windowHeight - 4 * 2 - 5 * buttonHeight - 3,
			buttonWidth,
			buttonHeight,
			hWnd,
			(HMENU)118,
			NULL,
			NULL
		);

		division = CreateWindow(
			_T("button"),
			_T("÷"),
			WS_CHILD | WS_VISIBLE,
			3 + 3 * buttonWidth + 3 * 2,
			windowHeight - 4 * 2 - 5 * buttonHeight - 3,
			buttonWidth,
			buttonHeight,
			hWnd,
			(HMENU)119,
			NULL,
			NULL
		);

		hEdit = CreateWindow(
			_T("edit"),
			_T("0"),
			WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_NUMBER | ES_NOHIDESEL,
			0,
			windowHeight - 5 * 2 - 6 * buttonHeight - 3 - 50,
			windowWidth,
			100,
			hWnd,
			NULL,
			NULL,
			NULL
		);
		SendMessage(hEdit, EM_SETLIMITTEXT, 10, 0);

		hStatic = CreateWindow(
			_T("static"),
			_T("0"),
			WS_CHILD | WS_VISIBLE | SS_RIGHT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			windowWidth - 10,
			15,
			hWnd,
			NULL,
			NULL,
			NULL
		);

		HMENU hMenu1 = CreateMenu();
		HMENU hMenu2 = CreateMenu();
		HMENU hMenubar1 = CreateMenu();
		AppendMenu(hMenu1, MF_STRING, 201, L"Copy");
		AppendMenu(hMenu1, MF_STRING, 202, L"Paste");
		AppendMenuW(hMenubar1, MF_POPUP, (UINT_PTR)hMenu1, L"Edit");
		AppendMenu(hMenu2, MF_STRING, 211, L"About Calculator");
		AppendMenuW(hMenubar1, MF_POPUP, (UINT_PTR)hMenu2, L"Help");
		SetMenu(hWnd, hMenubar1);

		LOGFONT lf;
		memset(&lf, 0, sizeof(LOGFONT));
		lstrcpy(lf.lfFaceName, _T("Calibri")); // Имя шрифта.
		lf.lfHeight = 80; // По высоте.
		HFONT hFont = CreateFontIndirect(&lf);
		SendMessage(hEdit, WM_SETFONT, (WPARAM)hFont, 0L);
	}
	break;
	case WM_GETMINMAXINFO:
	{
		MINMAXINFO* MMI = (MINMAXINFO*)lParam;
		MMI->ptMinTrackSize.x = windowWidth + 16;
		MMI->ptMaxTrackSize.x = windowWidth + 16;
		MMI->ptMinTrackSize.y = windowHeight + 60;
		MMI->ptMaxTrackSize.y = windowHeight + 60;
	}
	break;
	case WM_COMMAND:
	{
		//if (refresh2) SetWindowText(hStatic, ttt);
		switch (LOWORD(wParam))
		{
		case 100:
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (*buf == '0' || refresh) { *buf = 0; refresh = false; }
			if (lstrlen(buf) <= 7) {
				StrCat(buf, TEXT("0"));
				SetWindowText(hEdit, buf);
			}
		}
		break;

		case 101:
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (*buf == '0' || refresh) { *buf = 0; refresh = false; }
			if (lstrlen(buf) <= 7) {
				StrCat(buf, TEXT("1"));
				SetWindowText(hEdit, buf);
			}
		}
		break;

		case 102:
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (*buf == '0' || refresh) { *buf = 0; refresh = false; }
			if (lstrlen(buf) <= 7) {
				StrCat(buf, TEXT("2"));
				SetWindowText(hEdit, buf);
			}
		}
		break;

		case 103:
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (*buf == '0' || refresh) { *buf = 0; refresh = false; }
			if (lstrlen(buf) <= 7) {
				StrCat(buf, TEXT("3"));
				SetWindowText(hEdit, buf);
			}
		}
		break;

		case 104:
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (*buf == '0' || refresh) { *buf = 0; refresh = false; }
			if (lstrlen(buf) <= 7) {
				StrCat(buf, TEXT("4"));
				SetWindowText(hEdit, buf);
			}
		}
		break;

		case 105:
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (*buf == '0' || refresh) { *buf = 0; refresh = false; }
			if (lstrlen(buf) <= 7) {
				StrCat(buf, TEXT("5"));
				SetWindowText(hEdit, buf);
			}
		}
		break;

		case 106:
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (*buf == '0' || refresh) { *buf = 0; refresh = false; }
			if (lstrlen(buf) <= 7) {
				StrCat(buf, TEXT("6"));
				SetWindowText(hEdit, buf);
			}
		}
		break;

		case 107:
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (*buf == '0' || refresh) { *buf = 0; refresh = false; }
			if (lstrlen(buf) <= 7) {
				StrCat(buf, TEXT("7"));
				SetWindowText(hEdit, buf);
			}
		}
		break;

		case 108:
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (*buf == '0' || refresh) { *buf = 0; refresh = false; }
			if (lstrlen(buf) <= 7) {
				StrCat(buf, TEXT("8"));
				SetWindowText(hEdit, buf);
			}
		}
		break;

		case 109:
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (*buf == '0' || refresh) { *buf = 0; refresh = false; }
			if (lstrlen(buf) <= 7) {
				StrCat(buf, TEXT("9"));
				SetWindowText(hEdit, buf);
			}
		}
		break;

		case 110:
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (*buf != '0' && *buf != 0) {
				if (*buf == '-') StrCpy(buf, &buf[1]);
				else {
					TCHAR tmp[256] = { '-' };
					StrCat(tmp, buf);
					StrCpy(buf, tmp);
				}
				SetWindowText(hEdit, buf);
			}
		}
		break;

		case 111:
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (StrChr(buf, ',') == NULL) {
				StrCat(buf, TEXT(","));
				SetWindowText(hEdit, buf);
			}
		}
		break;

		case 112:
		{
			operation[0] = operation[1];
			operation[1] = 1;
			refresh = true;
			if (operation[0] == 0) leftOperand = _wtof(buf);
			StrCat(ttt, buf);
			StrCat(ttt, TEXT(" = "));
			SetWindowText(hStatic, ttt);
			memset(&ttt, 0, lstrlen(buf));
		}
		break;

		case 113:
		{
			operation[0] = operation[1];
			operation[1] = 2;
			refresh = true;
			if (operation[0] == 0) leftOperand = _wtof(buf);
			StrCat(ttt, buf);
			StrCat(ttt, TEXT(" + "));
			SetWindowText(hStatic, ttt);
		}
		break;

		case 114:
		{
			operation[0] = operation[1];
			operation[1] = 3;
			refresh = true;
			if (operation[0] == 0) leftOperand = _wtof(buf);
			StrCat(ttt, buf);
			StrCat(ttt, TEXT(" - "));
			SetWindowText(hStatic, ttt);
		}
		break;

		case 115:
		{
			operation[0] = operation[1];
			operation[1] = 4;
			refresh = true;
			if (operation[0] == 0) leftOperand = _wtof(buf);
			StrCat(ttt, buf);
			StrCat(ttt, TEXT(" * "));
			SetWindowText(hStatic, ttt);
		}
		break;

		case 116:
		{
			if (!refresh) {
				GetWindowText(hEdit, buf, sizeof(buf));
				if (*buf == '0') *buf = 0;
				int a = lstrlen(buf);
				if (a == 0 || a == 1) buf[0] = '0';
				else StrNCpy(buf, buf, a);
				SetWindowText(hEdit, buf);
			}
		}
		break;

		case 117:
		{
			memset(&buf[1], 0, lstrlen(buf));
			buf[0] = '0';
			SetWindowText(hEdit, buf);
		}
		break;

		case 118:
		{
			refresh = false;
			operation[0] = 0;
			operation[1] = 0;
			leftOperand = NULL;
			memset(&buf[1], 0, lstrlen(buf));
			buf[0] = '0';
			SetWindowText(hEdit, buf);
			SetWindowText(hStatic, buf);
		}
		break;

		case 119:
		{
			operation[0] = operation[1];
			operation[1] = 5;
			refresh = true;
			if (operation[0] == 0) leftOperand = _wtof(buf);
			StrCat(ttt, buf);
			StrCat(ttt, TEXT(" / "));
			SetWindowText(hStatic, ttt);
		}
		break;


		case 201:
		{
			OpenClipboard(0);
			EmptyClipboard();
			HGLOBAL hStrMem = GlobalAlloc(GMEM_MOVEABLE, sizeof(buf));
			void* pStrMem = GlobalLock(hStrMem);
			memcpy(pStrMem, buf, sizeof(buf));
			GlobalUnlock(pStrMem);
			SetClipboardData(CF_UNICODETEXT, hStrMem);
			CloseClipboard();
			//SendMessage(hEdit, WM_COPY, 0, 0);
		}
		break;

		case 202:
		{
			/*HGLOBAL hglb = GetClipboardData(CF_TEXT);
			if (hglb != NULL)
			{
				LPCSTR* lptstr = GlobalLock(hglb);
				if (lptstr != NULL)
				{
					// Обращаемся к определяемой прикладной программой функции
					// ReplaceSelection, чтобы вставить текст и перерисовать окно.

					SetWindowText(hStatic, lptstr);
					GlobalUnlock(hglb);
				}
			}
			CloseClipboard();
			memset(&buf[1], 0, lstrlen(buf));
			buf[0] = '0';
			SetWindowText(hStatic, buf);*/
			SendMessage(hEdit, WM_PASTE, 0, 0);
		}
		break;


		case 211:
		{
			MessageBox(hWnd, TEXT("Терентьев В.О. ИУ5-43"), TEXT("Message"), MB_OK);
		}
		break;
		}
	}
	break;
	/*case WM_SIZE:
	{
		RECT rc;
		GetClientRect(hwndDlg, &rc);
		SetWindowPos(hEdit, 0, rc.left + 4, rc.top + 4, rc.right - rc.left - 8, rc.bottom - rc.top - 34, SWP_NOZORDER);
		SetWindowPos(hOk, 0, rc.left + 4, rc.bottom - 26, rc.right - rc.left - 112, 22, SWP_NOZORDER);
		SetWindowPos(hCancel, 0, rc.right - 104, rc.bottom - 26, 100, 22, SWP_NOZORDER);
	}
	break;*/
	case WM_DESTROY:
		PostQuitMessage(0);
		break; 			// Завершение программы 
	default: 			// Обработка сообщения по умолчанию 
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	switch (operation[0]) {
	case 0:
		break;
	case 1:
	{
		operation[0] = 0;
		string klj = to_string(leftOperand);
		copy(klj.begin(), klj.begin() + 8, buf);
		SetWindowText(hEdit, buf);
	}
	break;
	case 2:
	{

		operation[0] = 0;
		PWSTR qwe = StrChr(buf, ',');
		if (qwe != NULL) {
			*qwe = '.';
		}
		leftOperand = leftOperand + _wtof(buf);
		string klj = to_string(leftOperand);
		copy(klj.begin(), klj.begin() + 8, buf);
		//*(double*)buf = leftOperand;
		SetWindowText(hEdit, buf);
	}
	break;

	case 3:
	{
		operation[0] = 0;
		PWSTR qwe = StrChr(buf, ',');
		if (qwe != NULL) {
			*qwe = '.';
		}
		leftOperand = leftOperand - _wtof(buf);
		string klj = to_string(leftOperand);
		copy(klj.begin(), klj.begin() + 8, buf);
		SetWindowText(hEdit, buf);
	}
	break;

	case 4:
	{
		operation[0] = 0;
		PWSTR qwe = StrChr(buf, ',');
		if (qwe != NULL) {
			*qwe = '.';
		}
		leftOperand = leftOperand * _wtof(buf);
		string klj = to_string(leftOperand);
		copy(klj.begin(), klj.begin() + 8, buf);
		SetWindowText(hEdit, buf);
	}
	break;

	case 5:
	{
		operation[0] = 0;
		PWSTR qwe = StrChr(buf, ',');
		if (qwe != NULL) {
			*qwe = '.';
		}
		leftOperand = leftOperand / _wtof(buf);
		string klj = to_string(leftOperand);
		string::iterator it = klj.end();
		copy(klj.begin(), klj.begin() + 8, buf);
		SetWindowText(hEdit, buf);
	}
	break;
	}

	return 0;
}