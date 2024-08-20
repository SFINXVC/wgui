#ifndef WGUI__WINDOW_H
#define WGUI__WINDOW_H

#include "control.h"
#include "utils.h"

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

        void show(int cmd_show = SW_SHOW);
        void hide(int cmd_show = SW_HIDE);

        void set_title(std::string_view title);
        std::string get_title() const;

        void close();

        bool create(HINSTANCE instance, std::string_view class_name, std::string_view title, const vec2i& size = { CW_USEDEFAULT, CW_USEDEFAULT }, const vec2i& pos = { CW_USEDEFAULT, CW_USEDEFAULT }, DWORD style = WS_OVERLAPPEDWINDOW, DWORD ex_style = 0, HWND parent = nullptr);

    private:
        WNDCLASSA m_wc = { 0 };
    };
}

#endif // WGUI__WINDOW_H