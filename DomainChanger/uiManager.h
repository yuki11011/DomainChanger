#pragma once

#include <Windows.h>
#include <string>
#include <shobjidl.h>
#include <tchar.h>

class UIManager {
public:
    void CreateControls(HWND hwnd, HINSTANCE hInstance);
    void OpenFilePicker(HWND hwnd);
    std::wstring GetTargetText();
    std::wstring GetReplacementText();

private:
    HWND m_filePathEdit;
    HWND m_targetEdit;
    HWND m_replacementEdit;
    HWND m_executeButton;
};