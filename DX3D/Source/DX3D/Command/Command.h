#pragma once
#include <iostream>
#include <DX3D/Game/GameObject.h>
#include <DX3D/Component/CubeComponent.h>
#include "../../Game/Objects/Player.h"
//#include "C:/Users/Elizabeth/Documents/GitHub/BananaKetchup/Game/Objects/Player.h"
#include <vector>


namespace dx3d
{

	class Command
	{
	public:
		virtual ~Command() {}
		virtual void execute(Player& player) = 0;

		//for undoing commands
		//virtual void undo() = 0;

		std::vector<dx3d::CubeComponent> cubeList;
	};

	//Space Bar - Spawn Shapes
	class SpawnCommand : public Command
	{
	public:
		virtual void execute(Player& player) {

			auto cube = player.spawnCube();

			//Add it onto list
			cubeList.push_back(cube);

		}
	};
}


