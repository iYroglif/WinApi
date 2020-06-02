#include <Windows.h>
#include <tchar.h>
#include <string>

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
    static HWND a;
    switch (message)		 // Обработчик сообщений
    {
    case WM_LBUTTONUP:
    {
        if (!a) {
            a = FindWindow(NULL, TEXT("Окно 2"));
            if (!a)
                MessageBox(hWnd, TEXT("Окно не найдено"), TEXT("Error"), MB_OK);
            else
            {
                MessageBox(hWnd, TEXT("Окно найдено"), TEXT("Message"), MB_OK);
            }
        }
        else {
            LRESULT b = SendMessage(a, WM_USER + 1, (WPARAM)hWnd, lParam);
            //MessageBox(hWnd, TEXT("Сообщение отправлено"), TEXT("Message"), MB_OK);
        }
    }
    break;
    case WM_RBUTTONUP:
    {
        LRESULT b = SendMessage(a, WM_USER + 2, (WPARAM)hWnd, lParam);
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