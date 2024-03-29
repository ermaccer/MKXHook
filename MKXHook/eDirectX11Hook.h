#pragma once
#include <Windows.h>
#include <dxgi.h>
#include <d3d11.h>
#include "kiero/kiero.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"


extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef HRESULT(__stdcall* ResizeBuffers) (IDXGISwapChain * pSwapChain,UINT BufferCount, UINT Width,UINT Height,DXGI_FORMAT NewFormat,UINT SwapChainFlags);

class eDirectX11Hook {
public:
	static Present m_pPresent;
	static ResizeBuffers m_pResizeBuffers;
	static HWND ms_hWindow;
	static WNDPROC ms_pWndProc;
	static ID3D11Device* pDevice;
	static ID3D11DeviceContext* pContext;
	static ID3D11RenderTargetView* mainRenderTargetView;
	static ImGuiStyle	ms_localStyleCopy;

	static bool ms_bInit;
	static bool ms_bShouldReloadFonts;

	static void	   Init();
	static void    SetImGuiStyle();
	static void    InitImGui();
	static void	   ReloadImGuiFont();
	static HRESULT __stdcall Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	static LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static HRESULT __stdcall ResizeBuffers(IDXGISwapChain * pSwapChain,UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);

};


DWORD WINAPI DirectXHookThread(LPVOID lpReserved);
