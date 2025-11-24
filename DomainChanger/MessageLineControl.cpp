#include "MessageLineControl.h"

void MessageLineControl::AddMessageToLines(const std::wstring& message) {
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
