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
#include <DirectXMath.h>

#include <iostream>

using namespace dx3d;



namespace catsup
{

	struct copyData {
		DirectX::XMFLOAT3 newPos;
	};

	class Spawner final : public Base
	{
	public:
		explicit Spawner(const SpawnerDesc& desc);
		virtual ~Spawner() override;

		VertexBufferPtr bakeShapes(int index, RenderSystem& device, std::vector<VertexBufferPtr> indexList,
			DeviceContext& context);
		void decoShapes(VertexBufferPtr vb,DeviceContext& context, std::vector<VertexBufferPtr> indexList);
		void addBuffer(VertexBufferPtr m_vb);

	public:

		//list of vertex buffers
		std::vector<VertexBufferPtr> bufferList;
		VertexBufferPtr originalCopy{}, cloneCopy{};
	};
}
