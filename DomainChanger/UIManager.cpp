#include "uiManager.h"

#include <Windows.h>
#include <shobjidl.h>
#include <tchar.h>
#include <memory>
#include "EditControl.h"
#include "ButtonControl.h"
#include "StaticControl.h"

struct UIManager::UIManagerImpl {
    std::unique_ptr<StaticControl> m_titleLabel;
    std::unique_ptr<StaticControl> m_filePathLabel;
    std::unique_ptr<EditControl> m_filePathEdit;
    std::unique_ptr<ButtonControl> m_browseButton;
    std::unique_ptr<StaticControl> m_targetLabel;
    std::unique_ptr<EditControl> m_targetEdit;
    std::unique_ptr<StaticControl> m_replacementLabel;
    std::unique_ptr<EditControl> m_replacementEdit;
    std::unique_ptr<ButtonControl> m_executeButton;
    std::unique_ptr<EditControl> m_messageLines;
};

UIManager::UIManager() {
    m_pImpl = new UIManagerImpl();

    m_pImpl->m_filePathEdit = std::make_unique<EditControl>(IDC_FILEPATH_EDIT);
    m_pImpl->m_filePathLabel = std::make_unique<StaticControl>();
    m_pImpl->m_targetLabel = std::make_unique<StaticControl>();
    m_pImpl->m_browseButton = std::make_unique<ButtonControl>(IDC_BROWSE_BUTTON);
    m_pImpl->m_replacementLabel = std::make_unique<StaticControl>();
    m_pImpl->m_targetEdit = std::make_unique<EditControl>(IDC_TARGET_EDIT);
    m_pImpl->m_titleLabel = std::make_unique<StaticControl>();
    m_pImpl->m_replacementEdit = std::make_unique<EditControl>(IDC_REPLACEMENT_EDIT);
    m_pImpl->m_executeButton = std::make_unique<ButtonControl>(IDC_EXECUTE_BUTTON);
    m_pImpl->m_messageLines = std::make_unique<EditControl>();
}

UIManager::~UIManager() {
    delete m_pImpl;
}

void UIManager::CreateControls(HWND hwnd, HINSTANCE hInstance) {
    m_pImpl->m_titleLabel->Create(hwnd, hInstance, L"Domain Changer v.1.0", 10, 10, 250, 24);
    m_pImpl->m_filePathLabel->Create(hwnd, hInstance, L"対象ファイルのパス：", 10, 40, 250, 24);
    m_pImpl->m_filePathEdit->Create(hwnd, hInstance, L"", 10, 70, 250, 24);
    m_pImpl->m_browseButton->Create(hwnd, hInstance, L"参照…", 270, 70, 80, 24);
    m_pImpl->m_targetLabel->Create(hwnd, hInstance, L"置換する対象文字列：", 10, 100, 250, 24);
    m_pImpl->m_targetEdit->Create(hwnd, hInstance, L"", 10, 130, 250, 24);
    m_pImpl->m_replacementLabel->Create(hwnd, hInstance, L"変更後の文字列：", 10, 160, 250, 24);
    m_pImpl->m_replacementEdit->Create(hwnd, hInstance, L"", 10, 190, 250, 24);
    m_pImpl->m_executeButton->Create(hwnd, hInstance, L"開始", 10, 230, 100, 30);
    m_pImpl->m_messageLines->Create(hwnd, hInstance, L"", 380, 70, 880, 600, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY);
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

void UIManager::SetFilePathText(const std::wstring& path) {
    m_pImpl->m_filePathEdit->SetText(path);
}

void UIManager::SetTargetText(const std::wstring& path) {
    m_pImpl->m_targetEdit->SetText(path);
}

void UIManager::SetReplacementText(const std::wstring& path) {
    m_pImpl->m_replacementEdit->SetText(path);
}

void UIManager::SetMessagesText(const std::wstring& text) {
    m_pImpl->m_messageLines->SetText(text);
}

void UIManager::AddMessageToLines(const std::wstring& message) {
    m_pImpl->m_messageLines->AddLine(message);
}

std::wstring UIManager::GetFilePathText() const {
    return m_pImpl->m_filePathEdit->GetText();
}

std::wstring UIManager::GetTargetText() const {
    return m_pImpl->m_targetEdit->GetText();
}

std::wstring UIManager::GetReplacementText() const {
    return m_pImpl->m_replacementEdit->GetText();
}

std::wstring UIManager::GetMessagesText() const {
    return m_pImpl->m_messageLines->GetText();
}
