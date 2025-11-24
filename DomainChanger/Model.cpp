#include "Model.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <locale>
#include <codecvt>
#include <sstream>
#include <Windows.h>
#undef CopyFile  // Windows.h のマクロを無効化

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

void Model::AddMessageToLines(const std::wstring& message) {
    std::wstring toAppend = message + L"\r\n";
    m_messageLines.append(toAppend);
    m_onMessageAppended(message);
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

bool Model::CopyFile(const std::wstring& srcPath, const std::wstring& dstPath) {
    std::ifstream src(srcPath, std::ios::binary);  // バイナリモードで開く
    if (!src) return false;

    std::ofstream dst(dstPath, std::ios::binary | std::ios::trunc);
    if (!dst) return false;

    dst << src.rdbuf(); // ストリームバッファをそのままコピー

    return true;
}

bool Model::OverwriteFile() {
    std::wstringstream ss;
    for (const auto& line : m_fileContent) {
        ss << line << L"\n";
    }

    // UTF-16（wchar_t）→ UTF-8変換
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::string utf8Text = converter.to_bytes(ss.str());

    // wstringパスを確実に扱うため、_wfopenを使用
    FILE* file = nullptr;
    errno_t err = _wfopen_s(&file, m_filePath.c_str(), L"wb");
    if (err != 0 || file == nullptr) {
        return false;
    }

    size_t written = fwrite(utf8Text.data(), 1, utf8Text.size(), file);
    fclose(file);

    return written == utf8Text.size();
}

int Model::ReplaceInFile(const std::wstring& target, const std::wstring& replacement) {
    int replacementsCount = 0;
    if (target.empty()) return 0;
    for (auto& line : m_fileContent) {
        size_t pos = 0;
        while ((pos = line.find(target, pos)) != std::wstring::npos) {
            line.replace(pos, target.length(), replacement);
            pos += replacement.length();
            replacementsCount++;
        }
    }
    return replacementsCount;
}

std::wstring Model::GetFileNameFromPath(const std::wstring& path) const {
    size_t pos = path.find_last_of(L"\\/");
    if (pos != std::wstring::npos) {
        return path.substr(pos + 1);
    }
    return path;
}

bool Model::CreateDirectoryIfNotExists(const std::wstring& dirPath) {
    DWORD attributes = GetFileAttributesW(dirPath.c_str());
    
    // ディレクトリが既に存在する場合
    if (attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY)) {
        return true;
    }
    
    // ディレクトリを作成
    return CreateDirectoryW(dirPath.c_str(), NULL) != 0 || GetLastError() == ERROR_ALREADY_EXISTS;
}
