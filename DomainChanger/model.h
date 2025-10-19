#pragma once

#include <string>

class Model {
public:
    void SetFilePath(std::wstring path);

    std::wstring GetFilePath() const;
    std::wstring GetFileContent() const;
    bool LoadFile();
private:
    std::wstring m_filePath;
    std::wstring m_fileContent;
};