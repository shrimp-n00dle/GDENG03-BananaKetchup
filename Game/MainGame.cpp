#include "MainGame.h"
#include "Objects/Player.h"
#include <DX3D/Clones/CubeClone.h>


MainGame::MainGame(const dx3d::GameDesc& desc) : dx3d::Game(desc)
{
}

void MainGame::onCreate()
{
	Game::onCreate();

	auto& world = getWorld();
	auto floor = world.createGameObject<dx3d::GameObject>();
	floor->createOrGetComponent<dx3d::PlaneComponent>();
	//floor->getTransform().setScale({ 6.8f, 0.1f, 6.8f });
	floor->getTransform().setScale({ 2.0f, 2.0f, 2.0f });
	floor->getTransform().setPosition({ 0, -1, 0 });
	//floor->getTransform().setPosition({ 0, 0,0 });

	srand((unsigned int)time(NULL));

	//for (auto y = -2; y < 3; y++)
	//{
	//	for (auto x = -2; x < 3; x++)
	//	{
	//		auto cube = world.createGameObject<dx3d::GameObject>();
	//		cube->createOrGetComponent<dx3d::CubeComponent>();
	//		auto height = (rand() % 120) + (80.0f);
	//		height /= 100.0f;

	//		auto width = (rand() % 600) + (200.0f);
	//		width /= 1000.0f;

	//		cube->getTransform().setScale({ width, height, width });
	//		cube->getTransform().setPosition({ x * 1.4f, (height / 2.0f) - 1.0f, y * 1.4f });
	//	}
	//}'

	//auto cube = world.createGameObject<dx3d::GameObject>();
	//		cube->createOrGetComponent<dx3d::CubeComponent>();
	//		auto height = (rand() % 15) + (50.0f);
	//		height /= 100.0f;

	//		auto width = (rand() % 60) + (50.0f);
	//		width /= 100.0f;

	//		cube->getTransform().setScale({ width, height, width });
	//		cube->getTransform().setPosition({ -2 * 0.5f, -0.8, -2 });
	//		m_objects[0] = cube;


	//MANUALLY ADDING THE CUBES
	float cube_scale = 0.3f;
	//CUBE 1
	auto cube1 = world.createGameObject<dx3d::GameObject>();
	cube1->createOrGetComponent<dx3d::CubeComponent>();
	auto height1 = (rand() % 120) + (80.0f);
	height1 /= 100.0f;

	auto width1 = (rand() % 600) + (200.0f);
	width1 /= 1000.0f;

	cube1->getTransform().setScale({ cube_scale,cube_scale,cube_scale });
	//cube1->getTransform().setPosition({ 0, 0.9,0 });
	cube1->getTransform().setPosition({ -0.3,-0.5,0.5 });
	m_objects[CubeCount] = cube1;
	CubeCount++;


	//CUBE 2
	auto cube2 = world.createGameObject<dx3d::GameObject>();
	cube2->createOrGetComponent<dx3d::CubeComponent>();
	auto height2 = (rand() % 120) + (80.0f);
	height2 /= 100.0f;

	auto width2 = (rand() % 600) + (200.0f);
	width2 /= 1000.0f;

	cube2->getTransform().setScale({ cube_scale,cube_scale,cube_scale });
	cube2->getTransform().setPosition({-0.7,-0.3,0.5 });
	m_objects[CubeCount] = cube2;
	CubeCount++;


	//CUBE 3
	auto cube3 = world.createGameObject<dx3d::GameObject>();
	cube3->createOrGetComponent<dx3d::CubeComponent>();
	auto height3 = (rand() % 120) + (80.0f);
	height3 /= 100.0f;

	auto width3 = (rand() % 600) + (200.0f);
	width3 /= 1000.0f;

	cube3->getTransform().setScale({ cube_scale,cube_scale,cube_scale });
	cube3->getTransform().setPosition({ -0.7,0,0});
	m_objects[CubeCount] = cube3;
	CubeCount++;

	std::cout << "CUBE COUNT IS " << CubeCount << std::endl;



	auto player = world.createGameObject<Player>();
	//player->getTransform().setPosition({ -0.66, -0.397, -3/*-2.736*/});
	//player->getTransform().setPosition({ 0, 0, -1});
	player->getTransform().setPosition({ -0.46, -0.12, 0.05 });
	player->getTransform().setRotation({ 0.69, -1.546, 0.00 });



	getInputSystem().setCursorLocked(true);
	getInputSystem().setCursorVisible(false);
}

void MainGame::onUpdate(dx3d::f32 deltaTime)
{
	Game::onUpdate(deltaTime);

}