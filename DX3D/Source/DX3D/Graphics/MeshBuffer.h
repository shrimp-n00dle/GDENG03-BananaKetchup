#pragma once
#include <DX3D/Graphics/GraphicsResource.h>
#include <vector>

namespace dx3d
{
	class MeshBuffer final : public GraphicsResource
	{
	public:
		MeshBuffer(const MeshBufferDesc& desc, const GraphicsResourceDesc& gDesc);

		const Vertex* getVertices() const noexcept;
		ui32 getVertexCount() const noexcept;

		const ui32* getIndices() const noexcept;
		ui32 getIndexCount() const noexcept;


	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer{};

		//Vertices
		std::vector<Vertex> m_vertices;
		//Indices
		std::vector<ui32> m_indices;


		friend class DeviceContext;
	};
}

