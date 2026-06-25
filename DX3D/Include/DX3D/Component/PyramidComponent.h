#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Game/Component.h>
#include <DX3D/Math/Vec3.h>
#include <DX3D/Math/Mat4x4.h>


namespace dx3d
{
	class PyramidComponent final : public Component
	{
		dx3d_typeid(PyramidComponent)
	public:
		explicit PyramidComponent(const ComponentDesc& data);
	};
}
