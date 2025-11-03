#pragma once

#include "uiControl.h"

class EditControl : public UIControl {
public:
    EditControl(int id = 0) : UIControl(id) {};
    virtual ~EditControl() = default;

    virtual bool Create(
        HWND hParentWindow,
        HINSTANCE hInstance,
        const std::wstring initialText,
        int x, int y, int width, int height,
        DWORD style = WS_CHILD | WS_VISIBLE | WS_BORDER
    ) override;

    std::wstring GetText() const;
    void SetText(const std::wstring& text);

    void AddLine(const std::wstring& message);

private:
    void SetControlTextLimit(HWND hwnd, int limit) const;
};