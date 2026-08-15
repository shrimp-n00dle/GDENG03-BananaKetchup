#pragma once
#include <DX3D/Resource/Resource.h>

#include <DX3D/Graphics/VertexBuffer.h>
#include <DX3D/Graphics/IndexBuffer.h>
#include <DX3D/Graphics/MeshBuffer.h>

namespace dx3d
{
	class MeshResource : public Resource
	{
	public:
		//MeshResource(const wchar_t* path);
		explicit MeshResource(const MeshResourceDesc& desc);
		//explicit MeshResource(const MeshResourceDesc& desc);
		RefPtr<MeshBuffer> getMesh() const {return m_mesh_buffer;};

	private:
		RefPtr<VertexBuffer> m_vertex_buffer{};
		RefPtr<IndexBuffer> m_index_buffer{};
		RefPtr<MeshBuffer> m_mesh_buffer;
	};
}
