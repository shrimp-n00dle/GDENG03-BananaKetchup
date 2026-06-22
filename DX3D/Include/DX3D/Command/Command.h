#pragma once
#include <iostream>
#include <vector>
#include <DX3D/Game/GameObject.h>
#include <DX3D/Graphics/GraphicsEngine.h>
namespace dx3d
{
	
	class Command
	{
	public:
		virtual ~Command() {}
		virtual void execute(UniquePtr<GraphicsEngine> g) = 0;

		//std::vector<CubeClone*> cubeList;

		//for undoing commands
		//virtual void undo() = 0;

	};

	//Space Bar - Spawn Shapes
	class SpawnCommand : public Command
	{

	public:
		
		virtual void execute(UniquePtr<GraphicsEngine> g) {

			//g->bSpawn = true;
			std::cout << "SPAWN";
		}
	};

	class DeleteCommand : public Command
	{
	public:
		virtual void execute(UniquePtr<GraphicsEngine> g)
		{
			//delete object
			std::cout << "DELETE?";

			//remove object from list
		}
	};

	class EndCommand : public Command
	{
	public:
		virtual void execute(UniquePtr<GraphicsEngine> g)
		{
			std::cout << "EXIT?";
		}
	};


}


