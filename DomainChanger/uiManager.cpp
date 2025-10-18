#include "uiManager.h"

#define IDC_EDIT 100

void UIManager::CreateControls(HWND hwnd, HINSTANCE hInstance) {
    HWND filePathLabel = CreateWindowEx(
        0, L"STATIC", L"対象ファイルのパス：",
        WS_CHILD | WS_VISIBLE,
        10, 10, 250, 24,
        hwnd, NULL, hInstance, NULL
    );
    m_filePathEdit = CreateWindow(
        L"EDIT", L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        10, 40, 250, 24,
        hwnd, (HMENU)IDC_EDIT, hInstance, NULL);
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
        hwnd, (HMENU)IDC_EDIT, hInstance, NULL);
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
        hwnd, (HMENU)(IDC_EDIT + 1), hInstance, NULL);
    m_executeButton = CreateWindowEx(
        0, L"BUTTON", L"開始",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        10, 200, 100, 30,
        hwnd, (HMENU)(IDC_EDIT + 2), hInstance, NULL);
}

void UIManager::OpenFilePicker(HWND hwnd) {
    IFileOpenDialog* pFileOpen = nullptr;
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

    hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_PPV_ARGS(&pFileOpen));

    hr = pFileOpen->Show(hwnd);
}
