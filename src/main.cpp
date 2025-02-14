// Dear ImGui: standalone example application for DirectX 11

// Learn about Dear ImGui:
// - FAQ                  https://dearimgui.com/faq
// - Getting Started      https://dearimgui.com/getting-started
// - Documentation        https://dearimgui.com/docs (same as your local docs/ folder).
// - Introduction, links and more at the top of imgui.cpp

#include <includes.h>
#include <gui/gui.hpp>
#include <memory/ProcessManagement.hpp>
#include <gui/MainMenu.hpp>
#include <data/globals.hpp>
// Data

// Main code
INT APIENTRY WinMain(HINSTANCE instance, HINSTANCE, PSTR, INT cmd_show)
{
    auto gui_window = GuiWindow(instance);

    auto procManagement = ProcessManagement(Globals::GAME_PROCESS_NAME);

    //procManagement.FindPattern("55 48 8B EC 48 83 EC ?? 48 89 ?? ?? 48 89 ?? ?? 4C 89 ?? ?? 4C 89 ?? ?? 4C 89 ?? ?? 4C 89 ?? ?? 4C 8B F9 48 8B FA 49 8B F0 41 89 BF ?? ?? ?? ??");
    // Main loop
    while (gui_window.running)
    {
        gui_window.NewFrame();

        MainMenu::drawMenu(&gui_window);

        gui_window.Render();

    }

    return 0;
}

