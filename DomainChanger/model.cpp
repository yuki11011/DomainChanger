#include "model.h"
#include <iostream>
#include <cstring>
#include <fstream>

void Model::SetFilePath(std::wstring path) {
    m_filePath = std::move(path);
}

std::wstring Model::GetFilePath() const {
    return m_filePath;
}

std::wstring Model::GetFileContent() const {
    return m_fileContent;
}

bool Model::LoadFile() {
    m_fileContent.clear();
        std::wifstream file(m_filePath);
    if (!file) {
        return false;
    }

    std::wstring line;
    while (std::getline(file, line)) {
        m_fileContent += line + L"\n";
    }

    file.close();
    return true;
}
