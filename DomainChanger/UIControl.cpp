#include "UIControl.h"

UIControl::UIControl() : m_hwnd(nullptr), m_params{} {
    m_id = GenerateId();
}

int UIControl::GenerateId() {
    static int s_currentId = 2000;
    return s_currentId++;
}

void UIControl::Setup(int x, int y, int width, int height, const std::wstring& text, DWORD style) {
    m_params.x = x;
    m_params.y = y;
    m_params.width = width;
    m_params.height = height;
    m_params.text = text;
    if (style != 0) m_params.style = style;
}