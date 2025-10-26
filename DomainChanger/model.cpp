#include "model.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <locale>
#include <codecvt>

void Model::SetFilePath(std::wstring path) {
    m_filePath = std::move(path);
}

std::wstring Model::GetFilePath() const {
    return m_filePath;
}

std::vector<std::wstring> Model::GetFileContent() const {
    return m_fileContent;
}

bool Model::LoadFile() {
    m_fileContent.clear();
        std::wifstream file(m_filePath);
    if (!file) {
        return false;
    }

    file.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));
    std::wstring line;
    while (std::getline(file, line)) {
        m_fileContent.push_back(line);
    }

    file.close();
    return true;
}

void Model::ReplaceInFile(const std::wstring& target, const std::wstring& replacement) {
    if (target.empty()) return;
    for (auto& line : m_fileContent) {
        size_t pos = 0;
        while ((pos = line.find(target, pos)) != std::wstring::npos) {
            line.replace(pos, target.length(), replacement);
            pos += replacement.length();
        }
    }
}
