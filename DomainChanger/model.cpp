#include "model.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <locale>
#include <codecvt>
#include <sstream>

void Model::SetFilePath(std::wstring&& path) {
    m_filePath = std::move(path);
}

std::wstring Model::GetFilePath() const {
    return m_filePath;
}

std::vector<std::wstring> Model::GetFileContent() const {
    return m_fileContent;
}

int Model::GetFileContentSize() const {
    int size = 0;
    for (const auto& line : m_fileContent) {
        size += static_cast<int>(line.length());
    }
    return size;
}

bool Model::LoadFile() {
    m_fileContent.clear();

    std::ifstream file(m_filePath, std::ios::binary);
    if (!file.is_open()) {
        std::wcerr << L"Failed to open file: " << m_filePath << std::endl;
        return false;
    }

    std::string utf8Data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring content = converter.from_bytes(utf8Data);

    std::wstringstream ss(content);
    std::wstring line;
    while (std::getline(ss, line)) {
        m_fileContent.push_back(line);
    }

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
