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
	if (ImGui::BeginMenu("Scene Settings")) {
		if (ImGui::MenuItem("Save Scene")) {
			//Insert functionality here
			setShowSave(true);
		}
		if (ImGui::MenuItem("Load Scene")) {
			setShowLoad(true);
		}

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


//ABOUT WINDOW
void MenuBar::setShow(bool b){b_show = b;}
bool MenuBar::getShow(){return b_show;}

//COLOR PICKER WINDOW
void MenuBar::setShowColor(bool b){b_color = b;}
bool MenuBar::getShowColor(){return b_color;}

//SAVE SCENE WINDOW
void MenuBar::setShowSave(bool b) { b_save = b; }
bool MenuBar::getShowSave() { return b_save; }

//LOAD SCENE WINDOW
void MenuBar::setShowLoad(bool b) { b_load = b; }
bool MenuBar::getShowLoad() { return b_load; }

