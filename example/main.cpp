#include <wgui/window.h>
#include <wgui/button.h>

#include <wgui/utils/display.h>

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // alloc a console window for debugging and stuff, for example
    AllocConsole();

    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);

    printf("Hello There!\n");

    wgui::window window("wgui_example", "wgui example window");

    wgui::button btn(&window, "Hello World");
    
    btn.OnClick = []() -> void
    {
        printf("Button clicked!\n");
    };

    const wgui::vec2i screen_size = wgui::display::get_size();
    printf("detected screen size: %dx%d\n", screen_size.x, screen_size.y);
    printf("there are %d childrens inside the window\n", (int)window.get_children().size());

    int i = 0;
    for (const auto& child : window.get_children())
    {
        printf("[%d]: 0x%p @ %zu", i, (void*)child, sizeof(*child));
        ++i;
    }

#ifdef _MSC_VER
    btn.Position = {4, 4};
    btn.Size = {150, 45};
    
    window.Position = {0, 0};
    window.Size = {800, 600};

    window.Title = "Something";
#else
    btn.set_pos({4, 4});
    btn.set_size({150, 45});

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