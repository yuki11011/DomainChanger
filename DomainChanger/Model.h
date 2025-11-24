#pragma once

#include <string>
#include <vector>
#include <functional>

#undef CopyFile

class Model {
public:
    using OnStateChangedCallback = std::function<void(const std::wstring&)>;

    void SubscribeFilePath(OnStateChangedCallback callback) { m_onFilePathChanged = callback; }
    void SubscribeTargetText(OnStateChangedCallback callback) { m_onTargetTextChanged = callback; }
    void SubscribeReplacementText(OnStateChangedCallback callback) { m_onReplacementTextChanged = callback; }
    void SubscribeMessageLines(OnStateChangedCallback callback) { m_onMessageAppended = callback; }

    void SetFilePath(const std::wstring& path) {
        if (m_filePath != path) {
            m_filePath = std::move(path);
            if (m_onFilePathChanged) m_onFilePathChanged(m_filePath);
        }
    }
    void SetTargetText(const std::wstring& text) {
        if (m_targetText != text) {
            m_targetText = std::move(text);
            if (m_onTargetTextChanged) m_onTargetTextChanged(text);
        }
    }
    void SetReplacementText(const std::wstring& text) {
        if (m_replacementText != text) {
            m_replacementText = std::move(text);
            if (m_onReplacementTextChanged) m_onReplacementTextChanged(text);
        }
    }

    std::wstring GetFilePath() const { return m_filePath; };
    std::wstring GetTargetText() const { return m_targetText; };
    std::wstring GetReplacementText() const { return m_replacementText; };

    std::wstring GetFileNameFromPath(const std::wstring& path) const;
    std::vector<std::wstring> GetFileContent() const;
    int GetFileContentSize() const;

    void AddMessageToLines(const std::wstring& message);

    bool LoadFile();
    bool CopyFile(const std::wstring& srcPath, const std::wstring& destPath);
    bool OverwriteFile();
    bool CreateDirectoryIfNotExists(const std::wstring& dirPath);

    int ReplaceInFile(const std::wstring& target, const std::wstring& replacement);

private:
    std::wstring m_filePath;
    std::wstring m_targetText;
    std::wstring m_replacementText;
    std::wstring m_messageLines;
    std::vector<std::wstring> m_fileContent;

    OnStateChangedCallback m_onFilePathChanged;
    OnStateChangedCallback m_onTargetTextChanged;
    OnStateChangedCallback m_onReplacementTextChanged;
    OnStateChangedCallback m_onMessageAppended;
};