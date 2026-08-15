#include <DX3D/Component/MeshComponent.h>
#include <DX3D/Game/World.h>
#include <DX3D/Math/Vec3.h>
#include <DX3D/Math/Vec2.h>
#include <DX3D/Math/Mat4x4.h>
#include <DX3D/Graphics/GraphicsDevice.h>


dx3d::MeshComponent::MeshComponent(const ComponentDesc& data) : Component(data), input(data.object.getInputSystem())
	,modelScale(data.object.getTransform())
{
}

void dx3d::MeshComponent::setMaterial(const RefPtr<MaterialResource>& material)
{
	m_material = material;
}

dx3d::RefPtr<dx3d::VertexBuffer> dx3d::MeshComponent::callVertexBuffer(GraphicsDevice& _device)
{
	if (!m_vb)
	{
		m_vb = _device.createVertexBuffer({
			m_mesh->getVertices(),
			m_mesh->getVertexCount(),
			sizeof(Vertex)
			});
	}

	return m_vb;
}

dx3d::RefPtr<dx3d::IndexBuffer> dx3d::MeshComponent::callIndexBuffer(GraphicsDevice& _device)
{
	if (!m_ib)
	{
		m_ib = _device.createIndexBuffer({
			m_mesh->getIndices(),
			m_mesh->getIndexCount()
			});
	}

	return m_ib;
}

void dx3d::MeshComponent::assignMesh(const RefPtr<MeshBuffer>& mesh) noexcept
{
	m_mesh = mesh;
}

dx3d::MaterialResource* dx3d::MeshComponent::getMaterial()
{
	return m_material.get();
}

dx3d::VertexBuffer& dx3d::MeshComponent::getVertexBuffer()
{
	return *m_vb;
}

dx3d::IndexBuffer& dx3d::MeshComponent::getIndexBuffer()
{
	return *m_ib;
}