#pragma once

#include <Windows.h>
#include <string>

class UIControl {
public:
    UIControl(int id) : m_id(id), m_hwnd(nullptr), m_baseRect({ 0, 0, 0, 0 }) {}
    virtual ~UIControl() {};

    static const int s_baseDpi = 120;
    static int Scale(int val, int dpi) {
        return MulDiv(val, dpi, s_baseDpi);
    }

    virtual bool Create(
        HWND hParentWindow,
        HINSTANCE hInstance,
        const std::wstring initialText,
        int x, int y, int width, int height,
        DWORD style
    ) = 0;

    void UpdateLayout(int newDpi, HFONT hFont);

    HWND GetHwnd() const { return m_hwnd; }
    int GetId() const { return static_cast<int>(m_id); }

    UIControl(const UIControl&) = delete;
    UIControl& operator=(const UIControl&) = delete;

protected:
    long long int m_id;
    HWND m_hwnd;
    RECT m_baseRect;
};
