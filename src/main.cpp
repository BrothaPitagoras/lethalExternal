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
#include <data/GameClasses.hpp>
// Data

// Main code
INT APIENTRY WinMain(HINSTANCE instance, HINSTANCE, PSTR, INT cmd_show)
{
    auto gui_window = GuiWindow(instance);

    auto procManagement = ProcessManagement(Globals::GAME_PROCESS_NAME, Globals::MODULE_GAMEASSEMBLY);

    //uintptr_t staminaFunctionStaticAddress = procManagement.FindPattern("40 53 48 83 EC 30 80 3D ?? ?? ?? ?? 00 48 8B D9 75 1F 48 8D 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 8D 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? C6 05 ?? ?? ?? ?? 01 33 C9 E8 ?? ?? ?? ?? 48 85 C0 0F 84 ?? ?? ?? ?? 48 8B 40 30 48 85 C0 0F 84 ?? ?? ?? ?? 83 78 40 02 0F 84 ?? ?? ?? ?? 80 7B 47 00 0F 84 ?? ?? ?? ?? 48 8B 43 38 48 85 C0 0F 84 ?? ?? ?? ?? 80 78 28 00 0F 85 ?? ?? ?? ?? 33 C9 E8 ?? ?? ?? ?? 84 C0 75 68 48");
    
    uintptr_t network_class_address = procManagement.ReadMemory<uintptr_t>(procManagement.moduleBaseAddr + Offsets::singleton_network_class);
    uintptr_t network_static_fields_address = procManagement.ReadMemory<uintptr_t>(network_class_address + Offsets::network_static_fields_offset);
    uintptr_t network_object_address = procManagement.ReadMemory<uintptr_t>(network_static_fields_address + Offsets::network_object_offset);
    Offsets::Network_o network_object = procManagement.ReadMemory<Offsets::Network_o>(network_object_address);
    Offsets::Player_o Player_object = procManagement.ReadMemory<Offsets::Player_o>(network_object.localPlayer);
    
    while (gui_window.running)
    {
        gui_window.NewFrame();

        MainMenu::drawMenu(&gui_window);

        gui_window.Render();

    }

    return 0;
}

