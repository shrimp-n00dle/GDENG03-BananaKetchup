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
	dx3d::GameObject* m_objects[25]{};
	dx3d::f32 m_rot{}, m_scale{};
	int value = 0;
	int CubeCount = 0;

	//Question #5 Variables
	dx3d::f32 warpTime;

	//Once it reaches this value, warp it onto the plane!
	float maxTime = 3.0f;
};

