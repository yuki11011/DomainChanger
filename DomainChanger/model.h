#pragma once

#include <string>
#include <vector>

class Model {
public:
    void SetFilePath(std::wstring path);

    std::wstring GetFilePath() const;
    std::vector<std::wstring> GetFileContent() const;
    bool LoadFile();
private:
    std::wstring m_filePath;
    std::vector<std::wstring> m_fileContent;
};