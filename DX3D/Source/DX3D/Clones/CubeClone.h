#pragma once
#pragma once
#include <DX3D/All.h>
#include <DX3D/Game/Game.h>


class CubeClone : public dx3d::GameObject
{
	dx3d_typeid(CubeClone)
public:
	explicit CubeClone(const dx3d::GameObjectDesc& desc);
	virtual ~CubeClone() override;
protected:
	virtual void onCreate();
	virtual void onUpdate(dx3d::f32 deltaTime);
};
