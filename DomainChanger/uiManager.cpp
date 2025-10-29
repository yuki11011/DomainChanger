#include "uiManager.h"

#include <Windows.h>
#include <shobjidl.h>
#include <tchar.h>

struct UIManager ::UIManagerImpl {
    HWND m_filePathEdit;
    HWND m_browseButton;
    HWND m_targetEdit;
    HWND m_replacementEdit;
    HWND m_executeButton;
    HWND m_messageLines;
};

UIManager::UIManager() {
    m_pImpl = new UIManagerImpl();
}

UIManager::~UIManager() {
    delete m_pImpl;
}

void UIManager::CreateControls(HWND hwnd, HINSTANCE hInstance) {
    HWND filePathLabel = CreateWindowEx(
        0, L"STATIC", L"対象ファイルのパス：",
        WS_CHILD | WS_VISIBLE,
        10, 10, 250, 24,
        hwnd, NULL, hInstance, NULL
    );
    m_pImpl->m_filePathEdit = CreateWindow(
        L"EDIT", L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
        10, 40, 250, 24,
        hwnd, (HMENU)IDC_FILEPATH_EDIT, hInstance, NULL);
    m_pImpl->m_browseButton = CreateWindowEx(
        0, L"BUTTON", L"参照…",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        270, 40, 80, 24,
        hwnd, (HMENU)IDC_BROWSE_BUTTON, hInstance, NULL);
    HWND sourceLabel = CreateWindowEx(
        0, L"STATIC", L"置換する対象文字列：",
        WS_CHILD | WS_VISIBLE,
        10, 70, 250, 24,
        hwnd, NULL, hInstance, NULL
    );
    m_pImpl->m_targetEdit = CreateWindow(
        L"EDIT", L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        10, 100, 250, 24,
        hwnd, (HMENU)IDC_TARGET_EDIT, hInstance, NULL);
    HWND destLabel = CreateWindowEx(
        0, L"STATIC", L"変更後の文字列：",
        WS_CHILD | WS_VISIBLE,
        10, 130, 250, 24,
        hwnd, NULL, hInstance, NULL
    );
    m_pImpl->m_replacementEdit = CreateWindow(
        L"EDIT", L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        10, 160, 250, 24,
        hwnd, (HMENU)IDC_REPLACEMENT_EDIT, hInstance, NULL);
    m_pImpl->m_executeButton = CreateWindowEx(
        0, L"BUTTON", L"開始",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        10, 200, 100, 30,
        hwnd, (HMENU)IDC_EXECUTE_BUTTON, hInstance, NULL);
    m_pImpl->m_messageLines = CreateWindow(
        L"EDIT", L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
        380, 40, 880, 600,
        hwnd, NULL, hInstance, NULL);
}

std::wstring UIManager::OpenFilePicker(HWND hwnd) {
    IFileOpenDialog* pFileOpen;
    std::wstring filePath;

    // Create the FileOpenDialog object.
    HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
        IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

    if (SUCCEEDED(hr)) {
        // Show the Open dialog box.
        hr = pFileOpen->Show(NULL);

        // Get the file name from the dialog box.
        if (SUCCEEDED(hr)) {
            IShellItem* pItem;
            hr = pFileOpen->GetResult(&pItem);
            if (SUCCEEDED(hr)) {
                PWSTR pszFilePath;
                hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                filePath.assign(pszFilePath ? pszFilePath : L"");
                pItem->Release();
                CoTaskMemFree(pszFilePath);
            }
        }
        pFileOpen->Release();
    }
    return filePath;
}

void UIManager::SetFilePathText(const std::wstring& path) {
    int res = SetWindowTextW(m_pImpl->m_filePathEdit, path.c_str());
}

void UIManager::SetTargetText(const std::wstring& path) {
    int res = SetWindowTextW(m_pImpl->m_targetEdit, path.c_str());
}

void UIManager::SetReplacementText(const std::wstring& path) {
    int res = SetWindowTextW(m_pImpl->m_replacementEdit, path.c_str());
}

void UIManager::SetMessagesText(const std::wstring& text) {
    int res = SetWindowTextW(m_pImpl->m_messageLines, text.c_str());
}

void UIManager::AddMessageToLines(const std::wstring& message) {
    std::wstring toAppend = message + L"\r\n";
    // Get current length and set selection to end
    int len = GetWindowTextLengthW(m_pImpl->m_messageLines);
    SendMessageW(m_pImpl->m_messageLines, EM_SETSEL, (WPARAM)len, (LPARAM)len);
    // Replace selection (empty) with new text
    SendMessageW(m_pImpl->m_messageLines, EM_REPLACESEL, FALSE, (LPARAM)toAppend.c_str());
    // Ensure caret/scroll follows appended text
    SendMessageW(m_pImpl->m_messageLines, EM_SCROLLCARET, 0, 0);
}

std::wstring UIManager::GetFilePathText() const {
    int len = GetWindowTextLengthW(m_pImpl->m_filePathEdit);
    if (len <= 0) return L"";
    std::wstring buffer;
    buffer.resize(len + 1);
    GetWindowTextW(m_pImpl->m_filePathEdit, &buffer[0], len + 1);
    buffer.resize(len);
    return buffer;
}

std::wstring UIManager::GetTargetText() const {
    int len = GetWindowTextLengthW(m_pImpl->m_targetEdit);
    if (len <= 0) return L"";
    std::wstring buffer;
    buffer.resize(len + 1);
    GetWindowTextW(m_pImpl->m_targetEdit, &buffer[0], len + 1);
    buffer.resize(len);
    return buffer;
}

std::wstring UIManager::GetReplacementText() const {
    int len = GetWindowTextLengthW(m_pImpl->m_replacementEdit);
    if (len <= 0) return L"";
    std::wstring buffer;
    buffer.resize(len + 1);
    GetWindowTextW(m_pImpl->m_replacementEdit, &buffer[0], len + 1);
    buffer.resize(len);
    return buffer;
}

std::wstring UIManager::GetMessagesText() const {
    std::wstring buffer;
    int len = GetWindowTextLengthW(m_pImpl->m_messageLines);
    if (len <= 0) return L"";
    buffer.resize(len + 1);
    GetWindowTextW(m_pImpl->m_messageLines, &buffer[0], len + 1);
    buffer.resize(len);
    return buffer;
}
