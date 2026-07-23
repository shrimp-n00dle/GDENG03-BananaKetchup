#include <DX3D/Component/MeshComponent.h>
#include <DX3D/Game/World.h>
#include <DX3D/Math/Vec3.h>
#include <DX3D/Math/Vec2.h>
#include <DX3D/Math/Mat4x4.h>
#include <DX3D/Graphics/GraphicsDevice.h>





dx3d::MeshComponent::MeshComponent(const ComponentDesc& data) : Component(data)
{

  
}

void dx3d::MeshComponent::setMaterial(const RefPtr<MaterialResource>& material)
{
	m_material = material;
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
