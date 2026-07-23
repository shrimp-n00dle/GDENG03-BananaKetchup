#pragma once
#include <DX3D/GUI/WinBase.h>
#include <DX3D/Core/Base.h>
#include <DX3D/Core/Core.h>


class AboutWin : public WinBase
{
public:
	AboutWin();
	~AboutWin();

	void setUpImage(dx3d::RefPtr<dx3d::TextureResource> textSrc);
	void initialize() override;
	void setOpen(bool b);
private:
	bool b_about_open = false;
	dx3d::RefPtr<dx3d::TextureResource> src;
	ImTextureID ptrValue;

};
