#pragma once

struct HWND__;
typedef struct HWND__* HWND;

class UIManager;
class Model;

#include <iostream>

class Controller {
public:
    Controller(UIManager* ui, Model* model);

    void OnBrowseButtonClicked(HWND hwnd);
    void OnExecuteButtonClicked(HWND hwnd);
    void OnFilePathChanged();
    std::wstring GetDateString();

private:
    UIManager* m_ui;
    Model* m_model;
};