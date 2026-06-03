#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Core/Base.h>
#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Math/Vertex.h>
#include <list>

#include <iostream>

using namespace dx3d;

namespace catsup
{
	class Spawner final : public Base
	{
	public:
		explicit Spawner(const SpawnerDesc& desc);
		virtual ~Spawner() override;

		void bakeShapes(int index);

	private:
		//Each QUAD

		//Has a list of the vertices and colors
		std::list<Vertex> objlist;

		//list of vertex buffers
		std::list<VertexBufferPtr> bufferList;

	};
}
