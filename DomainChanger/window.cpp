#include "window.h"
#include <iostream>
#include <fstream>

#define IDC_EDIT 100

Window::Window(HINSTANCE hInstance, int nCmdShow, const std::wstring& windowTitle, int width, int height)
    : m_hInstance(hInstance),
    m_nCmdShow(nCmdShow),
    m_hWnd(nullptr),
    m_windowTitle(windowTitle),
    m_width(width),
    m_height(height) {
}

Window::~Window() {
}

bool Window::Create() {
    WNDCLASSEXW wc = {};
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = Window::StaticWindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = sizeof(Window*);
    wc.hInstance = m_hInstance;
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = L"DirectX12WindowClass";
    wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

    if (!RegisterClassExW(&wc)) {
        MessageBoxW(nullptr, L"ウィンドウクラスの登録に失敗しました！", L"エラー", MB_OK | MB_ICONERROR);
        return false;
    }

    // ウィンドウの作成
    RECT windowRect = { 0, 0, m_width, m_height };
    AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);
    m_hWnd = CreateWindowExW(
        0,
        wc.lpszClassName,
        m_windowTitle.c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        windowRect.right - windowRect.left,
        windowRect.bottom - windowRect.top,
        nullptr,
        nullptr,
        m_hInstance,
        this // ウィンドウのインスタンスを渡す
    );

    if (!m_hWnd) {
        MessageBoxW(nullptr, L"ウィンドウの作成に失敗しました！", L"エラー", MB_OK | MB_ICONERROR);
        return false;
    }

    return true;
}

void Window::Show() {
    if (m_hWnd) {
        ShowWindow(m_hWnd, m_nCmdShow);
        UpdateWindow(m_hWnd);
    }
}

HWND Window::GetHWND() const {
    return m_hWnd;
}

int Window::GetWidth() const {
    return m_width;
}

int Window::GetHeight() const {
    return m_height;
}

// 静的メソッドとしてウィンドウプロシージャを定義
LRESULT CALLBACK Window::StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    Window* pWindow = nullptr;

    if (uMsg == WM_NCCREATE) {
        CREATESTRUCTW* pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
        pWindow = static_cast<Window*>(pCreate->lpCreateParams);
        SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
        pWindow->m_hWnd = hwnd; // ウィンドウハンドルを保存
    } else {
        pWindow = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }
    if (pWindow) {
        return pWindow->MessageHandler(hwnd, uMsg, wParam, lParam);
    } else {
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

//実際にメッセージを処理するのはこの関数
LRESULT CALLBACK Window::MessageHandler(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    HDC hdc;
    PAINTSTRUCT ps;

    switch (uMsg) {
    case WM_DESTROY:
        CoUninitialize();
        PostQuitMessage(0);
        return 0;
    case WM_CREATE: {
        HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
            COINIT_DISABLE_OLE1DDE);
        ui.CreateControls(hwnd, ((LPCREATESTRUCT)lParam)->hInstance);
        return 0;
    }
    case WM_PAINT: {
     /*   HBRUSH hbr = CreateSolidBrush(RGB(55, 55, 55));

        hdc = BeginPaint(hwnd, &ps);

        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hbr);

        Rectangle(hdc, 5, 5, m_width - 5, m_height - 5);

        SelectObject(hdc, oldBrush);

        EndPaint(hwnd, &ps);
        DeleteObject(hbr);
        return 0;*/
    }
    case WM_COMMAND:
        if (LOWORD(wParam) == IDC_EDIT + 1) {
            wchar_t* filePath = ui.OpenFilePicker(hwnd);
            if (filePath) {
                ui.SetFilePathText(filePath);
            }
            return 0;
        } else if (LOWORD(wParam) == IDC_EDIT + 4) {
            std::ifstream ifs(ui.GetFilePathText());
            return 0;
        }
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}