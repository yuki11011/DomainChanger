#pragma once

#include <string>
#include <vector>

class Model {
public:
    void SetFilePath(std::wstring path);

    std::wstring GetFilePath() const;
    std::vector<std::wstring> GetFileContent() const;

    bool LoadFile();

    void ReplaceInFile(const std::wstring& target, const std::wstring& replacement);

private:
    std::wstring m_filePath;
    std::vector<std::wstring> m_fileContent;
};