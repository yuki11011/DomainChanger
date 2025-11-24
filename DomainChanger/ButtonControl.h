#pragma once

#include "UIControl.h"
#include <functional>

class ButtonControl : public UIControl {
public:
    using OnClickCallback = std::function<void()>;
    ButtonControl() {
        m_params.style = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON;
    };

    void SetOnClick(OnClickCallback callback) {
        m_callback = callback;
    }

    virtual bool Create(HWND hParentWindow, HINSTANCE hInstance) override;

    virtual void OnCommand(WORD notificationCode) override;

    void SetText(const std::wstring& text);

private:
    OnClickCallback m_callback;
};