#pragma once
#include <iostream>
#include <vector>
#include <DX3D/Game/WorldRenderer.h>
#include <string.h>



namespace dx3d
{
	
	class Command
	{
	public:
		//Command Queue
		std::vector<std::string> queueList;

		virtual ~Command() {}
		virtual void execute(WorldRenderer& g) = 0;

		//std::vector<CubeClone*> cubeList;
		//for undoing commands
		virtual void undo(WorldRenderer& g) = 0;

		//for redoing commands
		//virtual void redo() = 0;

		virtual void promptList();

	};

	//Space Bar - Spawn Shapes
	//class SpawnCommand : public Command
	//{

	//public:
	//	virtual void execute(WorldRenderer& g);
	//	virtual void undo(WorldRenderer& g);
	//};

	//Backspace - remove the latest shape added
	//class DeleteCommand : public Command
	//{
	//public:
	//	virtual void execute(WorldRenderer& g);
	//	virtual void undo(WorldRenderer& g);

	//};

	//Escape - closes program
	class EndCommand : public Command
	{
	public:
		virtual void execute(WorldRenderer& g);
		virtual void undo(WorldRenderer& g);
	};


}


