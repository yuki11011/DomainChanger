#include "UIControl.h"

UIControl::UIControl() : m_hwnd(nullptr), m_params{} {
    m_id = GenerateId();
}

int UIControl::GenerateId() {
    static int s_currentId = 2000;
    return s_currentId++;
}

void UIControl::Setup(int x, int y, int width, int height, const std::wstring& text, DWORD style) {
    m_params.x = x;
    m_params.y = y;
    m_params.width = width;
    m_params.height = height;
    m_params.text = text;
    if (style != 0) m_params.style = style;
}

void UIControl::UpdateLayout(int newDpi, HFONT hFont) {
    if (!m_hwnd) return;

    int scaledX = Scale(m_params.x, newDpi);
    int scaledY = Scale(m_params.y, newDpi);
    int scaledW = Scale(m_params.width, newDpi);
    int scaledH = Scale(m_params.height, newDpi);

    SetWindowPos(m_hwnd, nullptr, scaledX, scaledY, scaledW, scaledH, SWP_NOZORDER | SWP_NOACTIVATE);

    SendMessageW(m_hwnd, WM_SETFONT, (WPARAM)hFont, TRUE);
}
