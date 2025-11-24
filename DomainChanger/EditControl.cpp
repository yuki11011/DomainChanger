#include "EditControl.h"

bool EditControl::Create(HWND hParentWindow, HINSTANCE hInstance) {
    m_hwnd = CreateWindowExW(0, L"EDIT", m_params.text.c_str(), m_params.style,
        m_params.x, m_params.y, m_params.width, m_params.height,
        hParentWindow, (HMENU)(intptr_t)m_id, hInstance, nullptr);
    return m_hwnd != nullptr;
}

void EditControl::OnCommand(WORD notificationCode) {
    if (notificationCode == EN_CHANGE && m_callback) {
        m_callback(GetText());
    }
}

std::wstring EditControl::GetText() const {
    if (m_hwnd == nullptr) return L"";
    int len = GetWindowTextLengthW(m_hwnd);
    if (len <= 0) return L"";
    std::wstring buffer;
    buffer.resize(len + 1);
    GetWindowTextW(m_hwnd, &buffer[0], len + 1);
    buffer.resize(len);
    return buffer;
}

void EditControl::SetText(const std::wstring& text) {
    long currentLimit = SendMessageW(m_hwnd, EM_GETLIMITTEXT, 0, 0);
    if (text.length() + 1 > currentLimit) {
        SetControlTextLimit(m_hwnd, static_cast<int>(text.length()) + 1024);
    }
    SetWindowTextW(m_hwnd, text.c_str());
}

void EditControl::SetControlTextLimit(HWND hwnd, int limit) const {
    if (hwnd) SendMessageW(hwnd, EM_SETLIMITTEXT, (WPARAM)limit, 0);
}
