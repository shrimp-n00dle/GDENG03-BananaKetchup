#pragma once
#include <DX3D/Core/Base.h>
#include <Windows.h>
#include <stdexcept>

namespace dx3d
{
	class Window : public Base
	{
	public:
		Window();
		virtual ~Window() override;

	private:
		void* m_handle{};
	};
}

