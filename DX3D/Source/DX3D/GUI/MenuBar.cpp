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

	//SAVE AND LOAD SCENE
	if (ImGui::BeginMenu("Save Scene")) {
		//Insert functionality here
		ImGui::EndMenu();
	};

	//SPAWNIES
	if (ImGui::BeginMenu("Instantiate")) {

		//PLANE
		if (ImGui::MenuItem("Plane")) {
			
		}

		//CUBE
		if (ImGui::MenuItem("Cube")) {

		}


		//SPHERE
		if (ImGui::MenuItem("Sphere")) {

		}


		//CAPSULE
		if (ImGui::MenuItem("Capsule")) {

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

