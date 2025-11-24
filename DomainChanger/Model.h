#pragma once

#include <string>
#include <vector>

#undef CopyFile

class Model {
public:
    void SetFilePath(std::wstring&& path) { m_filePath = std::move(path); };
    void SetTargetText(std::wstring&& text) { m_targetText = std::move(text); };
    void SetReplacementText(std::wstring&& text) { m_replacementText = std::move(text); };

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
};