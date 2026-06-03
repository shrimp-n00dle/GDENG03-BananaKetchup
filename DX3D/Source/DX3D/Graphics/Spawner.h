#pragma once
#include <DX3D/Graphics/GraphicsResource.h>
#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Math/Vec3.h>
#include <DX3D/Math/Vec4.h>
#include <list>

using namespace dx3d;

namespace catsup
{
	class Spawner final : public GraphicsResource
	{
	public:
		explicit Spawner();
		virtual ~Spawner() override;

	private:
		//Each QUAD

		//Has a list of the vertices and colors
		std::list<Vec3> objList;
		std::list<Vec4> colorList;

		//list of vertex buffers
		std::list<VertexBufferPtr> bufferList;

	};
}
