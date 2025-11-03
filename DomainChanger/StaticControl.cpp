#include "StaticControl.h"

bool StaticControl::Create(HWND hParentWindow, HINSTANCE hInstance, const std::wstring initialText, int x, int y, int width, int height, DWORD style) {
    m_baseRect = { x, y, x + width, y + height };
    HWND hwnd = CreateWindowEx(
        0, L"STATIC", initialText.c_str(),
        style,
        0, 0, 0, 0,
        hParentWindow, NULL, hInstance, NULL
    );
    if (!hwnd) {
        return false;
    }
    m_hwnd = hwnd;
    return true;
}
