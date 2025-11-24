#pragma once

#include "UIControl.h"

class StaticControl : public UIControl {
public:
    StaticControl() {
        m_params.style = WS_CHILD | WS_VISIBLE;
    };
    virtual ~StaticControl() = default;

    virtual bool Create(HWND hParentWindow, HINSTANCE hInstance) override;
};