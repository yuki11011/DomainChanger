#pragma once

#include <Windows.h>
#include <string>
#include <shobjidl.h>
#include <tchar.h>

constexpr int IDC_EDIT = 100;

class UIManager {
public:
    void CreateControls(HWND hwnd, HINSTANCE hInstance);
    wchar_t* OpenFilePicker(HWND hwnd);
    std::wstring GetTargetText();
    std::wstring GetReplacementText();
    void SetFilePathText(const wchar_t* path);
    const wchar_t* GetFilePathText();

private:
    int GetWindowID();

    int m_windowID = IDC_EDIT;
    HWND m_filePathEdit;
    HWND m_browseButton;
    HWND m_targetEdit;
    HWND m_replacementEdit;
    HWND m_executeButton;
};