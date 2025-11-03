#pragma once

#include <string>
#include <vector>

class Model {
public:
    void SetFilePath(std::wstring&& path);

    std::wstring GetFilePath() const;
    std::wstring GetFileNameFromPath(const std::wstring& path) const;
    std::vector<std::wstring> GetFileContent() const;
    int GetFileContentSize() const;

    bool LoadFile();
    bool CopyFile(const std::wstring& srcPath, const std::wstring& destPath);
    bool OverwriteFile();
    bool CreateDirectoryIfNotExists(const std::wstring& dirPath);

    int ReplaceInFile(const std::wstring& target, const std::wstring& replacement);

private:
    std::wstring m_filePath;
    std::vector<std::wstring> m_fileContent;
};