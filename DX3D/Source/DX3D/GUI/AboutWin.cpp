#include <DX3D/GUI/AboutWin.h>

AboutWin::AboutWin()
{
}

AboutWin::~AboutWin()
{
}

void AboutWin::initialize()
{
	ImGui::Begin("Credits");
	ImGui::Text("Jan Vingno");
	ImGui::Text("GDENG03");


	ImGui::End();
}
