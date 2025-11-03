#include "UIControl.h"

void UIControl::UpdateLayout(int newDpi, HFONT hFont) {
    if (!m_hwnd) return;

    int scaledX = Scale(m_baseRect.left, newDpi);
    int scaledY = Scale(m_baseRect.top, newDpi);
    int scaledW = Scale(m_baseRect.right - m_baseRect.left, newDpi);
    int scaledH = Scale(m_baseRect.bottom - m_baseRect.top, newDpi);

    SetWindowPos(m_hwnd, NULL, scaledX, scaledY, scaledW, scaledH, SWP_NOZORDER);
    SendMessage(m_hwnd, WM_SETFONT, (WPARAM)hFont, TRUE);
}