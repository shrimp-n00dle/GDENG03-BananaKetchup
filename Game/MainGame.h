#pragma once
#include <DX3D/All.h>


class MainGame : public dx3d::Game
{
public:
	explicit MainGame(const dx3d::GameDesc& desc);
protected:
	virtual void onCreate();
	virtual void onUpdate(dx3d::f32 deltaTime);

private:
	dx3d::GameObject* m_objects[9]{};
	dx3d::f32 m_rot{}, m_scale_x{}, m_scale_y{}, m_scale_z{};
	int value = 0;
	int CubeCount = 0;
};

