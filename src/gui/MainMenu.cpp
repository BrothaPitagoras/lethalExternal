#include <gui/MainMenu.hpp>

void MainMenu::drawMenu(GuiWindow* guiWindow) {
    if (GetAsyncKeyState(VK_END) & 1) {
        MainMenu::shouldRender = !MainMenu::shouldRender;

        long style = GetWindowLongPtr(guiWindow->window, GWL_EXSTYLE);
        style = MainMenu::shouldRender ? (style & ~WS_EX_LAYERED) : (style | WS_EX_LAYERED);
        SetWindowLongPtr(guiWindow->window, GWL_EXSTYLE, style);

        SetForegroundWindow(MainMenu::shouldRender ? guiWindow->window : FindWindow(nullptr, Globals::GAME_WINDOW_NAME.c_str()));
    }

    if (MainMenu::shouldRender)
    {
        ImGui::Begin("MainMenu");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }
}