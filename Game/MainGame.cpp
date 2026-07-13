#include "MainGame.h"
#include "Objects/Player.h"

MainGame::MainGame(const dx3d::GameDesc& desc) : dx3d::Game(desc)
{

}

void MainGame::onCreate()
{
	Game::onCreate();

	auto& world = getWorld();

	{
		auto basicMat = getResourceManager().createResourceFromFile<dx3d::MaterialResource>(L"Game/Assets/Shaders/Basic.hlsl");
		if (basicMat)
		{
			auto matData = dx3d::Vec3(0.1f, 0.1f, 0.1f);
			basicMat->setData(std::as_bytes(std::span{ &matData, 1 }));
		}

		auto floor = world.createGameObject<dx3d::GameObject>();
		floor->createOrGetComponent<dx3d::CubeComponent>();
		auto comp = floor->createOrGetComponent<dx3d::CubeComponent>();
		comp->setMaterial(basicMat);
		floor->getTransform().setScale({ 6.8f, 0.1f, 6.8f });
		floor->getTransform().setPosition({ 0, -1, 0 });

	}

	srand((unsigned int)time(NULL));

	for (auto y = -2; y < 3; y++)
	{
		for (auto x = -2; x < 3; x++)
		{
			auto basicMat = getResourceManager().createResourceFromFile<dx3d::MaterialResource>(L"Game/Assets/Shaders/Basic.hlsl");
			if (basicMat)
			{
				auto r = (rand() % 255) / 255.0f;
				auto g = (rand() % 255) / 255.0f;
				auto b = (rand() % 255) / 255.0f;
				auto matData = dx3d::Vec3(r, g, b);
				basicMat->setData(std::as_bytes(std::span{ &matData, 1 }));
			}

			auto cube = world.createGameObject<dx3d::GameObject>();
			auto comp = cube->createOrGetComponent<dx3d::CubeComponent>();
			comp->setMaterial(basicMat);
			auto height = (rand() % 120) + (80.0f);
			height /= 100.0f;

			auto width = (rand() % 600) + (200.0f);
			width /= 1000.0f;

			cube->getTransform().setScale({ width, height, width });
			cube->getTransform().setPosition({ x * 1.4f, (height / 2.0f) - 1.0f, y * 1.4f });
		}
	}





	//MODIFIED
	/*for (auto y = -2; y < 3; y++)
	{
		for (auto x = -2; x < 3; x++)
		{
			auto cube = world.createGameObject<dx3d::GameObject>();
			cube->createOrGetComponent<dx3d::CubeComponent>();
			auto height = (rand() % 120) + (80.0f);
			height /= 100.0f;

			auto width = (rand() % 600) + (200.0f);
			width /= 1000.0f;

			cube->getTransform().setScale({ width, height, width });
			cube->getTransform().setPosition({ x * 0.5f, (height / 2.0f) - 1.0f, y * 0.5f });
		}
	}*/


	auto player = world.createGameObject<Player>();
	player->getTransform().setPosition({ 0, 1, -2 });
	//player->getTransform().setPosition({ 0, 1, -1 });
	//player->getTransform().setPosition({ 0, 1, -1 });


	//getInputSystem().setCursorLocked(true);
	//getInputSystem().setCursorVisible(false);
}

void MainGame::onUpdate(dx3d::f32 deltaTime)
{
	Game::onUpdate(deltaTime);
}