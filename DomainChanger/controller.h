#pragma once

struct HWND__;
typedef struct HWND__* HWND;

class UIManager;
class Model;

class Controller {
public:
    Controller(UIManager* ui, Model* model);

    void SetNewTextLength(HWND hwnd);

    void OnBrowseButtonClicked(HWND hwnd);
    void OnExecuteButtonClicked(HWND hwnd);
    void OnFilePathChanged();

private:
    UIManager* m_ui;
    Model* m_model;
};