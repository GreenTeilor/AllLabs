#include "DrawableField.h"

DrawableField::DrawableField(Field& field, HWND& hWnd, HINSTANCE& hInst) : m_field{ field }, m_hWnd{ hWnd }, m_hInst{ hInst }, m_buttons{}, m_images{}
{

}

void DrawableField::update(bool isRecreateButtons, SUBCLASSPROC fieldActions)
{
    if (isRecreateButtons)
    {
        int btnNumber = 0;
        for (auto& btn : m_buttons)
        {
            DestroyWindow(btn);
        }
        m_buttons.clear();
        m_buttons.resize(m_field.getWidth() * m_field.getHeight());

        m_images.clear();
        m_images.resize(m_field.getWidth() * m_field.getHeight());

        for (int i = 0; i < m_field.getHeight(); i++)
        {
            for (int j = 0; j < m_field.getWidth(); j++)
            {
                HWND btnHwnd = CreateWindow(L"button", L"",
                    WS_CHILD | WS_VISIBLE | BS_BITMAP | BS_NOTIFY | BS_PUSHBUTTON,
                    1 + Const::imgWidth * j, 35 + Const::imgHeight * i, Const::imgWidth, Const::imgHeight, m_hWnd, (HMENU)btnNumber, m_hInst, 0);
                HBITMAP img = Const::images.at(Type::Types::CLOSED);
                SendMessage(btnHwnd, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)img);

                if (!SetWindowSubclass(GetDlgItem(m_hWnd, btnNumber), fieldActions, 0, btnNumber))
                {
                    DestroyWindow(m_hWnd);
                }

                m_buttons[btnNumber] = btnHwnd;

                m_images[btnNumber] = img;

                ++btnNumber;
            }
        }
    }
    else
    {
        for (int i = 0; i < m_field.getHeight(); ++i)
        {
            for (int j = 0; j < m_field.getWidth(); ++j)
            {
                if (m_images[i * m_field.getWidth() + j] != Const::images.at(m_field[i][j].getType()))
                {
                    SendMessage(m_buttons[i * m_field.getWidth() + j], BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)Const::images.at(m_field[i][j].getType()));
                    m_images[i * m_field.getWidth() + j] = Const::images.at(m_field[i][j].getType());
                    //BELOW IS SETTING REVEALED BUTTONS STYLE TO *PRESSED*, WHICH STANDS OUT UNREVEALED BUTTONS
                    //THIS IMPLEMENTATION TAKES INTO ACCOUNT ONLY DIFFERENCE BETWEEN REVEALED AND UNREVEALED BUTTON
                    //IF YOU WANT TO ADD SOME DIVERSITY YOU SHOULD ADD SOME std::map OR METHOD, WHICH SET STYLE ACCORDING TO 
                    //CELL TYPE
                    if (m_field[i][j].isOpened())
                        SendMessage(m_buttons[i * m_field.getWidth() + j], BM_SETSTATE, TRUE, NULL);
                    else
                        SendMessage(m_buttons[i * m_field.getWidth() + j], BM_SETSTATE, FALSE, NULL);
                }
            }
        }
    }
}