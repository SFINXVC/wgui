#include <wgui/window.h>
#include <wgui/button.h>
#include <wgui/utils/vec2i.h>

#include <wgui/utils/display.h>
#include <winuser.h>

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // alloc a console window for debugging and stuff, for example
    AllocConsole();

    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);

    printf("Hello There!\n");

    wgui::window window("wgui_example", "wgui example window");

    window.OnDestroy = [](wgui::control* ctrl) -> void
    {
        MessageBox(ctrl->get_handle(), "Received window OnDestroy event!", "Alert!", MB_OK | MB_ICONINFORMATION);
    };

    window.OnClose = [](wgui::control* ctrl) -> bool
    {
        int response = MessageBox(ctrl->get_handle(), "Are you sure you want to exit?", "Confirm Exit", MB_YESNO | MB_ICONQUESTION);
        
        if (response == IDNO)
            return false;
        else if (response == IDYES)
            return true;
        else
            MessageBox(ctrl->get_handle(), "Unknown response ID for msgbox", "Error", MB_OK | MB_ICONERROR);

        return true;
    };

    wgui::button btn(&window, "Hello World");
    wgui::button btn2(&window, "Im probably fine?");
    
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
        printf("[%d]: 0x%p @ %zu\n", i, (void*)child, sizeof(*child));
        ++i;
    }

#ifdef _MSC_VER
    btn.Position = {4, 4};
    btn.Size = {150, 45};

    // test calc
    btn2.Position = btn.Position + wgui::vec2i(btn.Size.x, 0) + wgui::vec2i(4, 0);
    btn2.Size = {150, 45};
    window.Size = {800, 600};

    window.Position = wgui::vec2i(
        (screen_size.x - window.Size.x) / 2,
        (screen_size.y - window.Size.y) / 2
    );

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