#include <DX3D/GUI/AboutWin.h>

using namespace dx3d;

AboutWin::AboutWin()
{
	
	//manager = nullptr;
	setUpImage();
}

AboutWin::~AboutWin()
{
}


void AboutWin::setUpImage()
{




}

void AboutWin::initialize()
{
	if (b_about_open)
	{
		//auto texture = manager.createResourceFromFile<dx3d::TextureResource>(L"Game/Assets/Textures/wood.jpg");
		ImGui::Begin("Credits");
		//Insert Photo
		//ImVec2 display_size = ImVec2(100.0f, 100.0f);
		//ImGui::Image((ImTextureID)(intptr_t)texture, display_size);
		//ImGui::Image((void*)my_texture_srv, display_size);

		//Header
		ImGui::Text("About");
		ImGui::Text("Banana Catsup V1.0 (Pre-Genesis)");
		ImGui::Text("Developer: Jan Elizabeth G. Vingno");

		ImGui::Text("Acknowledgements:");
		ImGui::Text("PardCode Tutorials");

		if (ImGui::Button("Close Window"))
		{
			b_about_open = false;
		}
		ImGui::End();

	}




}

void AboutWin::setOpen(bool b)
{
	b_about_open = b;
}
