#include <DX3D/GUI/MenuBar.h>



MenuBar::MenuBar()
{
}

MenuBar::~MenuBar()
{
}

void MenuBar::initialize()
{
	ImGui::BeginMainMenuBar();

	if (ImGui::BeginMenu("About")) {  
		if (ImGui::MenuItem("Credits")) {
			setShow(true);
		}
		ImGui::EndMenu();
	};

	
	ImGui::EndMainMenuBar();

}

void MenuBar::setShow(bool b)
{
	b_show = b;
}

bool MenuBar::getShow()
{
	return b_show;
}

