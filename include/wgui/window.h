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

        bool create(HINSTANCE instance, std::string_view class_name, std::string_view title, const vec2i& size = { CW_USEDEFAULT, CW_USEDEFAULT }, const vec2i& pos = { CW_USEDEFAULT, CW_USEDEFAULT }, DWORD style = WS_OVERLAPPEDWINDOW, DWORD ex_style = 0, HWND parent = nullptr);

    private:
        WNDCLASSA m_wc = { 0 };

#ifdef _MSC_VER
    public:
        __declspec(property(get=get_title, put=set_title)) std::string Title;
    };
#endif // _MSC_VER
}

#endif // WGUI__WINDOW_H