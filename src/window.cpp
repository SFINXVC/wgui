#include "window.h"

#include <libloaderapi.h>
#include <winuser.h>

namespace wgui
{
    window::window(std::string_view class_name, std::string_view title)
    {
        create(nullptr, class_name, title);
    }

    window::window(HINSTANCE instance, std::string_view class_name, std::string_view title)
    {
        create(instance, class_name, title);
    }

    window::~window()
    {
        if (!has_handle())
            return;

        DestroyWindow(m_handle);
    }

    void window::show(int cmd_show)
    {
        if (!has_handle())
            return;

        ShowWindow(m_handle, cmd_show);
        update();
    }

    void window::hide(int cmd_show)
    {
        if (!has_handle())
            return;

        ShowWindow(m_handle, cmd_show);
        update();
    }

    void window::set_title(std::string_view title)
    {
        if (!has_handle())
            return;

        SetWindowTextA(m_handle, title.data());
    }

    std::string window::get_title() const
    {
        if (!has_handle())
            return "";
        
        // TODO: Change This - Deprecated
        char title[256];
        GetWindowTextA(m_handle, title, sizeof(title));

        return std::string(title);
    }

    void window::close()
    {
        if (!has_handle())
            return;

        DestroyWindow(m_handle);
        set_handle(nullptr);
    }

    bool window::create(HINSTANCE instance, std::string_view class_name, std::string_view title, const vec2i& size, const vec2i& pos, DWORD style, DWORD ex_style, HWND parent)
    {
        m_wc.lpfnWndProc = DefWindowProcA;
        m_wc.hInstance = instance;
        m_wc.lpszClassName = class_name.data();

        if (!RegisterClassA(&m_wc))
            return false;

        m_handle = CreateWindowExA(ex_style, class_name.data(), title.data(), style, pos.x, pos.y, size.x, size.y, parent, nullptr, instance, nullptr);

        if (!has_handle())
            return false;

        m_parent = parent;

        SetWindowLongPtr(m_handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

        return true;
    }
}