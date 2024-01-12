#include "MainActivity.hpp"

#include <stdexcept>
#include <memory>
#include <chrono>
#include <fstream>
#include <iterator>
#include <Windowsx.h>
#include <CommCtrl.h>
#include <mshtmcid.h>
#include <Windef.h>
#include "SizeMenu.hpp"

MainActivity::MainActivity() : m_className{ "Lab_2_WNDCLASS" }, m_label{ "Lab 2" }
{
    try
    {
        registerClass(m_className.c_str());
        SizeMenu::registerClass("ResizeDLG");


        m_wndHandle = CreateWindowEx(
        0,                              // Optional window styles.
        m_className.c_str(),              // Window class
        m_label.c_str(),                  // Window text
        WS_OVERLAPPEDWINDOW,            // Window style
        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        nullptr,                        // Parent window    
        nullptr,                        // Menu
        GetModuleHandle(nullptr),       // Instance handle
        this                            // Additional application data
        );

        if (!m_wndHandle)
            throw std::runtime_error{"Failed to create window!"};

    }
    catch(const std::exception& e)
    {
        MessageBox(nullptr, e.what(), "ERROR", MB_OK | MB_ICONERROR);
        ExitProcess(EXIT_FAILURE);
    }
    
}

MainActivity::MainActivity(std::string filePath) : MainActivity()
{
    //To remove spaces
    m_table.resize(3, 5);
    m_table.setText(std::string(std::istream_iterator<char>(std::ifstream(filePath)), {}));
    
    //std::ifstream ifs(filePath);
    //std::string str(std::istreambuf_iterator<char>{ifs}, {});
    //table.setText(str);
}

int MainActivity::run()
{
    MSG msg{};
    ShowWindow(m_wndHandle, SW_SHOW);
    UpdateWindow(m_wndHandle);

    while(msg.message != WM_QUIT)
    {
        if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)(msg.wParam);
}

LRESULT MainActivity::appProg(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    MainActivity* pApp;
    if(uMsg == WM_NCCREATE)
    {
        pApp = (MainActivity*)(((CREATESTRUCTW*)lParam)->lpCreateParams);
        SetLastError(0);
        if(!SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pApp))
        {
            if(GetLastError() != 0)
                return false;
        }
    }
    else
        pApp = (MainActivity*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    
    if(pApp)
    {
        pApp->m_wndHandle = hwnd;
        return pApp->WindowProc(hwnd, uMsg, wParam, lParam);

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT MainActivity::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {  
        case WM_MOUSEWHEEL:
        {
            int prevOffset = m_offset;
            m_offset += GET_WHEEL_DELTA_WPARAM(wParam);
            m_offset = min(m_offset, 0);
            if(m_offset < -m_table.getRect().bottom + 100)
                m_offset = -m_table.getRect().bottom + 100;
            if(m_offset != prevOffset)
            {
                invalidateRect();
            }

            break;
        }
        case WM_CREATE:
        {
            auto hMenu = CreateMenu();
            AppendMenu(hMenu, MF_ENABLED | MF_STRING, RESIZE, "Resize"); //Resize table
            SetMenu(hwnd, hMenu);


            break;
        }
        case WM_COMMAND:
        {
            switch (wParam)
            {
            case RESIZE:
            {
                SizeMenu sizeMenu(hwnd, "ResizeDLG", "Resize"); 
                sizeMenu.run();

                if(sizeMenu.resCol && sizeMenu.resRow)
                {
                    m_table.resize(sizeMenu.resRow, sizeMenu.resCol);
                    invalidateRect();
                }
                break;
            }
            }
            break;
        }
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            auto secHDC = CreateCompatibleDC(hdc);
            auto secBM = CreateCompatibleBitmap(hdc, m_appWidht, m_appHeight);
            
            auto origBM = (HBITMAP)SelectBitmap(secHDC, secBM);


            auto hFont = CreateFont(-MulDiv(m_fontSize, GetDeviceCaps(hdc, LOGPIXELSY), 72), 
                                    0, 0, 0, 
                                    FW_NORMAL, 
                                    false, false, false,
                                    ANSI_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, m_fontName.c_str());
            
            SelectObject(secHDC, hFont);
            m_table.calcCellsSize(secHDC, m_fontSize);
            FillRect(secHDC, &ps.rcPaint, (HBRUSH) (WHITE_BRUSH));
            m_table.draw(secHDC, m_offset);

            BitBlt(hdc, 0, 0, m_appWidht, m_appHeight, secHDC, 0, 0, SRCCOPY);

            SelectBitmap(secHDC, origBM);
            DeleteObject(secBM);
            DeleteDC(secHDC);

            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_GETMINMAXINFO:
        {
            LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
            lpMMI->ptMinTrackSize.x = 300;
            lpMMI->ptMinTrackSize.y = 300;
            return 0;
        }
        case WM_CLOSE:
        {
            DestroyWindow(hwnd);
            return 0;
        }
        case WM_DESTROY:
        {
            PostQuitMessage(EXIT_SUCCESS);
            return 0;
        }
        case WM_SIZE:
        {
            m_appWidht = LOWORD(lParam);
            m_appHeight = HIWORD(lParam);
            m_table.resize({0, 0, m_appWidht, m_appHeight});
            return 0;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void MainActivity::invalidateRect()
{
    RECT rect{0, 0, m_appWidht, m_appHeight};
    InvalidateRect(m_wndHandle, &rect, false);
}

HWND MainActivity::addEdit(const std::string& lable, const UINT type, const RECT& posSize, HMENU id)
{
    return CreateWindow("Edit", lable.c_str(), WS_VISIBLE | WS_CHILD | WS_BORDER | type, posSize.left, posSize.top, posSize.right, posSize.bottom, m_wndHandle, id, NULL, NULL);
}

inline void MainActivity::registerClass(const CHAR* className)
{
     WNDCLASSEX wc = { sizeof(WNDCLASSEX) };

        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.lpfnWndProc   = MainActivity::appProg;
        wc.hInstance     = GetModuleHandleW(nullptr);
        wc.lpszClassName = className;
        wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
        wc.lpszMenuName = nullptr;
        wc.style = CS_HREDRAW | CS_VREDRAW;
        
        if(!RegisterClassEx(&wc))
            throw std::runtime_error{"Failed to create window class!"};
}

