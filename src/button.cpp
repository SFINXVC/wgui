#include "button.h"
#include <libloaderapi.h>
#include <winuser.h>

namespace wgui
{
    button::button(control* parent, std::string_view text)
    {
        create(parent, text);
    }

    button::button(int id, control* parent, std::string_view text)
    {
        // TODO: Write the ids, (kinda lazy to code rn)
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

    bool button::create(control* parent, std::string_view text)
    {
        if (!parent->has_handle())
            return false;
        
        m_handle = CreateWindowEx(
            0,
            "BUTTON",
            text.data(),
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            0, 0, 0, 0,
            parent->get_handle(),
            (HMENU)parent->get_next_id(),
            GetModuleHandle(NULL),
            NULL
        );

        if (!m_handle)
            return false;

        SetWindowText(m_handle, text.data());

        parent->add_children(this);

        return true;
    }
}