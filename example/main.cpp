#include <iostream>

#include <wgui/window.h>

int main()
{
    wgui::window window("wgui_example", "wgui example window");

    // TODO: MOVE THIS LOOP SHIT TO ANOTHER PLACE, COULD BE ANYWHERE BUT NOT HERE!
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

}