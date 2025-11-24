#pragma once

#include "UIControl.h"
#include <functional>

class EditControl : public UIControl {
public:
    using OnValueChangedCallback = std::function<void(const std::wstring)>;

    EditControl() {
        m_params.style = WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL;
    };

    void SetOnValueChanged(OnValueChangedCallback callback) {
        m_callback = callback;
    }

    virtual bool Create(HWND hParentWindow, HINSTANCE hInstance) override;

    virtual void OnCommand(WORD notificationCode) override;

    std::wstring GetText() const;
    void SetText(const std::wstring& text);

protected:
    void SetControlTextLimit(HWND hwnd, int limit) const;

private:    
    OnValueChangedCallback m_callback;
};