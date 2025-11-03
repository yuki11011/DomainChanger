// Application.cpp
#include "Application.h"
#include <stdexcept> // エラーハンドリングのため

// Pimpl (実装クラス)
struct Application::ApplicationImpl {
    ComInitializer m_comInit; // COMの生存期間管理
    Model m_model;
    UIManager m_ui;
    Controller m_controller;
    Window m_window;

    // コンストラクタで依存関係を注入
    ApplicationImpl(HINSTANCE hInstance, int nCmdShow)
        : m_comInit(),
        m_model(),
        m_ui(),
        m_controller(&m_ui, &m_model), // ★依存注入（UIとModelのアドレスを渡す）
        m_window(hInstance, nCmdShow, L"Domain Changer v.1.0", &m_controller) { // ★依存注入（Controllerのアドレスを渡す）
        if (FAILED(m_comInit.GetHResult())) {
            throw std::runtime_error("COM initialization failed");
        }
    }
};

// --- Application クラスのメソッド ---

Application::Application(HINSTANCE hInstance, int nCmdShow) {
    m_pImpl = new ApplicationImpl(hInstance, nCmdShow);
}

Application::~Application() {
    delete m_pImpl;
};

int Application::Run() {
    if (!m_pImpl->m_window.Create(&m_pImpl->m_ui)) {
        MessageBoxW(nullptr, L"ウィンドウの作成に失敗しました！", L"エラー", MB_OK | MB_ICONERROR);
        return -1;
    }

    // 2. ウィンドウを表示
    m_pImpl->m_window.Show();

    // 3. メッセージループ
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return static_cast<int>(msg.wParam);
}