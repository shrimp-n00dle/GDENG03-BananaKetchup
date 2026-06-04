#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Core/Base.h>
#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/RenderSystem.h>
#include <DX3D/Math/Vertex.h>
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/VertexBuffer.h>
#include <list>
#include <vector> // Required header

#include <iostream>

using namespace dx3d;

namespace catsup
{
	class Spawner final : public Base
	{
	public:
		explicit Spawner(const SpawnerDesc& desc);
		virtual ~Spawner() override;

		void bakeShapes(int index, RenderSystem& device);
		void decoShapes(DeviceContext& context);
		void addBuffer(VertexBufferPtr m_vb);
		VertexBufferPtr getList();


		//bool b

	private:
		//Each QUAD

		//Has a list of the vertices and colors
		std::list<Vertex> objlist;

		//list of vertex buffers
		std::vector<VertexBufferPtr> bufferList;
		VertexBufferPtr originalCopy{};
	};
}
