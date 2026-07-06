#include <DX3D/Component/CubeComponent.h>
#include <DX3D/Game/World.h>

dx3d::CubeComponent::CubeComponent(const ComponentDesc& data) : Component(data)
{
}

void dx3d::CubeComponent::setMaterial(const RefPtr<MaterialResource>& material)
{
	m_material = material;
}

dx3d::MaterialResource* dx3d::CubeComponent::getMaterial()
{
	return m_material.get();
}