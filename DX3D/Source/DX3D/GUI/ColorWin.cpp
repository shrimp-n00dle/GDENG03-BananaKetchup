#include <DX3D/GUI/ColorWin.h>


ColorWin::ColorWin()
{
}

ColorWin::~ColorWin()
{
}

void ColorWin::initialize()
{
	static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f );
	ImGui::Begin("Color Picker Screen");
	ImGuiColorEditFlags flags = ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_PickerHueWheel;
	ImGui::ColorPicker4("Current Color", (float*)&clear_color, flags);
	ImGui::End();
}
