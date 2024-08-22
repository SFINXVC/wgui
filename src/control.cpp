#include "control.h"
#include <winuser.h>

namespace wgui
{
    void control::set_size(const vec2i& size)
    {
        if (!has_handle())
            return;

        SetWindowPos(m_handle, nullptr, 0, 0, size.x, size.y, SWP_NOMOVE | SWP_NOZORDER);
    }

    vec2i control::get_size() const
    {
        if (!has_handle())
            return vec2i(0, 0);

        RECT rect;
        GetWindowRect(m_handle, &rect);

        return vec2i{ rect.right - rect.left, rect.bottom - rect.top };
    }

    void control::set_pos(const vec2i& pos)
    {
        if (!has_handle())
            return;

        SetWindowPos(m_handle, nullptr, pos.x, pos.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    }

    vec2i control::get_pos() const
    {
        if (!has_handle())
            return vec2i(0, 0);

        RECT rect;
        GetWindowRect(m_handle, &rect);

        POINT pt;
        pt.x = rect.left;
        pt.y = rect.top;

        MapWindowPoints(nullptr, m_parent, &pt, 1);

        return { pt.x, pt.y };
    }

    void control::set_style(UINT style)
    {
        if (!has_handle())
            return;

        SetWindowLongPtr(m_handle, GWL_STYLE, m_style);
        update();
    }

    void control::remove_style(UINT style)
    {
        if (!has_handle())
            return;

        SetWindowLongPtr(m_handle, GWL_STYLE, m_style);
        update();
    }

    UINT control::get_style() const
    {
        return m_style;
    }

    bool control::has_style(UINT style)
    {
        return (m_style & style) != 0;
    }

    void control::add_style(UINT style)
    {
        if (!has_handle())
            return;

        m_style |= style;
        SetWindowLongPtr(m_handle, GWL_STYLE, m_style);

        update();
    }

    void control::set_style_ex(UINT style)
    {
        if (!has_handle())
            return;

        m_style_ex = style;
        SetWindowLongPtr(m_handle, GWL_EXSTYLE, m_style_ex);

        update();
    }

    void control::remove_style_ex(UINT style)
    {
        if (!has_handle())
            return;

        m_style_ex &= ~style;
        SetWindowLongPtr(m_handle, GWL_EXSTYLE, m_style_ex);

        update();
    }

    UINT control::get_style_ex() const
    {
        return m_style_ex;
    }

    bool control::has_style_ex(UINT style)
    {
        return (m_style_ex & style) != 0;
    }

    void control::add_style_ex(UINT style)
    {
        if (!has_handle())
            return;

        m_style_ex |= style;
        SetWindowLongPtr(m_handle, GWL_EXSTYLE, m_style_ex);

        update();
    }

    void control::set_handle(HWND handle)
    {
        m_handle = handle;
    }

    HWND control::get_handle() const
    {
        return m_handle;
    }

    void control::set_parent(HWND handle)
    {
        m_parent = handle;
    }

    HWND control::get_parent() const
    {
        return m_parent;
    }

    bool control::has_handle() const
    {
        return m_handle != nullptr;
    }

    bool control::has_parent() const
    {
        return m_parent != nullptr;
    }

    void control::set_enabled(bool state)
    {
        m_enabled = state;
        EnableWindow(m_handle, m_enabled);
    }

    bool control::is_enabled() const
    {
        return m_enabled;
    }

    void control::add_children(control* child)
    {
        m_children.push_back(child);
        child->set_parent(get_handle());
    }

    void control::remove_children(control* child)
    {
        auto it = std::find(m_children.begin(), m_children.end(), child);
        if (it != m_children.end())
        {
            child->set_parent(nullptr);
            m_children.erase(it);
        }
    }

    std::vector<control*> control::get_children() const
    {
        return m_children;
    }

    void control::on_click(std::function<void()> fn)
    {
        m_on_click = fn;
    }

    std::function<void()> control::get_on_click()
    {
        return m_on_click;
    }

    void control::update()
    {
        if (!has_handle())
            return;
        
        SetWindowPos(m_handle, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
    }
}