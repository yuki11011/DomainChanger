#include "ButtonControl.h"

bool ButtonControl::Create(HWND hParentWindow, HINSTANCE hInstance, const std::wstring initialText, int x, int y, int width, int height, DWORD style) {
    HWND hwnd = CreateWindowEx(
        0, L"BUTTON", initialText.c_str(),
        style,
        x, y, width, height,
        hParentWindow, (HMENU)m_id, hInstance, NULL);
    if (!hwnd) {
        return false;
    }
    m_hwnd = hwnd;
    return true;
}

void ButtonControl::SetText(const std::wstring& text) {
    SetWindowTextW(m_hwnd, text.c_str());
}
