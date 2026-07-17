#include <DX3D/GUI/AboutWin.h>

using namespace dx3d;

AboutWin::AboutWin()
{
}

AboutWin::~AboutWin()
{
}

void AboutWin::initialize()
{
	//auto texture = getResourceManager().createResourceFromFile<dx3d::TextureResource>(L"Game/Assets/Textures/wood.jpg");
	ImGui::Begin("Credits");
	//Insert Photo
	//ImVec2 display_size = ImVec2(100.0f, 100.0f);
	//ImGui::Image((ImTextureID)(intptr_t)texture, display_size);

	//Header
	ImGui::Text("About");
	ImGui::Text("Banana Catsup V1.0 (Pre-Genesis)");
	ImGui::Text("Developer: Jan Elizabeth G. Vingno");

	ImGui::Text("Acknowledgements:");
	ImGui::Text("PardCode Tutorials");


	ImGui::End();
}
