// main.cpp (変更後)
#include <Windows.h>
#include "Application.h"
#include <shellscalingapi.h>
#include <exception> // エラーハンドリングのため

#pragma comment(lib, "Shcore.lib")

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
    SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);

    try {
        Application app(hInstance, nCmdShow);
        return app.Run();
    } catch (const std::exception& e) {
        // 例外処理 (COM初期化失敗など)
        MessageBoxA(nullptr, e.what(), "Fatal Error", MB_OK | MB_ICONERROR);
        return -1;
    } catch (...) {
        MessageBoxW(nullptr, L"不明な例外が発生しました。", L"Fatal Error", MB_OK | MB_ICONERROR);
        return -1;
    }
}