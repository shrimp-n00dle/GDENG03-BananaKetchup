#pragma once
#include <DX3D/GUI/WinBase.h>
#include <DX3D/GUI/AboutWin.h>

class MenuBar : public WinBase
{
public:
	MenuBar();
	~MenuBar();

	void initialize() override;

	bool b_show = false;
	void setShow(bool b);
	bool getShow();

	bool b_color = false;
	void setShowColor(bool b);
	bool getShowColor();

	AboutWin* aboutWin = new AboutWin();

};

