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
	floor->getTransform().setScale({ 6.8f, 0.1f, 6.8f });
	floor->getTransform().setPosition({ 0, -1, 0 });

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


	//FOR LOOP FOR CUBES (TOTAL HERE IS 49)
		for (auto y = -2; y < 5; y++)
	{
		for (auto x = -2; x < 5; x++)
		{
			auto cube = world.createGameObject<dx3d::GameObject>();
			cube->createOrGetComponent<dx3d::CubeComponent>();
			auto height = (rand() % 120) + (80.0f);
			height /= 100.0f;

			auto width = (rand() % 600) + (200.0f);
			width /= 1000.0f;

			cube->getTransform().setScale({0.5,0.5,0.5});
			cube->getTransform().setPosition({ x * 1.4f, (height / 2.0f) - 1.0f, y * 1.4f });
			m_objects[CubeCount] = cube;
			CubeCount++;
		}
	}
		

	//ADDED ONE MORE CUBE (SO ITS 50 NOW)
			auto cube = world.createGameObject<dx3d::GameObject>();
			cube->createOrGetComponent<dx3d::CubeComponent>();
			auto height = (rand() % 120) + (80.0f);
			height /= 100.0f;

			auto width = (rand() % 600) + (200.0f);
			width /= 1000.0f;

			cube->getTransform().setScale({ 0.5,0.5,0.5 });
			cube->getTransform().setPosition({ -1 * 1.4f, (height / 2.0f) - 1.0f, -3 * 1.4f });
			m_objects[49] = cube;
			CubeCount++;
			std::cout << "CUBE COUNT IS " << CubeCount << std::endl;


	//MODIFIED Planes
	for (auto y = -2; y < 3; y++)
	{
		for (auto x = -2; x < 3; x++)
		{
			auto cube = world.createGameObject<dx3d::GameObject>();
			cube->createOrGetComponent<dx3d::PlaneComponent>();
			auto height = (rand() % 120) + (80.0f);
			height /= 100.0f;

			auto width = (rand() % 600) + (200.0f);
			width /= 1000.0f;

			cube->getTransform().setScale({ width, height, width });
			cube->getTransform().setPosition({ x * 0.5f, -0.8, y * 0.5f });
		}
	}

	auto player = world.createGameObject<Player>();
	player->getTransform().setPosition({ -0.66, -0.397, -3/*-2.736*/});


	getInputSystem().setCursorLocked(true);
	getInputSystem().setCursorVisible(false);
}

void MainGame::onUpdate(dx3d::f32 deltaTime)
{
	Game::onUpdate(deltaTime);

	m_rot += deltaTime * 0.707f;
	////m_scale = std::abs(std::sin(m_rot));
	//m_scale = 0.5f;

	for (auto i = 0; i < 50; i++)
	{
		m_objects[i]->getTransform().setRotation({ m_rot * i, m_rot, m_rot * i });
		//m_objects[i]->getTransform().setScale({ m_scale,m_scale,m_scale });
	}

}