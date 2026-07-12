#pragma once
#include <DX3D/Core/Base.h>
#include <DX3D/Core/Common.h>
#include <Windows.h>
#include <stdexcept>

namespace dx3d
{
	class Window : public Base
	{
	public:
		explicit Window(const WindowDesc& desc);
		virtual ~Window() override;

		dx3d::Rect getClientAreaInScreenSpace();

		HWND getHwnd();
		void setHWND(HWND hwnd);

	protected:
		void* m_handle{};
		Rect m_size{};
		
	};
}

