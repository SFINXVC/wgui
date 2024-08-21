#include "button.h"
#include <libloaderapi.h>
#include <winuser.h>

namespace wgui
{
    button::button(control* parent, std::string_view text)
    {
        create(parent->get_handle(), text);
    }

    button::button(HWND parent, std::string_view text)
    {
        create(parent, text);
    }

    void button::set_text(std::string_view text)
    {
        SetWindowText(m_handle, text.data());
    }

    std::string button::get_text() const
    {
        int length = GetWindowTextLength(m_handle);
        std::string text(length, '\0');
        GetWindowText(m_handle, text.data(), length + 1);
        return text;
    }

    bool button::create(HWND parent, std::string_view text)
    {
        m_handle = CreateWindowEx(
            0,
            "BUTTON",
            text.data(),
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            0, 0, 0, 0,
            parent,
            NULL,
            GetModuleHandle(NULL),
            NULL
        );

        if (!m_handle)
            return false;

        SetWindowText(m_handle, text.data());

        return true;
    }
}