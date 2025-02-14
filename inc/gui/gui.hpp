#pragma once

#include <includes.h>
#include <data/globals.hpp>

class GuiWindow
{
public:
	
	bool running = true;

	WNDCLASSEXW window_class;
	HWND window;
	unsigned int window_width;
	unsigned int window_height;
	
	RECT windowsPosition;
	
	// Data

	ID3D11Device* g_pd3dDevice = nullptr;
	ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
	IDXGISwapChain* g_pSwapChain = nullptr;
	bool g_SwapChainOccluded = false;
	unsigned int g_resizeWidth = 0;
	unsigned int g_resizeHeight = 0;
	ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;

	GuiWindow(HINSTANCE instance);
	~GuiWindow();

	int initialize(const std::string& gameWindowName);

	void CleanupDeviceD3D();
	void CreateRenderTarget();
	void CleanupRenderTarget();
	bool CreateDeviceD3D(HWND hWnd);

	void updateWindow();

	void NewFrame();

	void Render();

};