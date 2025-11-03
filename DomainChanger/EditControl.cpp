#include "EditControl.h"

bool EditControl::Create(HWND hParentWindow, HINSTANCE hInstance, const std::wstring initialText, int x, int y, int width, int height, DWORD style) {
    m_baseRect = { x, y, x + width, y + height };
    HWND hwnd = CreateWindowEx(
        0, L"EDIT", initialText.c_str(),
        style,
        0, 0, 0, 0,
        hParentWindow, (HMENU)m_id, hInstance, NULL);
    if (!hwnd) {
        return false;
    }
    m_hwnd = hwnd;
    return true;
}

std::wstring EditControl::GetText() const {
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

void EditControl::AddLine(const std::wstring& message) {
    std::wstring toAppend = message + L"\r\n";

    int currentLen = GetWindowTextLengthW(m_hwnd);
    long currentLimit = SendMessageW(m_hwnd, EM_GETLIMITTEXT, 0, 0);

    if (currentLen + toAppend.length() + 1 > currentLimit) {
        this->SetControlTextLimit(m_hwnd, static_cast<int>(currentLen + toAppend.length()) + 1024);
    }

    // Get current length and set selection to end
    int len = GetWindowTextLengthW(m_hwnd);
    SendMessageW(m_hwnd, EM_SETSEL, (WPARAM)len, (LPARAM)len);
    // Replace selection (empty) with new text
    SendMessageW(m_hwnd, EM_REPLACESEL, FALSE, (LPARAM)toAppend.c_str());
    // Ensure caret/scroll follows appended text
    SendMessageW(m_hwnd, EM_SCROLLCARET, 0, 0);
}

void EditControl::SetControlTextLimit(HWND hwnd, int limit) const {
    if (hwnd) SendMessageW(hwnd, EM_SETLIMITTEXT, (WPARAM)limit, 0);
}
