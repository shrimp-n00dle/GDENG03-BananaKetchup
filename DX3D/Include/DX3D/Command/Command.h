#pragma once
#include <iostream>
#include <vector>
#include <DX3D/Game/GameObject.h>
namespace dx3d
{
	
	class Command
	{
	public:
		virtual ~Command() {}
		virtual void execute(GameObject* cube) = 0;

		std::vector<GameObject*> cubeList;

		//for undoing commands
		//virtual void undo() = 0;

	};

	//Space Bar - Spawn Shapes
	class SpawnCommand : public Command
	{
	public:
		virtual void execute(GameObject* cube) {
			cubeList.push_back(cube);
		}
	};

	class DeleteCommand : public Command
	{
	public:
		virtual void execute(GameObject* cube)
		{
			//delete object
			std::cout << "DELETE?";

			//remove object from list
		}
	};

	class EndCommand : public Command
	{
	public:
		virtual void execute(GameObject* cube)
		{
			std::cout << "EXIT?";
		}
	};


}


