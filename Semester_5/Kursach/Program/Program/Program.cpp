#include "framework.h"
#include "Program.h"
#include <map>
#include <string>
#include <stdlib.h>
#include <regex>
#include "Const.h"
#include "Field.h"
#include "DrawableField.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
HWND hWnd;                                      // Дескриптор окна
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

Field field{ 10, 10, 20 };
DrawableField drawableField{ field, hWnd, hInst };
int timer = 0;
int flagsSet = 0;
HBITMAP digitsBitmap;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Difficulty(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK fieldActions(HWND hButton, UINT message, WPARAM wParam, LPARAM lParam, 
    UINT_PTR uIdSubclass, DWORD_PTR dwRefData);

void resetStatistics(HWND hWnd);
void checkItem(HWND hWnd, int wmId);
void getDesktopResolution(int& width, int& height);
int getWindowWidth();
int getWindowHeight();
void changeWindowPositionAndDimension();

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.
    Const::loadImages(); //Images load
    digitsBitmap = Const::images.at(Type::Types::DIGITS);

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PROGRAM, szWindowClass, MAX_LOADSTRING);
    
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    SetTimer(hWnd, ID_TIMER, 1000, NULL);

    //Field creation
    drawableField.update(true, fieldActions);
    changeWindowPositionAndDimension();

    //Smile creation
    HWND hSmile = CreateWindowEx(0, L"BUTTON", L"", WS_CHILD | WS_VISIBLE | BS_BITMAP | BS_NOTIFY | BS_PUSHBUTTON,
        getWindowWidth() / 2 - Const::smileWidth, Const::interfaceElementsTopGap, Const::smileWidth, Const::smileHeight, hWnd, (HMENU)IDM_SMILE, hInstance, 0);
    SendMessage(hSmile, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)Const::images.at(Type::Types::SMILE_HAPPY));

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROGRAM));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROGRAM));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PROGRAM);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            int buttonNumber = 0;
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_NEW:
                resetStatistics(hWnd);
                SendMessage(GetDlgItem(hWnd, IDM_SMILE), BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)Const::images.at(Type::Types::SMILE_HAPPY));
                /*====================================*/

                //HERE CODE ON NEW GAME CREATION!!!
                field.generate(field.getWidth(), field.getHeight(), field.getNumMines());
                drawableField.update(false, fieldActions);
                /*====================================*/
                break;
            case IDM_DIFFICULTY_EASY:
                resetStatistics(hWnd);
                SendMessage(GetDlgItem(hWnd, IDM_SMILE), BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)Const::images.at(Type::Types::SMILE_HAPPY));
                //Code to set easy difficulty
                field.generate(20, 20, 40);
                drawableField.update(true, fieldActions);
                changeWindowPositionAndDimension();
                checkItem(hWnd, IDM_DIFFICULTY_EASY);
                break;
            case IDM_DIFFICULTY_MEDIUM:
                resetStatistics(hWnd);
                SendMessage(GetDlgItem(hWnd, IDM_SMILE), BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)Const::images.at(Type::Types::SMILE_HAPPY));
                //Code to set medium difficulty
                field.generate(30, 30, 100);
                drawableField.update(true, fieldActions);
                changeWindowPositionAndDimension();
                checkItem(hWnd, IDM_DIFFICULTY_MEDIUM);
                break;
            case IDM_DIFFICULTY_HARD:
                resetStatistics(hWnd);
                SendMessage(GetDlgItem(hWnd, IDM_SMILE), BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)Const::images.at(Type::Types::SMILE_HAPPY));
                //Code to set hard difficulty
                field.generate(40, 40, 200);
                drawableField.update(true, fieldActions);
                changeWindowPositionAndDimension();
                checkItem(hWnd, IDM_DIFFICULTY_HARD);
                break;
            case IDM_DIFFICULTY_CUSTOM:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIFFICULTYBOX), hWnd, Difficulty);
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break; 
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case IDM_SMILE:
                resetStatistics(hWnd);
                field.generate(field.getWidth(), field.getHeight(), field.getNumMines());
                drawableField.update(false, fieldActions);
                SendMessage(GetDlgItem(hWnd, IDM_SMILE), BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)Const::images.at(Type::Types::SMILE_HAPPY));
                SetFocus(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_TIMER:
        {
            if (field.isDeminingStarted() && !field.isGameEnded() && timer < 999)
            {
                ++timer;
                InvalidateRect(hWnd, NULL, FALSE);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            HDC hdcBitmap = CreateCompatibleDC(hdc);

            digitsBitmap = (HBITMAP)SelectObject(hdcBitmap, digitsBitmap);

            //For timer
            BitBlt(hdc, getWindowWidth() - 69, 6, 15, 23, hdcBitmap, 17 * ((timer / 100) % 10) + 1, 0, SRCCOPY);
            BitBlt(hdc, getWindowWidth() - 54, 6, 15, 23, hdcBitmap, 17 * ((timer / 10) % 10) + 1, 0, SRCCOPY);
            BitBlt(hdc, getWindowWidth() - 39, 6, 15, 23, hdcBitmap, 17 * (timer % 10) + 1, 0, SRCCOPY);

            //For mines to mark left
            int flagsLeftToSet = ((field.getNumMines() - flagsSet) > 0) ? (field.getNumMines() - flagsSet) : 0;
            BitBlt(hdc, 7, 6, 15, 23, hdcBitmap, 17 * ((flagsLeftToSet / 100) % 10) + 1, 0, SRCCOPY);
            BitBlt(hdc, 22, 6, 15, 23, hdcBitmap, 17 * ((flagsLeftToSet / 10) % 10) + 1, 0, SRCCOPY);
            BitBlt(hdc, 37, 6, 15, 23, hdcBitmap, 17 * (flagsLeftToSet % 10) + 1, 0, SRCCOPY);

            digitsBitmap = (HBITMAP)SelectObject(hdcBitmap, digitsBitmap);
            DeleteDC(hdcBitmap);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_LBUTTONDOWN:
        {
            if (!field.isGameEnded()) 
            {
                SendMessage(GetDlgItem(hWnd, IDM_SMILE), BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)Const::images.at(Type::Types::SMILE_SHOCKED));
            }
        }
        break;

    case WM_LBUTTONUP:
        {
            if (!field.isGameEnded()) 
            {
                SendMessage(GetDlgItem(hWnd, IDM_SMILE), BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)Const::images.at(Type::Types::SMILE_HAPPY));
            }
        }
        break;
    case WM_DESTROY:
        KillTimer(hWnd, ID_TIMER);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

// Обработчик сообщений для окна "Пользовательская сложность".
INT_PTR CALLBACK Difficulty(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK)
        {
            resetStatistics(hWnd);
            SendMessage(GetDlgItem(hWnd, IDM_SMILE), BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)Const::images.at(Type::Types::SMILE_HAPPY));
            /*====================================*/

                //HERE CODE ON CHANGE DIFFICULTY PARAMS!!!
            wchar_t widthBuf[1024];
            wchar_t heightBuf[1024];
            GetWindowText(GetDlgItem(hDlg, IDC_EDITFIELD_WIDTH), widthBuf, 1024);
            GetWindowText(GetDlgItem(hDlg, IDC_EDITFIELD_HEIGHT), heightBuf, 1024);
            std::wregex digitsRegex{L"([0-9]+)"};
            int width;
            int height;
            int hDimension;
            int vDimension;
            getDesktopResolution(hDimension, vDimension);
            if (std::regex_match(std::wstring{ widthBuf }, digitsRegex) && std::regex_match(std::wstring{ heightBuf }, digitsRegex)
                && (width = _wtoi(widthBuf)) <= (hDimension - 18) / Const::imgWidth && (height = _wtoi(heightBuf)) <= (vDimension - 96 * 2) / Const::imgHeight
                && width > 9 && height > 9)
            {
                field.generate(width, height, width * height * 0.1);
                drawableField.update(true, fieldActions);
                changeWindowPositionAndDimension();

                /*====================================*/
                checkItem(hWnd, IDM_DIFFICULTY_CUSTOM);
                EndDialog(hDlg, LOWORD(wParam));
            }
            else
            {
                MessageBox(hDlg, L"Хотя бы одно из значений слишком велико или мало или не является числом", L"Ошибка", MB_OK);
            }
            return (INT_PTR)TRUE;
        }
        else if (LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

LRESULT CALLBACK fieldActions(HWND btnHwnd, UINT message, WPARAM wParam, LPARAM lParam,
    UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    int x = dwRefData % field.getWidth(); //HAS TO BE DIVIDED BY ACTUAL FIELD WIDTH
    int y = dwRefData / field.getWidth(); //HAS TO BE DIVIDED BY ACTUAL FIELD WIDTH
    HBITMAP img = Const::images.at(Type::Types::EMPTY);
    
    switch (message)
    {
    case WM_LBUTTONDOWN:
        if (!field.isGameEnded()) {
            SendMessage(GetDlgItem(hWnd, IDM_SMILE), BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)Const::images.at(Type::Types::SMILE_SHOCKED));
        }
        return TRUE;
    case WM_LBUTTONUP:
        if (field.isGameEnded()) {
            return TRUE;
        }
        SendMessage(GetDlgItem(hWnd, IDM_SMILE), BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)Const::images.at(Type::Types::SMILE_HAPPY));
        field.reveal(x, y);
        if (field[y][x].getInner() == Type::Types::BOMB && field[y][x].getCover() != Type::Types::FLAG) {
            field.revealAll();
            field[y][x].setInner(Type::Types::BOMB_BOOM);
            SendMessage(GetDlgItem(hWnd, IDM_SMILE), BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)Const::images.at(Type::Types::SMILE_DEAD));
        }
        if (field.isDemined()) {
            SendMessage(GetDlgItem(hWnd, IDM_SMILE), BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)Const::images.at(Type::Types::SMILE_COOL));
        }
        drawableField.update(false, fieldActions);
        return TRUE;
    case WM_RBUTTONDOWN:
        if (field[y][x].changeFlag() == Type::Types::FLAG)
        {
            ++flagsSet;
        }
        else if (!field[y][x].isOpened())
        {
            --flagsSet;
        }
        InvalidateRect(hWnd, NULL, FALSE);
        drawableField.update(false, fieldActions);
        return TRUE;
    case WM_NCDESTROY:
        RemoveWindowSubclass(btnHwnd, fieldActions, uIdSubclass);
        return DefSubclassProc(btnHwnd, message, wParam, lParam);
    default:
        return DefSubclassProc(btnHwnd, message, wParam, lParam);
    }
    
}

