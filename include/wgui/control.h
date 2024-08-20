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

        // events
        void set_on_click_callback(std::function<void()> fn);
        std::function<void()> get_on_click_callback();

    protected:
        HWND m_handle = nullptr;
        HWND m_parent = nullptr;

        UINT m_style = 0;
        UINT m_style_ex = 0;

    private:
        std::function<void()> m_on_click;

#ifdef _MSC_VER
    public:
        __declspec(property(get=get_size, put=set_size)) vec2i Size;
        __declspec(property(get=get_pos, put=set_pos)) vec2i Position;
        __declspec(property(get=get_style, put=set_style)) UINT Style;
        __declspec(property(get=get_style_ex, put=set_style_ex)) UINT StyleEx;
        __declspec(property(get=get_handle, put=set_handle)) HWND Handle;
        __declspec(property(get=get_parent, put=set_parent)) HWND Parent;

        // TODO: Fix this property stuffs
        __declspec(property(get=get_on_click_callback, put=set_on_click_callback)) std::function<void()> OnClick;
#endif // _MSC_VER
    };
}

#endif // WGUI__CONTROL_H