#pragma once

#include <Windows.h>
#include <string>

class UIControl {
public:
    UIControl(int id) : m_id(id), m_hwnd(nullptr) {};
    virtual ~UIControl() {};
    virtual bool Create(
        HWND hParentWindow,
        HINSTANCE hInstance,
        const std::wstring initialText,
        int x, int y, int width, int height,
        DWORD style
    ) = 0;

    HWND GetHwnd() const { return m_hwnd; }
    int GetId() const { return m_id; }

    UIControl(const UIControl&) = delete;
    UIControl& operator=(const UIControl&) = delete;

protected:
    long long int m_id;
    HWND m_hwnd;
};
