#pragma once

#include <Windows.h>
#include <string>
#include <functional>

class UIControl {
public:
    UIControl();
    virtual ~UIControl() = default;

    struct CreateParams {
        std::wstring text;
        int x, y, width, height;
        DWORD style;
    };

    void Setup(int x, int y, int width, int height, const std::wstring& text, DWORD style = 0);

    static const int s_baseDpi = 120;
    static int Scale(int val, int dpi) {
        return MulDiv(val, dpi, s_baseDpi);
    }

    virtual bool Create(HWND hParentWindow, HINSTANCE hInstance) = 0;

    virtual void OnCommand(WORD notificationCode) {}

    void UpdateLayout(int newDpi, HFONT hFont);

    HWND GetHwnd() const { return m_hwnd; }
    int GetId() const { return static_cast<int>(m_id); }

    UIControl(const UIControl&) = delete;
    UIControl& operator=(const UIControl&) = delete;

protected:
    long long int m_id;
    HWND m_hwnd;
    CreateParams m_params;

private:
    static int GenerateId();
};
