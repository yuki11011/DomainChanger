#pragma once

#include <string>
#include <vector>

#define DEFAULT_TEXT_LIMIT_LENGTH 32767

#define IDC_FILEPATH_EDIT 1001
#define IDC_BROWSE_BUTTON 1002
#define IDC_TARGET_EDIT 1003
#define IDC_REPLACEMENT_EDIT 1004
#define IDC_EXECUTE_BUTTON 1005

struct HWND__;
typedef struct HWND__* HWND;
struct HINSTANCE__;
typedef struct HINSTANCE__* HINSTANCE;
class UIControl;

class UIManager {
public:
    UIManager();
    ~UIManager();

    void CreateControls(HWND hwnd, HINSTANCE hInstance);
    void UpdateLayoutAndFonts(int newDpi);

    bool ShowConfirmationDialog();

    void SetFilePathText(const std::wstring& path);
    void SetTargetText(const std::wstring& path);
    void SetReplacementText(const std::wstring& path);
    void SetMessagesText(const std::wstring& text);
    void AddMessageToLines(const std::wstring& message);

    std::wstring GetFilePathText() const;
    std::wstring GetTargetText() const;
    std::wstring GetReplacementText() const;
    std::wstring GetMessagesText() const;

    std::wstring OpenFilePicker(HWND hwnd);

    UIManager(const UIManager&) = delete;
    UIManager& operator=(const UIManager&) = delete;
    UIManager(UIManager&&) = delete;
    UIManager& operator=(UIManager&&) = delete;

private:
    struct UIManagerImpl;
    UIManagerImpl* m_pImpl;
};
