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

	if (ImGui::BeginMenu("Tools")) {
		if (ImGui::MenuItem("Color Picker")) {
			setShowColor(true);
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

void MenuBar::setShowColor(bool b)
{
	b_color = b;
}

bool MenuBar::getShowColor()
{
	return b_color;
}

