#pragma once

#include "model.h"
#include "uiManager.h"

class Controller {
public:
    void SetUIManager(UIManager* ui);
    void SetModel(Model* model);

    void OnBrowseButtonClicked(HWND hwnd);
    void OnExecuteButtonClicked(HWND hwnd);
private:
    Model* m_model;
    UIManager* m_ui;
};