#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Math/Vec3.h>
#include <DX3D/Math/Vec4.h>
namespace dx3d 
{
	//MUST BE EXACT TO BASIC.HLSL or it wont work
	struct Vertex
	{
		Vec3 position;
		Vec4 color;
		float time;
	};
}
