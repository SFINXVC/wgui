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

    void window::show()
    {
        if (!has_handle())
            return;

        ShowWindow(m_handle, SW_SHOW);
        update();

        g_windows_created++;
    }

    void window::hide()
    {
        if (!has_handle())
            return;

        ShowWindow(m_handle, SW_HIDE);
        update();
    }

    void window::minimize()
    {
        if (!has_handle())
            return;

        ShowWindow(m_handle, SW_MINIMIZE);
        update();
    }

    void window::maximize()
    {
        if (!has_handle())
            return;
        
        ShowWindow(m_handle, SW_MAXIMIZE);
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

    void window::update()
    {
        UpdateWindow(m_handle);
    }

    void window::on_destroy(std::function<void(control*)> fn)
    {
        m_on_destroy = fn;
    }

    std::function<void(control*)> window::get_on_destroy()
    {
        return m_on_destroy;
    }

    void window::on_create(std::function<void(control*)> fn)
    {
        m_on_create = fn;
    }

    std::function<void(control*)> window::get_on_create()
    {
        return m_on_create;
    }

    void window::on_close(std::function<bool(control*)> fn)
    {
        m_on_close = fn;
    }

    std::function<bool(control*)> window::get_on_close()
    {
        return m_on_close;
    }

    bool window::create(HINSTANCE instance, std::string_view class_name, std::string_view title, const vec2i& size, const vec2i& pos, DWORD style, DWORD ex_style, HWND parent)
    {
        ZeroMemory(&m_wc, sizeof(WNDCLASSEX));

        m_wc.cbSize = sizeof(WNDCLASSEX);
        m_wc.lpfnWndProc = window_procedure;
        m_wc.hInstance = instance;
        m_wc.style = CS_HREDRAW | CS_VREDRAW;
        m_wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        m_wc.lpszClassName = class_name.data();

        if (!RegisterClassEx(&m_wc))
            return false;

        m_handle = CreateWindowEx(ex_style, class_name.data(), title.data(), style, pos.x, pos.y, size.x, size.y, parent, nullptr, instance, nullptr);

        if (!m_handle)
            return false;

        m_parent = parent;

        SetWindowLongPtr(m_handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

        return true;
    }

    LRESULT CALLBACK window::window_procedure(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
    {
        switch (msg)
        {
            case WM_CREATE:
            {
                window* w_ptr = reinterpret_cast<window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

                if (w_ptr && w_ptr->get_on_create())
                    w_ptr->get_on_create()(w_ptr);

                break;
            }
            case WM_CLOSE:
            {
                window* w_ptr = reinterpret_cast<window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
                
                bool res = true;

                if (w_ptr && w_ptr->get_on_close())
                    res = w_ptr->get_on_close()(w_ptr);

                if (res && w_ptr->has_handle())
                {
                    DestroyWindow(w_ptr->get_handle());
                    g_windows_created--;
                }

                break;
            }
            case WM_DESTROY:
            {
                window* w_ptr = reinterpret_cast<window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

                printf("window count: %d\n", g_windows_created);

                if (g_windows_created > 1)
                    break;

                if (w_ptr && w_ptr->get_on_destroy())
                    w_ptr->get_on_destroy()(w_ptr);

                PostQuitMessage(0);

                break;
            }
            case WM_COMMAND:
            {
                window* w_ptr = reinterpret_cast<window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

                if (!w_ptr)
                    break;

                if (w_ptr->get_children().empty())
                    break;

                for (const auto & i : w_ptr->get_children())
                {
                    HMENU menu = GetMenu(i->get_handle());

                    if (LOWORD(w_param) != LOWORD(menu))
                        continue;
                    
                    if (i->get_on_click())
                        i->get_on_click()();
                }

                break;
            }
            default:
                return DefWindowProcA(hwnd, msg, w_param, l_param);
        }

        return 0;
    }
}