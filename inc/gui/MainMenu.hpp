#pragma once

#include <includes.h>
#include <gui/gui.hpp>
#include <data/globals.hpp>

namespace MainMenu {
	inline bool shouldRender = false;

	void drawMenu(GuiWindow* guiWindow);
}