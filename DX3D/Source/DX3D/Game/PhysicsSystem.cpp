#include <DX3D/Game/PhysicsSystem.h>

dx3d::PhysicsSystem::PhysicsSystem(const PhysicsSystemDesc& desc) : Base(desc.base)
{
	//Physics System Initialization
	this->physicsCommon = new PhysicsCommon();
	PhysicsWorld::WorldSettings settings;
	settings.defaultVelocitySolverNbIterations = 50;
	Vec3 gravityBase = Vec3(0, -9.81, 0);
	settings.gravity = Vector3(gravityBase.x, gravityBase.y, gravityBase.z);
	this->physicsWorld = this->physicsCommon->createPhysicsWorld(settings);
	std::cout << "Successfully created Physics World!" << std::endl;
}

dx3d::PhysicsSystem::~PhysicsSystem()
{
}

reactphysics3d::PhysicsWorld * dx3d::PhysicsSystem::getPhysicsWorld()
{
	return physicsWorld;
}

reactphysics3d::PhysicsCommon* dx3d::PhysicsSystem::getPhysicsCommon()
{
	return physicsCommon;
}


