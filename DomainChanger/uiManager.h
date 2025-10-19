#pragma once

#include <Windows.h>
#include <string>
#include <shobjidl.h>
#include <tchar.h>

#define IDC_FILEPATH_EDIT 1001
#define IDC_BROWSE_BUTTON 1002
#define IDC_TARGET_EDIT 1003
#define IDC_REPLACEMENT_EDIT 1004
#define IDC_EXECUTE_BUTTON 1005

class UIManager {
public:
    void CreateControls(HWND hwnd, HINSTANCE hInstance);

    void SetFilePathText(const std::wstring path);
    void SetTargetText(const std::wstring path);
    void SetReplacementText(const std::wstring path);
    void SetMessagesText(const std::wstring text);
    void AddMessageToLines(const std::wstring message);

    std::wstring GetFilePathText() const;
    std::wstring GetTargetText() const;
    std::wstring GetReplacementText() const;
    std::wstring GetMessagesText() const;

    std::wstring OpenFilePicker(HWND hwnd);

private:
    HWND m_filePathEdit;
    HWND m_browseButton;
    HWND m_targetEdit;
    HWND m_replacementEdit;
    HWND m_executeButton;
    HWND m_messageLines;
};