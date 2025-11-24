#include "ButtonControl.h"

bool ButtonControl::Create(HWND hParentWindow, HINSTANCE hInstance) {
    m_hwnd = CreateWindowEx(
        0, L"BUTTON", m_params.text.c_str(), m_params.style,
        m_params.x, m_params.y, m_params.width, m_params.height,
        hParentWindow, (HMENU)(intptr_t)m_id, hInstance, nullptr);
    return m_hwnd != nullptr;
}

void ButtonControl::OnCommand(WORD notificationCode) {
    if (notificationCode == BN_CLICKED && m_callback) {
        m_callback();
    }
}

void ButtonControl::SetText(const std::wstring& text) {
    SetWindowTextW(m_hwnd, text.c_str());
}
