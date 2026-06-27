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
	dx3d::f32 m_rot{}, m_scale{}, m_pos{};
	int value = 0;
	int CubeCount = 0;

	float min_scale = 0.25f;
	float max_scale = 1.0f;

};

