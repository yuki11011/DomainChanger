#include "UIManager.h"

#include <Windows.h>
#include <shobjidl.h>
#include <tchar.h>
#include <memory>
#include "EditControl.h"
#include "ButtonControl.h"
#include "StaticControl.h"

int Scale(int val, int dpi) {
    return MulDiv(val, dpi, 120); // 120 DPI (125%) を基準にする
}

void UIManager::CreateControls(HWND hwnd, HINSTANCE hInstance) {
    for (auto& ctrl : m_controls) {
        if (ctrl->Create(hwnd, hInstance)) {
            m_controlMap[ctrl->GetId()] = ctrl.get();
        }
    }
}

bool UIManager::HandleCommand(WPARAM wParam) {
    int id = LOWORD(wParam);
    WORD code = HIWORD(wParam);

    auto it = m_controlMap.find(id);
    if (it != m_controlMap.end()) {
        it->second->OnCommand(code);
        return true;
    }
    return false;
}

void UIManager::UpdateLayoutAndFonts(int newDpi) {
    if (m_hFont) {
        DeleteObject(m_hFont);
        m_hFont = nullptr;
    }

    LOGFONTW lf = {};
    lf.lfHeight = -UIControl::Scale(16, newDpi);
    lf.lfWeight = FW_NORMAL;
    wcscpy_s(lf.lfFaceName, L"Yu Gothic UI");
    m_hFont = CreateFontIndirectW(&lf);

    for (auto& ctrl : m_controls) {
        ctrl->UpdateLayout(newDpi, m_hFont);
    }
}

bool UIManager::ShowConfirmationDialog() {
    int id = MessageBoxW(NULL, L"実行前に必ずバックアップを取ってください。\nこのプログラムの制作者はこのプログラムの使用によって生じた一切の損害に対して責任を負いません。\n処理を実行しますか？", L"確認", MB_OKCANCEL | MB_ICONQUESTION);
    return id == IDOK;
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
