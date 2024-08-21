#ifndef WGUI__WINDOW_H
#define WGUI__WINDOW_H

#include "control.h"
#include "utils/vec2i.h"

#include <string_view>
#include <winuser.h>

namespace wgui
{
    class window : public control
    {
    public:
        window(std::string_view class_name, std::string_view title);
        window(HINSTANCE instance, std::string_view class_name, std::string_view title);
        ~window();

        void show();
        void hide();
        void minimize();
        void maximize();

        void set_title(std::string_view title);
        std::string get_title() const;

        void close();
        void update() override;

        // ------------------ events -----------------------
        void on_destroy(std::function<void(control*)> fn);
        std::function<void(control*)> get_on_destroy();

        void on_create(std::function<void(control*)> fn);
        std::function<void(control*)> get_on_create();
        
        void on_close(std::function<void(control*)> fn);
        std::function<void(control*)> get_on_close();
        // -------------------------------------------------

        bool create(HINSTANCE instance, std::string_view class_name, std::string_view title, const vec2i& size = { CW_USEDEFAULT, CW_USEDEFAULT }, const vec2i& pos = { CW_USEDEFAULT, CW_USEDEFAULT }, DWORD style = WS_OVERLAPPEDWINDOW, DWORD ex_style = 0, HWND parent = nullptr);

    private:
        static LRESULT CALLBACK window_procedure(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);

    private:
        WNDCLASSA m_wc = { 0 };

        std::function<void(control*)> m_on_destroy;
        std::function<void(control*)> m_on_create;
        std::function<void(control*)> m_on_close;

#ifdef _MSC_VER
    public:
        __declspec(property(get=get_title, put=set_title)) std::string Title;
    };
#endif // _MSC_VER
}

#endif // WGUI__WINDOW_H