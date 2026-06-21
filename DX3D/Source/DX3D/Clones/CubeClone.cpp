#include <DX3D/Clones/CubeClone.h>

CubeClone::CubeClone(const dx3d::GameObjectDesc& desc) : dx3d::GameObject(desc)
{
}

CubeClone::~CubeClone()
{
}

void CubeClone::onCreate()
{
	auto& world = getWorld();

	srand((unsigned int)time(NULL));

	auto cube = world.createGameObject<dx3d::GameObject>();
	cube->createOrGetComponent<dx3d::CubeComponent>();
	auto height = (rand() % 120) + (80.0f);
	height /= 100.0f;

	auto width = (rand() % 600) + (200.0f);
	width /= 1000.0f;

	cube->getTransform().setScale({ width, height, width });
	cube->getTransform().setPosition({ x * 0.5f, (height / 2.0f) - 1.0f, y * 0.5f });
}

void CubeClone::onUpdate(dx3d::f32 deltaTime)
{
}