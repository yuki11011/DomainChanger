#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>
#include "UIControl.h"

class UIManager {
public:
    UIManager() = default;

    template <typename T>
    T* AddControl(int x, int y, int w, int h, const std::wstring& text = L"") {
        auto ctrl = std::make_unique<T>();
        ctrl->Setup(x, y, w, h, text);
        T* ptr = ctrl.get();
        m_controls.push_back(std::move(ctrl));
        return ptr;
    }

    void CreateControls(HWND hwnd, HINSTANCE hInstance);
    bool HandleCommand(WPARAM wParam);
    void UpdateLayoutAndFonts(int newDpi);

    bool ShowConfirmationDialog();

    std::wstring OpenFilePicker(HWND hwnd);

    UIManager(const UIManager&) = delete;
    UIManager& operator=(const UIManager&) = delete;
    UIManager(UIManager&&) = delete;
    UIManager& operator=(UIManager&&) = delete;

private:
    std::vector<std::unique_ptr<UIControl>> m_controls;
    std::map<int, UIControl*> m_controlMap;
    HFONT m_hFont = nullptr;
};
