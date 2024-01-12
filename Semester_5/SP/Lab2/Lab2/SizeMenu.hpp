#pragma once

#include <Windows.h>

#include <cstdint>
#include <string>
#include <vector>
#include <exception>

class SizeMenu
{
private:
    HWND m_wndHandle{};
    HWND m_parent{};
    HWND m_close, m_ok, m_editRow, m_editCol;
    std::string m_className;
    std::string m_label;
    long m_widht, m_height;

    static LRESULT CALLBACK appProg(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
    enum messages
    {
        CLOSE, OK, EDIT_ROW, EDIT_COL
    };
    int resRow{ 0 }, resCol{ 0 };
    int run();

    static void registerClass(const CHAR* className);
    SizeMenu(HWND parent, const std::string& className, const std::string& label);

    HWND addButton(const std::string& label, const RECT& posSize, HMENU id);
    HWND addEdit(const std::string& label, const RECT& posSize, HMENU id);
    HWND addLabel(const std::string& label, const RECT& posSize, HMENU id);

    HWND getHandle();
};