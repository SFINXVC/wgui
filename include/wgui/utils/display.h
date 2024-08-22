#ifndef WGUI__UTILS__DISPLAY_H
#define WGUI__UTILS__DISPLAY_H

#include <Windows.h>
#include <WinUser.h>

#include "vec2i.h"

namespace wgui
{
    class display
    {
    public:
        static vec2i get_size()
        {
            return vec2i(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
        }

        static vec2i get_center()
        {
            const vec2i size = get_size();
            return vec2i(size.x / 2, size.y / 2);
        }

        static vec2i get_primary_monitor_size()
        {
            HMONITOR hMonitor = MonitorFromWindow(NULL, MONITOR_DEFAULTTOPRIMARY);
            MONITORINFO mi;
            GetMonitorInfo(hMonitor, &mi);
            return vec2i(mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top);
        }

        static vec2i get_cursor_position()
        {
            POINT pt;
            GetCursorPos(&pt);
            return vec2i(pt.x, pt.y);
        }

        static int get_dpi()
        {
            HDC hdc = GetDC(NULL);
            int dpi = GetDeviceCaps(hdc, LOGPIXELSX);
            ReleaseDC(NULL, hdc);
            return dpi;
        }

        static int get_display_count()
        {
            return GetSystemMetrics(SM_CMONITORS);
        }
    };
}

#endif // WGUI__UTILS__DISPLAY_H