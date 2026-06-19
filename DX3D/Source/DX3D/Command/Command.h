#pragma once
#include <iostream>

namespace dx3d
{
	class Command
	{
	public:
		virtual ~Command() {}
		virtual void execute() = 0;

		//for undoing commands
		virtual void undo() = 0;
	};

	//Space Bar - Spawn Shapes
	class SpawnCommand : public Command
	{
	public:
		virtual void execute() {
			std::cout << "SPACE COMMAND FROM COMMAND.H" << std::endl;

		}
	};
	
	//Backspace - delete latest cube
	class RemoveTopShapeCommand : public Command
	{
	public:
		virtual void execute()
		{
			std::cout << "BACKSPACE COMMAND FROM COMMAND.H" << std::endl;
		}
	};
}
