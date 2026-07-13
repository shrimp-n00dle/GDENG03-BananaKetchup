#include <DX3D/Window/Window.h>

#include <DX3D/Graphics/ImGui/imgui.h>
#include <DX3D/Graphics/ImGui/imgui_impl_win32.h>
#include <DX3D/Graphics/ImGui/imgui_impl_dx11.h>

#include <iostream>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

static LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam)) {
		
		return true;
	}

	switch (msg)
	{

	case WM_CLOSE:
	{
		//ImGui Cleanup
		std::cout << "GUI CLEANED UP" << std::endl;
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();

		PostQuitMessage(0);
		break;
	}
	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}

	

	return 0;
}

void CleanUpImGui()
{
	std::cout << "GUI CLEANED UP" << std::endl;
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

dx3d::Window::Window(const WindowDesc& desc) : Base(desc.base), m_size(desc.size)
{
	auto registerWindowClassFunction = []()
		{
			//Create a window class
//To define the properties of a window class before it is registered with RegisterClassEx.
			WNDCLASSEX wc{};
			wc.cbSize = sizeof(WNDCLASSEX);

			//The name of your class/ representing a null-terminated string that serves as the unique identifier for a window class
			wc.lpszClassName = L"DX3DWindow";

			//It assigns the Window Procedure (often called WndProc or WindowProc) to the window class, which is a callback function that handles messages (like clicks, paint requests, or closing) 
			wc.lpfnWndProc = &WindowProcedure;


			return RegisterClassEx(&wc);

		};

	static const auto windowClassId = std::invoke(registerWindowClassFunction);


	//PARAMETRS -
	// (1)Extended Window Style = NULL 
	// (2)Name of Window Class =
	// (3)Title of our window
	// (4)Window Style (standard window / title bar window / and a system menu)
	// (5)Position of the window
	// (6) Do you want to provide a initial position? if NO use CW_USEDEFAULT
	// (7) Width
	// (8) Height


	if (!windowClassId) {
		DX3DLogThrowError("RegisterClassEx failed.");
	}
	RECT rc{ 0,0,m_size.width,m_size.height };
	AdjustWindowRect(&rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, false);
	m_handle = CreateWindowEx(NULL, MAKEINTATOM(windowClassId), L"BananaKetchup_Ver1.0",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rc.right - rc.left, rc.bottom - rc.top,
		NULL, NULL, NULL, NULL);

	if (!m_handle)
	{
		DX3DLogThrowError("CreateWindowEx failed");
	}

	
	ShowWindow(static_cast<HWND>(m_handle), SW_SHOW);

	auto hwnd = static_cast<HWND>(m_handle);
	setHWND(hwnd);
}


dx3d::Rect dx3d::Window::getClientAreaInScreenSpace()
{
	auto hwnd = getHwnd();

	RECT client{};
	GetClientRect(hwnd, &client);

	POINT topLeft{ client.left, client.top };
	POINT bottomRight{ client.right, client.bottom };
	ClientToScreen(hwnd, &topLeft);
	ClientToScreen(hwnd, &bottomRight);

	return {
		topLeft.x ,
		topLeft.y ,
		bottomRight.x - topLeft.x,
		bottomRight.y - topLeft.y
	};
}

HWND dx3d::Window::getHwnd()
{
	return static_cast<HWND>(m_handle);
}

void dx3d::Window::setHWND(HWND hwnd)
{
	m_handle = hwnd;
}


dx3d::Window::~Window()
{
	DestroyWindow(static_cast<HWND>(m_handle));
}
