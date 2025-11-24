#include "Controller.h"
#include "EditControl.h"
#include "MessageLineControl.h"
#include "ButtonControl.h"
#include "StaticControl.h"
#include "UIManager.h"
#include "Model.h"
#include <time.h>

#undef CopyFile

Controller::Controller(UIManager* ui, Model* model)
    : m_ui(ui),
    m_model(model) {
}

void Controller::InitializeUI() {
    m_ui->AddControl<StaticControl>(10, 10, 250, 24, L"Domain Changer v.2.1");
    m_ui->AddControl<StaticControl>(10, 40, 250, 24, L"対象ファイルのパス");

    auto* pathEdit = m_ui->AddControl<EditControl>(10, 70, 250, 24, m_model->GetFilePath());
    m_model->SubscribeFilePath([pathEdit](const std::wstring& newVal) {
        if (pathEdit->GetText() != newVal) {
            pathEdit->SetText(newVal);
        }
        });
    pathEdit->SetOnValueChanged([this](const std::wstring& val) {
        m_model->SetFilePath(std::wstring(val));
        });

    auto* browseButton = m_ui->AddControl<ButtonControl>(270, 70, 80, 24, L"参照...");
    browseButton->SetOnClick([this]() {
        std::wstring path = m_ui->OpenFilePicker(nullptr);
        if (!path.empty()) {
            m_model->SetFilePath(std::move(path));
        }
        });

    m_ui->AddControl<StaticControl>(10, 100, 250, 24, L"置換する対象文字列：");
    auto* targetEdit = m_ui->AddControl<EditControl>(10, 130, 250, 24, m_model->GetTargetText());
    m_model->SubscribeTargetText([targetEdit](const std::wstring& newVal) {
        if (targetEdit->GetText() != newVal) {
            targetEdit->SetText(newVal);
        }
        });
    targetEdit->SetOnValueChanged([this](const std::wstring& val) {
        m_model->SetTargetText(std::wstring(val));
        });

    m_ui->AddControl<StaticControl>(10, 160, 250, 24, L"変更後の文字列：");
    auto* replacementEdit = m_ui->AddControl<EditControl>(10, 190, 250, 24, m_model->GetReplacementText());
    m_model->SubscribeReplacementText([replacementEdit](const std::wstring& newVal) {
        if (replacementEdit->GetText() != newVal) {
            replacementEdit->SetText(newVal);
        }
        });
    replacementEdit->SetOnValueChanged([this](const std::wstring& val) {
        m_model->SetReplacementText(std::wstring(val));
        });

    auto* executeButton = m_ui->AddControl<ButtonControl>(10, 230, 100, 30, L"開始");
    executeButton->SetOnClick([this]() {
        auto res = m_ui->ShowConfirmationDialog();
        if (!res) {
            m_model->AddMessageToLines(L"*処理がキャンセルされました");
            return;
        }

        if (m_model->LoadFile()) {
            m_model->AddMessageToLines(L"*ファイルの読み込みに成功しました");

            std::wstring backupDir = L"backups";
            if (!m_model->CreateDirectoryIfNotExists(backupDir)) {
                m_model->AddMessageToLines(L"*バックアップディレクトリの作成に失敗しました");
                m_model->AddMessageToLines(L"*処理を中止します");
                return;
            }

            std::wstring date = GetDateString();
            std::wstring fileName = m_model->GetFileNameFromPath(m_model->GetFilePath());
            std::wstring backupPath = backupDir + L"\\" + fileName + L"_" + date + L".bak";

            bool res = m_model->CopyFile(m_model->GetFilePath(), backupPath);
            if (!res) {
                m_model->AddMessageToLines(L"*バックアップファイルの作成に失敗しました");
                m_model->AddMessageToLines(L"*処理を中止します");
                return;
            } else {
                m_model->AddMessageToLines(L"*バックアップファイルを作成しました：" + backupPath);
            }

            m_model->AddMessageToLines(L"*置換を実行します");
            m_model->AddMessageToLines(L"*置換対象：" + m_model->GetTargetText());
            m_model->AddMessageToLines(L"*置換後：" + m_model->GetReplacementText());
            int replacementsCount = m_model->ReplaceInFile(m_model->GetTargetText(), m_model->GetReplacementText());

            m_model->AddMessageToLines(L"*置換処理が完了しました");
            m_model->AddMessageToLines(L"* 置換した文字列の個数：" + std::to_wstring(replacementsCount));
            m_model->AddMessageToLines(L"*ファイルを上書きします。");

            if (!m_model->OverwriteFile()) {
                m_model->AddMessageToLines(L"*ファイルの上書きに失敗しました");
                m_model->AddMessageToLines(L"*ファイルが使用中か、書き込み権限がない可能性があります");
                return;
            }
            m_model->AddMessageToLines(L"*ファイルの上書きに成功しました");
        } else {
            m_model->AddMessageToLines(L"*ファイルの読み込みに失敗しました");
            m_model->AddMessageToLines(L"*指定されたパスを確認してください");
        }
        });
    auto* messageLines = m_ui->AddControl<MessageLineControl>(380, 70, 880, 600, L"");
    m_model->SubscribeMessageLines([messageLines](const std::wstring& newVal) {
            messageLines->AddMessageToLines(newVal);
        });
}

std::wstring Controller::GetDateString() {
    time_t now = time(nullptr);
    struct tm localTime;
    localtime_s(&localTime, &now);
    wchar_t buffer[32];
    wcsftime(buffer, sizeof(buffer) / sizeof(wchar_t), L"%Y%m%d%H%M%S", &localTime);
    return std::wstring(buffer);
}
