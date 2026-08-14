#pragma once
#include <DX3D/GUI/WinBase.h>
#include <DX3D/GUI/AboutWin.h>

class MenuBar : public WinBase
{
public:
	MenuBar();
	~MenuBar();

	void initialize() override;

	//ABOUT WINDOW
	bool b_show = false;
	void setShow(bool b);
	bool getShow();


	//COLOR PICKER WINDOW
	bool b_color = false;
	void setShowColor(bool b);
	bool getShowColor();


	//SAVE SCENE WINDOW
	bool b_save = false;
	void setShowSave(bool b);
	bool getShowSave();

	AboutWin* aboutWin = new AboutWin();

};

