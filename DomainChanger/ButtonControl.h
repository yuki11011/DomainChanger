#pragma once

#include "UIControl.h"

class ButtonControl : public UIControl {
public:
    ButtonControl(int id) : UIControl(id) {};
    virtual ~ButtonControl() = default;

    virtual bool Create(
        HWND hParentWindow,
        HINSTANCE hInstance,
        const std::wstring initialText,
        int x, int y, int width, int height,
        DWORD style = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON
    ) override;

    void SetText(const std::wstring& text);
};