#include <DX3D/Graphics/MeshBuffer.h>
#include <DX3D/Graphics/GraphicsUtils.h>

dx3d::MeshBuffer::MeshBuffer(const MeshBufferDesc& desc, const GraphicsResourceDesc& gDesc) : GraphicsResource(gDesc)
{
	m_vertices = desc.verticesList;
	m_indices = desc.indicesList;
}

const dx3d::Vertex* dx3d::MeshBuffer::getVertices() const noexcept
{
	return m_vertices.data();
}

dx3d::ui32 dx3d::MeshBuffer::getVertexCount() const noexcept
{
	return static_cast<ui32>(m_vertices.size());
}

const dx3d::ui32* dx3d::MeshBuffer::getIndices() const noexcept
{
	return  m_indices.data();
}

dx3d::ui32 dx3d::MeshBuffer::getIndexCount() const noexcept
{
	return static_cast<ui32>(m_indices.size());
}
