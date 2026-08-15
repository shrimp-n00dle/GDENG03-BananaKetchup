#pragma once
#include <DX3D/All.h>
#include <DX3D/Command/Command.h>
#include <DX3D/Math/Vec3.h>

class Player : public dx3d::GameObject
{
	dx3d_typeid(Player)
public:
	explicit Player(const dx3d::GameObjectDesc& desc);
	virtual ~Player() override;
protected:
	virtual void onCreate();
	virtual void onUpdate(dx3d::f32 deltaTime);


public:
	//My Commands
	//dx3d::Command* spaceBar = new dx3d::SpawnCommand();

};

