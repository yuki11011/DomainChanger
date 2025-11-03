// Application.h
#pragma once

#include <Windows.h>
#include <string>
#include "Model.h"
#include "UIManager.h"
#include "Controller.h"
#include "Window.h"

// RAII ラッパー (COMの初期化/後処理を自動化)
class ComInitializer {
public:
    ComInitializer() : m_hr(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE)) {}
    ~ComInitializer() { if (SUCCEEDED(m_hr)) CoUninitialize(); }
    HRESULT GetHResult() const { return m_hr; }
private:
    HRESULT m_hr;
};

class Application {
public:
    Application(HINSTANCE hInstance, int nCmdShow);
    ~Application(); // デストラクタ (Pimplのため .cpp で定義)

    // アプリケーションのメインループを実行
    int Run();

private:
    struct ApplicationImpl;
    ApplicationImpl* m_pImpl;
};