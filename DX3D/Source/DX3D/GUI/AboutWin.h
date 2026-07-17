#pragma once
#include <DX3D/GUI/WinBase.h>
#include <DX3D/Core/Base.h>
#include <DX3D/Core/Core.h>

class AboutWin : public WinBase
{
public:
	AboutWin();
	~AboutWin();

	void initialize() override;

};
