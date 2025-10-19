#include "controller.h"

void Controller::SetUIManager(UIManager* ui) {
    m_ui = ui;
}

void Controller::SetModel(Model* model) {
    m_model = model;
}

void Controller::OnBrowseButtonClicked(HWND hwnd) {
    std::wstring filePath = m_ui->OpenFilePicker(hwnd);
    if (!filePath.empty()) {
        m_ui->SetFilePathText(filePath);
        m_model->SetFilePath(filePath);
    }
}

void Controller::OnExecuteButtonClicked(HWND hwnd) {
    if (m_model->LoadFile()) {
        m_ui->AddMessageToLines(L"ファイルの読み込みに成功しました");
        m_ui->AddMessageToLines(L"ファイルの内容：");
        m_ui->AddMessageToLines(m_model->GetFileContent());
    } else {
        m_ui->AddMessageToLines(L"ファイルの読み込みに失敗しました");
    }
}
