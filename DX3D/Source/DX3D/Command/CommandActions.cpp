#include <DX3D/Command/CommandActions.h>

dx3d::GameObject* dx3d::CommandActions::spawnObject()
{
	auto& world = getWorld();
	auto cube = world.createGameObject<dx3d::GameObject>();
	cube->createOrGetComponent<dx3d::CubeComponent>();
	auto height = (rand() % 120) + (80.0f);
	height /= 100.0f;

	auto width = (rand() % 600) + (200.0f);
	width /= 1000.0f;

	cube->getTransform().setScale({ width, height, width });
	cube->getTransform().setPosition({ x * 1.4f, (height / 2.0f) - 1.0f, y * 1.4f });

	//Increment
	x++;
	y++;

	return cube;
}
