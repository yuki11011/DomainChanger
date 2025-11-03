#include "StaticControl.h"

bool StaticControl::Create(HWND hParentWindow, HINSTANCE hInstance, const std::wstring initialText, int x, int y, int width, int height, DWORD style) {
    HWND hwnd = CreateWindowEx(
        0, L"STATIC", initialText.c_str(),
        style,
        x, y, width, height,
        hParentWindow, NULL, hInstance, NULL
    );
    if (!hwnd) {
        return false;
    }
    m_hwnd = hwnd;
    return true;
}
