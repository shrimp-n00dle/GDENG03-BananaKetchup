#pragma once

#include <DX3D/Graphics/ImGui/imgui.h>
#include <DX3D/Graphics/ImGui/imgui_impl_win32.h>
#include <DX3D/Graphics/ImGui/imgui_impl_dx11.h>

class WinBase
{
public:
	WinBase();
	~WinBase();

	virtual void initialize() = 0;

};
