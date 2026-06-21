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
		//virtual void undo() = 0;
	};
}


