#ifndef WGUI__CONTROL_H
#define WGUI__CONTROL_H

#include <Windows.h>
#include <corecrt.h>

#include <functional>
#include <string_view>

#include "utils.h"

namespace wgui
{
    class control
    {
    public:
        control() = default;
        control(const control&) = delete;

        void set_size(const vec2i& size);
        vec2i get_size() const;

        void set_pos(const vec2i& size);
        vec2i get_pos() const;

        void set_style(UINT style);
        void remove_style(UINT style);
        UINT get_style() const;
        bool has_style(UINT style);
        void add_style(UINT style);

        void set_style_ex(UINT style);
        void remove_style_ex(UINT style);
        UINT get_style_ex() const;
        bool has_style_ex(UINT style);
        void add_style_ex(UINT style);

        void set_handle(HWND handle);
        HWND get_handle() const;

        void set_parent(HWND handle);
        HWND get_parent() const;

        bool has_handle() const;
        bool has_parent() const;

        void update();

    protected:
        HWND m_handle = nullptr;
        HWND m_parent = nullptr;

        UINT m_style = 0;
        UINT m_style_ex = 0;
    };
}

#endif // WGUI__CONTROL_H