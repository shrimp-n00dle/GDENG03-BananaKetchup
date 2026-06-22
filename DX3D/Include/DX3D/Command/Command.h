#pragma once
#include <iostream>
#include <vector>
#include <DX3D/Game/GameObject.h>
#include <DX3D/Clones/CubeClone.h>
#include <DX3D/Game/Game.h>
namespace dx3d
{
	
	class Command
	{
	public:
		virtual ~Command() {}
		virtual void execute() = 0;

		//std::vector<CubeClone*> cubeList;

		//for undoing commands
		//virtual void undo() = 0;

	};

	//Space Bar - Spawn Shapes
	class SpawnCommand : public Command
	{

	public:
		
		virtual void execute() {

			std::cout << "SPAWN";
		}
	};

	class DeleteCommand : public Command
	{
	public:
		virtual void execute()
		{
			//delete object
			std::cout << "DELETE?";

			//remove object from list
		}
	};

	class EndCommand : public Command
	{
	public:
		virtual void execute()
		{
			std::cout << "EXIT?";
		}
	};


}


