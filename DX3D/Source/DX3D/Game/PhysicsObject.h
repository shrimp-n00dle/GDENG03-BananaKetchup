#pragma once
#include <DX3D/All.h>

#include <DX3D/Math/Vec3.h>

#include <reactphysics3d/reactphysics3d.h>

#include <DX3D/Game/PhysicsSystem.h>

using namespace reactphysics3d;


class PhysicsObject : public dx3d::GameObject
{
	dx3d_typeid(PhysicsObject)
public:
	explicit PhysicsObject(const dx3d::GameObjectDesc& desc);
	virtual ~PhysicsObject() override;
protected:
	virtual void onCreate();
	virtual void onUpdate(dx3d::f32 deltaTime);
	RigidBody* getRigidBody();


public:
	float mass = 1000.0f;
	RigidBody* rigidBody;
	dx3d::RefPtr<dx3d::PhysicsSystem> m_system{};
};

