#include "StaticControl.h"

bool StaticControl::Create(HWND hParentWindow, HINSTANCE hInstance) {
    m_hwnd = CreateWindowEx(
        0, L"STATIC", m_params.text.c_str(), m_params.style,
        m_params.x, m_params.y, m_params.width, m_params.height,
        hParentWindow, (HMENU)(intptr_t)m_id, hInstance, nullptr);
    return m_hwnd != nullptr;
}
