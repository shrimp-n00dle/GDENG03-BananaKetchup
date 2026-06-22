#pragma once
#include <iostream>
#include <vector>
#include <DX3D/Graphics/GraphicsEngine.h>


namespace dx3d
{
	
	class Command
	{
	public:
		virtual ~Command() {}
		virtual void execute(GraphicsEngine& g) = 0;

		//std::vector<CubeClone*> cubeList;
		//for undoing commands
		//virtual void undo() = 0;

	};

	//Space Bar - Spawn Shapes
	class SpawnCommand : public Command
	{

	public:
		
		virtual void execute(GraphicsEngine& g);
	};

	//class DeleteCommand : public Command
	//{
	//public:
	//	virtual void execute(const GraphicsEngine& g)
	//	{
	//		//delete object
	//		std::cout << "DELETE?";

	//		//remove object from list
	//	}
	//};

	//class EndCommand : public Command
	//{
	//public:
	//	virtual void execute(UniquePtr<GraphicsEngine> g)
	//	{
	//		std::cout << "EXIT?";
	//	}
	//};


}


