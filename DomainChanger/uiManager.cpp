#include "uiManager.h"

void UIManager::CreateControls(HWND hwnd, HINSTANCE hInstance) {
    HWND filePathLabel = CreateWindowEx(
        0, L"STATIC", L"対象ファイルのパス：",
        WS_CHILD | WS_VISIBLE,
        10, 10, 250, 24,
        hwnd, NULL, hInstance, NULL
    );
    m_filePathEdit = CreateWindow(
        L"EDIT", L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
        10, 40, 250, 24,
        hwnd, (HMENU)GetWindowID(), hInstance, NULL);
    m_browseButton = CreateWindowEx(
        0, L"BUTTON", L"参照…",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        270, 40, 80, 24,
        hwnd, (HMENU)(GetWindowID()), hInstance, NULL);
    HWND sourceLabel = CreateWindowEx(
        0, L"STATIC", L"置換する対象文字列：",
        WS_CHILD | WS_VISIBLE,
        10, 70, 250, 24,
        hwnd, NULL, hInstance, NULL
    );
    m_targetEdit = CreateWindow(
        L"EDIT", L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        10, 100, 250, 24,
        hwnd, (HMENU)GetWindowID(), hInstance, NULL);
    HWND destLabel = CreateWindowEx(
        0, L"STATIC", L"変更後の文字列：",
        WS_CHILD | WS_VISIBLE,
        10, 130, 250, 24,
        hwnd, NULL, hInstance, NULL
    );
    m_replacementEdit = CreateWindow(
        L"EDIT", L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        10, 160, 250, 24,
        hwnd, (HMENU)(GetWindowID()), hInstance, NULL);
    m_executeButton = CreateWindowEx(
        0, L"BUTTON", L"開始",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        10, 200, 100, 30,
        hwnd, (HMENU)GetWindowID(), hInstance, NULL);
}

wchar_t* UIManager::OpenFilePicker(HWND hwnd) {
    IFileOpenDialog* pFileOpen;
    wchar_t* filePath = nullptr;

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

                filePath = pszFilePath;
                pItem->Release();
            }
        }
        pFileOpen->Release();
    }
    return filePath;
}

void UIManager::SetFilePathText(const wchar_t* path) {
    int res = SetWindowTextW(m_filePathEdit, path);
}

const wchar_t* UIManager::GetFilePathText() {
    static wchar_t buffer[MAX_PATH];
    GetWindowTextW(m_filePathEdit, buffer, MAX_PATH);
    return buffer;
}

int UIManager::GetWindowID() {
    return m_windowID++;
}