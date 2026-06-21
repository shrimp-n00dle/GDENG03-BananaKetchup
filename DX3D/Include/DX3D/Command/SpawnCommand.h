#pragma once
#include <DX3D/Command/Command.h>
#include <iostream>

namespace dx3d 
{
	//Space Bar - Spawn Shapes
	class SpawnCommand : public Command
	{
	public:
		virtual void execute() {
			std::cout << "SPACE COMMAND FROM COMMAND.H" << std::endl;

		}
	};
}
