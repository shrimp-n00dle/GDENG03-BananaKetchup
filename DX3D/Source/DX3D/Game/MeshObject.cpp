#include <DX3D/Game/MeshObject.h>
MeshObject::MeshObject(const dx3d::GameObjectDesc& desc) : dx3d::GameObject(desc)
{
}

MeshObject::~MeshObject()
{
}

dx3d::Vec3 MeshObject::getScale()
{
	return { meshScale,meshScale,meshScale };
}

void MeshObject::onCreate()
{
	createOrGetComponent<dx3d::MeshComponent>();
}

void MeshObject::onUpdate(dx3d::f32 deltaTime)
{
	auto& input = getInputSystem();

	//UP DOWN
	if (getInputSystem().isKeyDown(dx3d::KeyCode::J)) meshScale += 0.01f;
	if (getInputSystem().isKeyDown(dx3d::KeyCode::L)) meshScale += -0.01f;

	getTransform().setScale({meshScale,meshScale,meshScale});
}
