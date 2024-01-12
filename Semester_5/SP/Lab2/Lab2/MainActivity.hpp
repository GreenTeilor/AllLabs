#pragma once

#include <Windows.h>

#include <cstdint>
#include <string>
#include <exception>

#include "Table.hpp"


class MainActivity
{
private:
    Table m_table;
    std::string m_fontName{ "Courier new" };
    int m_fontSize{ 23 };
    int m_offset{ 0 };

    std::string* m_cellTextPtr;

    HWND m_wndHandle{};
    std::string m_className;
    std::string m_label;
    long m_appWidht, m_appHeight;

    MainActivity();
    static LRESULT CALLBACK appProg(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    void invalidateRect();
    HWND addEdit(const std::string& lable, const UINT type, const RECT& posSize, HMENU id);
    inline void registerClass(const CHAR* className);

public:
    enum Menu
    {
        RESIZE
    };
    MainActivity(std::string filePath);
    int run();
};