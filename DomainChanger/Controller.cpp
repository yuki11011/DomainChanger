#include "controller.h"
#include "uiManager.h"
#include "model.h"
#include <time.h>

Controller::Controller(UIManager* ui, Model* model)
    : m_ui(ui),
    m_model(model) {
}

void Controller::OnBrowseButtonClicked(HWND hwnd) {
    std::wstring filePath = m_ui->OpenFilePicker(hwnd);
    if (!filePath.empty()) {
        m_ui->SetFilePathText(filePath);
        m_model->SetFilePath(std::move(filePath));
    }
}

void Controller::OnExecuteButtonClicked(HWND hwnd) {
    if (!m_ui->ShowConfirmationDialog()) {
        m_ui->AddMessageToLines(L"*処理がキャンセルされました");
        return;
    }
    if (m_model->LoadFile()) {
        m_ui->AddMessageToLines(L"*ファイルの読み込みに成功しました");
        //m_ui->AddMessageToLines(L"*ファイルの内容：");
        //std::wstring fileContent;
        //for (const auto& line : m_model->GetFileContent()) {
        //    fileContent += line + L"\r\n";
        //}
        //m_ui->AddMessageToLines(fileContent);
        
        // backupsディレクトリを作成
        std::wstring backupDir = L"backups";
        if (!m_model->CreateDirectoryIfNotExists(backupDir)) {
            m_ui->AddMessageToLines(L"*バックアップディレクトリの作成に失敗しました");
            m_ui->AddMessageToLines(L"*処理を中止します");
            return;
        }
        
        std::wstring date = GetDateString();
        std::wstring fileName = m_model->GetFileNameFromPath(m_model->GetFilePath());
        std::wstring backupPath = backupDir + L"\\" + fileName + L"_" + date + L".bak";
        
        bool res = m_model->CopyFile(m_model->GetFilePath(), backupPath);
        if (!res) {
            m_ui->AddMessageToLines(L"*バックアップファイルの作成に失敗しました");
            m_ui->AddMessageToLines(L"*処理を中止します");
            return;
        } else {
            m_ui->AddMessageToLines(L"*バックアップファイルを作成しました：" + backupPath);
        }
        m_ui->AddMessageToLines(L"*置換を実行します");
        m_ui->AddMessageToLines(L"*置換対象：" + m_ui->GetTargetText());
        m_ui->AddMessageToLines(L"*置換後：" + m_ui->GetReplacementText());
        int replacementsCount = m_model->ReplaceInFile(m_ui->GetTargetText(), m_ui->GetReplacementText());
        //m_ui->AddMessageToLines(L"*置換後の内容：");
        //fileContent.clear();
        //for (const auto& line : m_model->GetFileContent()) {
        //    fileContent += line + L"\r\n";
        //}
        //m_ui->AddMessageToLines(fileContent);
        m_ui->AddMessageToLines(L"*置換処理が完了しました");
        m_ui->AddMessageToLines(L"* 置換した文字列の個数：" + std::to_wstring(replacementsCount));
        m_ui->AddMessageToLines(L"*ファイルを上書きします。");

        if (!m_model->OverwriteFile()) {
            m_ui->AddMessageToLines(L"*ファイルの上書きに失敗しました");
            m_ui->AddMessageToLines(L"*ファイルが使用中か、書き込み権限がない可能性があります");
            return;
        }
        m_ui->AddMessageToLines(L"*ファイルの上書きに成功しました");
    } else {
        m_ui->AddMessageToLines(L"*ファイルの読み込みに失敗しました");
        m_ui->AddMessageToLines(L"*指定されたパスを確認してください");
    }
}

void Controller::OnFilePathChanged() {
    std::wstring text = m_ui->GetFilePathText();
    m_model->SetFilePath(std::move(text));
}

std::wstring Controller::GetDateString() {
    time_t now = time(nullptr);
    struct tm localTime;
    localtime_s(&localTime, &now);
    wchar_t buffer[32];
    wcsftime(buffer, sizeof(buffer) / sizeof(wchar_t), L"%Y%m%d%H%M%S", &localTime);
    return std::wstring(buffer);
}
