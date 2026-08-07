#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <DX3D/Core/Common.h>
#include <DX3D/Core/Base.h>

#include <DX3D/Math/Vec3.h>
#include <reactphysics3d/reactphysics3d.h>

using namespace reactphysics3d;

/*class PhysicsComponent*/;

namespace dx3d {
	class PhysicsSystem : public Base
	{
	public:
		//typedef std::string String;
		//typedef std::unordered_map<String, PhysicsComponent*> ComponentTable;
		//typedef std::vector<PhysicsComponent*> ComponentList;

		PhysicsSystem(const PhysicsSystemDesc& desc);
		~PhysicsSystem();

		//void registerComponent(PhysicsComponent* component);
		//void unregisterComponent(PhysicsComponent* component);
		//void unregisterComponentByName(String name);
		//PhysicsComponent* findComponentByName(String name);
		//ComponentList getAllComponents();


		//void updateAllComponents();
		PhysicsWorld* getPhysicsWorld();
		PhysicsCommon* getPhysicsCommon();

	private:
		//ComponentTable componentTavle;
		//ComponentList componentList;

		PhysicsCommon* physicsCommon;
		PhysicsWorld* physicsWorld;
	};
}
