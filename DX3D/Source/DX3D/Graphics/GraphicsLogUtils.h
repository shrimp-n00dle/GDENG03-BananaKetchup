#pragma once
#include <DX3D/Core/Logger.h>


namespace dx3d
{
#define DX3DGraphicsLogErrorAndThrow(hr,message)\
	{\
		auto res = (hr);\
	if(FAILED(hr))\
		DX3DLogErrorAndThrow(message);\
	}
}