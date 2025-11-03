#pragma once

#include "uiControl.h"

class StaticControl : public UIControl {
public:
    StaticControl(int id = 0) : UIControl(id) {};
    virtual ~StaticControl() = default;

    virtual bool Create(
        HWND hParentWindow,
        HINSTANCE hInstance,
        const std::wstring initialText,
        int x, int y, int width, int height,
        DWORD style = WS_CHILD | WS_VISIBLE
    ) override;
};