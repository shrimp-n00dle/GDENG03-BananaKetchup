#pragma once
#include <DX3D/All.h>
#include <DX3D/Command/Command.h>
#include <DX3D/Component/CubeComponent.h>

namespace dx3d
{
	class CommandActions : public dx3d::GameObject
	{
		dx3d_typeid(CommandActions);

		GameObject* spawnObject();
		int x = -2;
		int y = -2;
	};
}