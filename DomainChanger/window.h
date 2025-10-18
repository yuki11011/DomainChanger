#pragma once

#include <Windows.h>
#include <string>
#include "uiManager.h"

class Window {
public:
    Window(HINSTANCE hInstance, int nCmdShow, const std::wstring& windowTitle, int width = 1280, int height = 720);
    ~Window();
    bool Create();
    void Show();
    HWND GetHWND() const;
    int GetWidth() const;
    int GetHeight() const;
    static LRESULT CALLBACK StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
    LRESULT CALLBACK MessageHandler(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    HINSTANCE m_hInstance;
    int m_nCmdShow;
    HWND m_hWnd;
    std::wstring m_windowTitle;
    int m_width;
    int m_height;
};
