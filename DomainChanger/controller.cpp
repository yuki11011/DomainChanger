#include "controller.h"
#include "uiManager.h"
#include "model.h"

Controller::Controller(UIManager* ui, Model* model)
    : m_ui(ui),
    m_model(model) {
}

void Controller::SetNewTextLength(HWND hwnd) {
    int overflowSize = m_model->GetFileContentSize() - m_ui->GetTargetText().length();
    int newLimit = overflowSize + m_ui->GetReplacementText().length() + 1024;

    m_ui->SetControlTextLimit(hwnd, newLimit);

    m_ui->AddMessageToLines(L"（通知）テキスト長が最大に達したため、制限を " + std::to_wstring(newLimit) + L" に変更しました。");
}

void Controller::OnBrowseButtonClicked(HWND hwnd) {
    std::wstring filePath = m_ui->OpenFilePicker(hwnd);
    if (!filePath.empty()) {
        m_ui->SetFilePathText(filePath);
        m_model->SetFilePath(std::move(filePath));
    }
}

void Controller::OnExecuteButtonClicked(HWND hwnd) {
    if (m_model->LoadFile()) {
        m_ui->AddMessageToLines(L"ファイルの読み込みに成功しました");
        m_ui->AddMessageToLines(L"ファイルの内容：");
        std::wstring fileContent;
        for (const auto& line : m_model->GetFileContent()) {
            fileContent += line + L"\r\n";
        }
        m_ui->AddMessageToLines(fileContent);
        m_ui->AddMessageToLines(L"置換を実行します");
        m_model->ReplaceInFile(m_ui->GetTargetText(), m_ui->GetReplacementText());
        m_ui->AddMessageToLines(L"置換後の内容：");
        fileContent.clear();
        for (const auto& line : m_model->GetFileContent()) {
            fileContent += line + L"\r\n";
        }
        m_ui->AddMessageToLines(fileContent);
    } else {
        m_ui->AddMessageToLines(L"ファイルの読み込みに失敗しました");
    }
}

void Controller::OnFilePathChanged() {
    std::wstring text = m_ui->GetFilePathText();
    m_model->SetFilePath(std::move(text));
}
