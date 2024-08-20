#include <iostream>

#include <wgui/window.h>

int main()
{
    wgui::window window("wgui_example", "wgui example window");

#ifdef _MSC_VER
    window.Position = {0, 0};
    window.Size = {800, 600};

    window.Title = "Something";
#else
    window.set_pos({0, 0});
    window.set_size({800, 600});

    window.set_title("Something");
#endif

    window.show();

    // TODO: MOVE THIS LOOP SHIT TO ANOTHER PLACE, COULD BE ANYWHERE BUT NOT HERE!
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

}