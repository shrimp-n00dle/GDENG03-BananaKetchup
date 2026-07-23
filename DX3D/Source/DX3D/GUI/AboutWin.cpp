#include <DX3D/GUI/AboutWin.h>

using namespace dx3d;

AboutWin::AboutWin()
{
}

AboutWin::~AboutWin()
{
}


void AboutWin::setUpImage(dx3d::RefPtr<dx3d::TextureResource> textSrc)
{
	src = textSrc;
	ptrValue = reinterpret_cast<ImTextureID>(src.get());
	
}

void AboutWin::initialize()
{
	if (b_about_open)
	{
		ImGui::Begin("Credits");
		//Insert Photo
		ImVec2 display_size = ImVec2(100.0f, 100.0f);
		//ImGui::Image((ImTextureID)(intptr_t)ptrValue, display_size);
		ImGui::Image(ptrValue, display_size);
		//ImGui::Image((ImTextureID)ptrValue, display_size);
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
