#pragma once
#include <iostream>
#include <vector>
#include <DX3D/Graphics/GraphicsEngine.h>



namespace dx3d
{
	
	class Command
	{
	public:
		std::vector<int> test;
		virtual ~Command() {}
		virtual void execute(GraphicsEngine& g) = 0;

		//std::vector<CubeClone*> cubeList;
		//for undoing commands
		virtual void undo(GraphicsEngine& g) = 0;

		//for redoing commands
		//virtual void redo() = 0;

		virtual void promptList();

	};

	//Space Bar - Spawn Shapes
	class SpawnCommand : public Command
	{

	public:
		virtual void execute(GraphicsEngine& g);
		virtual void undo(GraphicsEngine& g);
	};

	//Backspace - remove the latest shape added
	class DeleteCommand : public Command
	{
	public:
		virtual void execute(GraphicsEngine& g);
		virtual void undo(GraphicsEngine& g);

	};

	//Escape - closes program
	class EndCommand : public Command
	{
	public:
		virtual void execute(GraphicsEngine& g);
		virtual void undo(GraphicsEngine& g);
	};


}


