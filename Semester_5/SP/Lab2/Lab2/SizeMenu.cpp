#include "SizeMenu.hpp"

#include <stdexcept>
#include <memory>
#include <chrono>
#include <fstream>
#include <sstream>
#include <iterator>
#include <Windowsx.h>
#include <CommCtrl.h>
#include <mshtmcid.h>
#include <Windef.h>

SizeMenu::SizeMenu(HWND parent, const std::string& className, const std::string& label) : m_className{className}, m_label{ label }
{
    try
    {
        RECT rect;
        GetWindowRect(parent, &rect);

        this->m_parent = parent;

        m_wndHandle = CreateWindowEx(
        0,                              // Optional window styles.
        className.c_str(),              // Window class
        label.c_str(),                  // Window text
        WS_DLGFRAME,   // Window style
        // Size and position
        rect.right / 2 - 160, rect.bottom / 2 - 90, 180, 280,
        parent,                        // Parent window    
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
        throw;
    }
    
}

HWND SizeMenu::addButton(const std::string &label, const RECT &posSize, HMENU id)
{
    return CreateWindow("Button", label.c_str(), WS_VISIBLE | WS_CHILD, posSize.left, posSize.top, posSize.right, posSize.bottom, m_wndHandle, id, NULL, NULL);
}
HWND SizeMenu::addEdit(const std::string &label, const RECT &posSize, HMENU id)
{
    return CreateWindow("Edit", label.c_str(), WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, posSize.left, posSize.top, posSize.right, posSize.bottom, m_wndHandle, id, NULL, NULL);
}
HWND SizeMenu::addLabel(const std::string &label, const RECT &posSize, HMENU id)
{
    return CreateWindow("Static", label.c_str(), WS_VISIBLE | WS_CHILD, posSize.left, posSize.top, posSize.right, posSize.bottom, m_wndHandle, id, NULL, NULL);
}

int SizeMenu::run()
{
    MSG msg{};
    ShowWindow(m_wndHandle, SW_SHOW);

    while (GetMessage(&msg, m_wndHandle, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return (int)(msg.wParam);
}

LRESULT SizeMenu::appProg(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    SizeMenu* pWindow;
    if(uMsg == WM_NCCREATE)
    {
        pWindow = (SizeMenu*)(((CREATESTRUCTW*)lParam)->lpCreateParams);
        SetLastError(0);
        if(!SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pWindow))
        {
            if(GetLastError() != 0)
                return false;
        }
    }
    else
        pWindow = (SizeMenu*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    
    if(pWindow)
    {
        pWindow->m_wndHandle = hwnd;
        return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT SizeMenu::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {  
        case WM_CREATE:
        {
            m_close = addButton("Close", {40, 150, 80, 30}, (HMENU)CLOSE);
            m_ok = addButton("Ok", {40, 190, 80, 30}, (HMENU)OK);

            m_editRow = addEdit("", {30, 40, 100, 30}, (HMENU)EDIT_ROW);
            addLabel("Rows", {30, 10, 35, 20}, 0);
            m_editCol = addEdit("", {30, 110, 100, 30}, (HMENU)EDIT_COL);
            addLabel("Columns", {30, 80, 57, 20}, 0);
            return true;
        }
        case WM_COMMAND:
        {
            switch (wParam)
            {
            case OK:
            {
                char text[100];
                GetWindowText(m_editRow, text, 100);
                {
                    std::istringstream in(text);
                    in >> resRow;
                }
                GetWindowText(m_editCol, text, 100);
                {
                    std::istringstream in(text);
                    in >> resCol;
                }
            }
            case CLOSE:
                EnableWindow(m_parent, true);
                DestroyWindow(hwnd);                
                break;
            case EDIT_ROW:
            {
                
                break;
            }
            case EDIT_COL:
            {
                char text[100];
                GetWindowText(m_editRow, text, 100);
                break;
            }
            }
            break;
        }
        case WM_GETMINMAXINFO:
        {
            LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
            lpMMI->ptMinTrackSize.x = 300;
            lpMMI->ptMinTrackSize.y = 300;
            return 0;
        }
        case WM_DESTROY:
        {
            EnableWindow(m_parent, true);
            return 0;
        }
        case WM_SIZE:
        {
            m_widht = LOWORD(lParam);
            m_height = HIWORD(lParam);
            return 0;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void SizeMenu::registerClass(const CHAR* className_)
{
    WNDCLASSEX wc = { sizeof(WNDCLASSEX) };

    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.lpfnWndProc   = SizeMenu::appProg;
    wc.hInstance     = GetModuleHandleW(nullptr);
    wc.lpszClassName = className_;
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = nullptr;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    
    if(!RegisterClassEx(&wc))
        throw std::runtime_error{"Failed to create window class!"};
}

HWND SizeMenu::getHandle() 
{
    return m_wndHandle; 
}
