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
	//Insert Photo

	//Header
	ImGui::Text("About");
	ImGui::Text("Banana Catsup V1.0 (Pre-Genesis)");
	ImGui::Text("Developer: Jan Elizabeth G. Vingno");

	ImGui::Text("Acknowledgements:");
	ImGui::Text("PardCode Tutorials");


	ImGui::End();
}
