#pragma once

#include <string>
#include <Windows.h>

class TextRect
{
private:
    std::string m_text;

public:
    TextRect(const std::string& text);
    TextRect();

    const std::string& operator=(const std::string& _text); 
    const std::string& operator=(const TextRect& other); 
    const std::string& getStr() const { return m_text; }; 
    std::string& getStr() { return m_text; }; 

    int draw(HDC hdc, RECT& Rect) noexcept;
    int computeHeight(HDC hdc, RECT& Rect) noexcept;
};