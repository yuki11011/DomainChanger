#pragma once

#include "UIControl.h"
#include "EditControl.h"
#include <functional>

class MessageLineControl : public EditControl {
public:
    MessageLineControl() {
        m_params.style = WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY;
    };

    void AddMessageToLines(const std::wstring& message);
};