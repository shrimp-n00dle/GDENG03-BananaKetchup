

#include "MainGame.h"
#include "Objects/Player.h"


MainGame::MainGame(const dx3d::GameDesc& desc) : dx3d::Game(desc)
{
}

void MainGame::onCreate()
{
	Game::onCreate();
	auto& world = getWorld();
	auto woodTex = getResourceManager().createResourceFromFile<dx3d::TextureResource>(L"Game/Assets/Textures/wood.jpg");
	auto floorTex = getResourceManager().createResourceFromFile<dx3d::TextureResource>(L"Game/Assets/Textures/floor.jpg");
	auto brickTex = getResourceManager().createResourceFromFile<dx3d::TextureResource>(L"Game/Assets/Textures/brick.jpg");
	auto logoTex = getResourceManager().createResourceFromFile<dx3d::TextureResource>(L"Game/Assets/Textures/floor.jpg");
	aboutWin->setUpImage(logoTex);

	auto bunnyMesh = getResourceManager().createResourceFromFile<dx3d::MeshResource>(L"Game/Assets/Models/bunny.obj");
	auto teapotMesh = getResourceManager().createResourceFromFile<dx3d::MeshResource>(L"Game/Assets/Models/teapot.obj");
	auto armaMesh = getResourceManager().createResourceFromFile<dx3d::MeshResource>(L"Game/Assets/Models/armadillo.obj");

	auto basicMat = getResourceManager().createResourceFromFile<dx3d::MaterialResource>(L"Game/Assets/Shaders/Basic.hlsl");
	if (basicMat)
	{
		auto matData = dx3d::Vec3(1, 1, 1);
		basicMat->setData(std::as_bytes(std::span{ &matData, 1 }));
		basicMat->setTexture(0, woodTex);
	}

	auto brickMat = getResourceManager().createResourceFromFile<dx3d::MaterialResource>(L"Game/Assets/Shaders/Basic.hlsl");
	if (basicMat)
	{
		auto matData = dx3d::Vec3(1, 1, 1);
		brickMat->setData(std::as_bytes(std::span{ &matData, 1 }));
		brickMat->setTexture(0, brickTex);
	}

	//BUNNY
	auto bunny = world.createGameObject<MeshObject>();
	auto Bunnycomp = bunny->createOrGetComponent<dx3d::MeshComponent>();
	Bunnycomp->setMaterial(basicMat);
	Bunnycomp->assignMesh(bunnyMesh->getMesh());
	auto rotyBunny = (rand() % 628) / 100.0f;
	bunny->getTransform().setScale({ 5,5,5 });
	bunny->getTransform().setPosition({2,0,0});
	bunny->getTransform().setRotation({ 0,rotyBunny,0 });


	//TEAPOT
	auto teapot = world.createGameObject<MeshObject>();
	auto Teapotcomp = teapot->createOrGetComponent<dx3d::MeshComponent>();
	Teapotcomp->setMaterial(brickMat);
	Teapotcomp->assignMesh(teapotMesh->getMesh());
	auto rotyTeaPot = (rand() % 628) / 100.0f;
	teapot->getTransform().setScale({ 1,1,1 });
	teapot->getTransform().setPosition({ 1, 0,0 });
	teapot->getTransform().setRotation({ 0,rotyTeaPot,0 });

	//ARMADILLO
	auto arma = world.createGameObject<MeshObject>();
	auto Armacomp = arma->createOrGetComponent<dx3d::MeshComponent>();
	Armacomp->setMaterial(basicMat);
	Armacomp->assignMesh(armaMesh->getMesh());
	auto rotyArma = (rand() % 628) / 100.0f;
	arma->getTransform().setScale({ 0.2,0.2,0.2 });
	arma->getTransform().setPosition({ 3, 0,0 });
	arma->getTransform().setRotation({ 0,rotyArma,0 });

	/*{
		auto basicMat = getResourceManager().createResourceFromFile<dx3d::MaterialResource>(L"Game/Assets/Shaders/Basic.hlsl");
		if (basicMat)
		{
			auto matData = dx3d::Vec3(1, 1, 1);
			basicMat->setData(std::as_bytes(std::span{ &matData, 1 }));
			basicMat->setTexture(0, floorTex);
		}

		auto floor = world.createGameObject<dx3d::GameObject>();
		floor->createOrGetComponent<dx3d::CubeComponent>();
		auto comp = floor->createOrGetComponent<dx3d::CubeComponent>();
		comp->setMaterial(basicMat);
		floor->getTransform().setScale({ 6.8f, 0.1f, 6.8f });
		floor->getTransform().setPosition({ 0, 0, 0 });
		
	}*/

	srand((unsigned int)time(NULL));

	/*for (auto y = -2; y < 3; y++)
	{
		for (auto x = -2; x < 3; x++)
		{
			auto basicMat = getResourceManager().createResourceFromFile<dx3d::MaterialResource>(L"Game/Assets/Shaders/Basic.hlsl");
			if (basicMat)
			{
				auto matData = dx3d::Vec3(1, 1, 1);
				basicMat->setData(std::as_bytes(std::span{ &matData, 1 }));
				basicMat->setTexture(0, woodTex);
			}

			auto cube = world.createGameObject<dx3d::GameObject>();
			auto comp = cube->createOrGetComponent<dx3d::CubeComponent>();
			comp->setMaterial(basicMat);
			auto roty = (rand() % 628) / 100.0f;
			cube->getTransform().setScale({ 0.5,0.5,0.5 });
			cube->getTransform().setPosition({ x * 1.4f, 0.25f + 0.05f, y * 1.4f });
			cube->getTransform().setRotation({ 0,roty,0 });
		}
	}*/

	//for (auto y = -2; y < 3; y++)
	//{
	//	for (auto x = -2; x < 3; x++)
	//	{
	//		auto basicMat = getResourceManager().createResourceFromFile<dx3d::MaterialResource>(L"Game/Assets/Shaders/Basic.hlsl");
	//		if (basicMat)
	//		{
	//			auto matData = dx3d::Vec3(1, 1, 1);
	//			basicMat->setData(std::as_bytes(std::span{ &matData, 1 }));
	//			basicMat->setTexture(0, woodTex);
	//		}

	//		auto cube = world.createGameObject<dx3d::GameObject>();
	//		auto comp = cube->createOrGetComponent<dx3d::MeshComponent>();
	//		comp->setMaterial(basicMat);
	//		auto roty = (rand() % 628) / 100.0f;
	//		cube->getTransform().setScale({ 0.5,0.5,0.5 });
	//		cube->getTransform().setPosition({ x * 1.4f, 0.25f + 0.05f, y * 1.4f });
	//		cube->getTransform().setRotation({ 0,roty,0 });
	//	}
	//}

	auto player = world.createGameObject<Player>();
	player->getTransform().setPosition({ 0, 1, -2});

	//getInputSystem().setCursorLocked(true);
	//getInputSystem().setCursorVisible(false);
}


void MainGame::onUpdate(dx3d::f32 deltaTime)
{
	Game::onUpdate(deltaTime);
}
