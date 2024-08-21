#ifndef WGUI__UTILS__MESSAGEBOX_H
#define WGUI__UTILS__MESSAGEBOX_H

#include <cstdint>

#include <string_view>

#include <Windows.h>

namespace wgui
{
    class messagebox
    {
    public:
        messagebox() = default;

        int show(std::string_view title, std::string_view description, uint32_t type = MB_OK)
        {
            return MessageBox(nullptr, description.data(), title.data(), type);
        }

    private:
        messagebox(const messagebox&) = delete;
        messagebox& operator=(const messagebox&) = delete;
    };
}

#endif // WGUI__UTILS__MESSAGEBOX_H