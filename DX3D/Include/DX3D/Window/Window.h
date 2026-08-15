#pragma once
#include <DX3D/Core/Base.h>
#include <DX3D/Core/Common.h>
#include <Windows.h>
#include <stdexcept>
//#define NOMINMAX //to avoid conflict with Windows.h MIN and MAX stuff

namespace dx3d
{
	class Window: public Base
	{
	public:
		explicit Window(const WindowDesc& desc);
		virtual ~Window() override;


		void* getHandle() const { return m_handle; }

		dx3d::Rect getClientAreaInScreenSpace();
	protected:
		void* m_handle{};
		Rect m_size{};
	};
}

