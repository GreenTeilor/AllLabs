#pragma once

#include "TextRect.hpp"
#include <vector>

class Table
{
private:
    int m_rows;
    int m_cols;
    RECT m_tableRect;

    std::vector<std::vector<RECT>> m_cellsDimensions;
    std::vector<std::vector<TextRect>> m_texts;
    std::string m_text;

public:
    Table(int rowNum, int colNum, RECT clientRect);
    Table();

    void setText(const std::string& str);
    void setText(const TextRect& text);

    inline void resize(RECT clientRect);
    inline void resize(int rows, int cols);
    void resize(int rows, int cols, RECT clientRect);
    void calcCellsSize(HDC hdc, int& fontSize);
    RECT getRect() { return m_tableRect; };

    void draw(HDC hdc, int offset);
};