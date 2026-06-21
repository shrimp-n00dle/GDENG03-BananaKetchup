#pragma once
#include <iostream>

class Player;
namespace dx3d
{
	
	class Command
	{
	public:
		virtual ~Command() {}
		virtual void execute(Player& p) = 0;

		//for undoing commands
		//virtual void undo() = 0;
	};

	//Space Bar - Spawn Shapes
	class SpawnCommand : public Command
	{
	public:
		virtual void execute(Player& p) {
			std::cout << "stuck";
		}
	};


}