void resetStatistics(HWND hWnd)
{
    timer = 0;
    flagsSet = 0;
    InvalidateRect(hWnd, NULL, FALSE);
}

void checkItem(HWND hWnd, int wmId) 
{
    CheckMenuItem(GetMenu(hWnd), IDM_DIFFICULTY_EASY, MF_BYCOMMAND | MF_UNCHECKED);
    CheckMenuItem(GetMenu(hWnd), IDM_DIFFICULTY_MEDIUM, MF_BYCOMMAND | MF_UNCHECKED);
    CheckMenuItem(GetMenu(hWnd), IDM_DIFFICULTY_HARD, MF_BYCOMMAND | MF_UNCHECKED);
    CheckMenuItem(GetMenu(hWnd), IDM_DIFFICULTY_CUSTOM, MF_BYCOMMAND | MF_UNCHECKED);

    CheckMenuItem(GetMenu(hWnd), wmId, MF_BYCOMMAND | MF_CHECKED);
}

void getDesktopResolution(int& width, int& height)
{
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    width = desktop.right;
    height = desktop.bottom;
}

//Get preferred window width with this field
int getWindowWidth()
{
    return 18 + Const::imgWidth * field.getWidth();
}

//Get preferred window height with this field
int getWindowHeight()
{
    return 96 + Const::imgHeight * field.getHeight();
}

void changeWindowPositionAndDimension()
{
    int horizontal = 0;
    int vertical = 0;
    getDesktopResolution(horizontal, vertical);
    MoveWindow(GetDlgItem(hWnd, IDM_SMILE), getWindowWidth() / 2 - Const::smileWidth, Const::interfaceElementsTopGap, Const::smileWidth, Const::smileHeight, TRUE); //Move smile button
    SetWindowPos(hWnd,
        HWND_TOP,
        horizontal / 2 - getWindowWidth() / 2,
        vertical / 2 - getWindowHeight() / 2,
        getWindowWidth(), getWindowHeight(),
        SWP_SHOWWINDOW);
}