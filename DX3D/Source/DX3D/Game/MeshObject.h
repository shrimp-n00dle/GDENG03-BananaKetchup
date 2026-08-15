#pragma once
#include <DX3D/All.h>
#include <DX3D/Command/Command.h>
#include <DX3D/Math/Vec3.h>

class MeshObject : public dx3d::GameObject
{
	dx3d_typeid(MeshObject)
public:
	explicit MeshObject(const dx3d::GameObjectDesc& desc);
	virtual ~MeshObject() override;
	dx3d::Vec3 getScale();
protected:
	virtual void onCreate();
	virtual void onUpdate(dx3d::f32 deltaTime);
	float meshScale = 1.0f;


public:
	//My Commands
	//dx3d::Command* spaceBar = new dx3d::SpawnCommand();

};

