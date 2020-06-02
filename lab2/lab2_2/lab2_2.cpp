#include <Windows.h>
#include <tchar.h>

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
        _T("Окно 2"), 		// Заголовок окна 
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
    static int x = 0, r1, r2, r3, r4, r5, r6, r7;
    PAINTSTRUCT ps;
    static HDC hdc;

    switch (message)		 // Обработчик сообщений
    {
    case WM_PAINT:
    { 
        hdc = BeginPaint(hWnd, &ps);
        if (x == 1) {
            HPEN hPen1 = CreatePen(PS_SOLID, 7, RGB(0, 0, 0));
            SelectObject(hdc, hPen1);
            HBRUSH hBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
            SelectObject(hdc, hBrush);
            Rectangle(hdc, 10, 10, 360, 260);
        }
       else if (x > 1) {
            HPEN hPen1 = CreatePen(PS_SOLID, 7, RGB(r1 % 255, r2 % 255, r3 % 255));
            SelectObject(hdc, hPen1);
            HBRUSH hBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
            SelectObject(hdc, hBrush);
            Rectangle(hdc, r4 % 600, r5 % 600, r6 % 600, r7 % 600);
        }
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_USER+1:
    {
        r1 = rand(); r2 = rand(); r3 = rand(); r4 = rand(); r5 = rand(); r6 = rand(); r7 = rand();
        x++;
        InvalidateRect(hWnd, NULL, false);
    }
    break;
    case WM_USER + 2:
    {
        SendMessage((HWND)wParam, WM_SYSCOMMAND, SC_CLOSE, lParam);
        //CloseWindow((HWND)wParam);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break; 			// Завершение программы 
    default: 			// Обработка сообщения по умолчанию 
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}