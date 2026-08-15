

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


	//SPHERE
	/*for (auto y = -2; y < 3; y++)
	{
		for (auto x = -2; x < 3; x++)
		{
	auto sphere = world.createGameObject<PhysicsObject>();
	sphere->createOrGetComponent<dx3d::SphereComponent>();
	sphere->objName = "Sphere";
	sphere->isPhysics = true;
	auto comp = sphere->createOrGetComponent<dx3d::SphereComponent>();
	comp->setMaterial(basicMat);
	sphere->getTransform().setScale({ 2.0f, 2.0f, 2.0f });
	sphere->getTransform().setPosition({ x * 1.2f, 20, y * 1.2f });
	sphere->initializePhysicsObject(false);

		}
	}

	auto floor = world.createGameObject<PhysicsObject>();
	floor->createOrGetComponent<dx3d::CubeComponent>();
	floor->objName = "Cube";
	floor->isPhysics = true;
	auto comp2 = floor->createOrGetComponent<dx3d::CubeComponent>();
	comp2->setMaterial(basicMat);
	floor->getTransform().setScale({ 60.8f, 0.1f, 60.8f });
	floor->getTransform().setPosition({5, 0, -5 }); 
	floor->initializePhysicsObject(true);*/



	//CAPSULE
	/*auto capsule = world.createGameObject<dx3d::GameObject>();
	capsule->createOrGetComponent<dx3d::CapsuleComponent>();
	capsule->objName = "Capsule";
	auto comp = capsule->createOrGetComponent<dx3d::CapsuleComponent>();
	comp->setMaterial(basicMat);
	capsule->getTransform().setScale({ 1.0f, 1.0f, 1.0f });
	capsule->getTransform().setPosition({ 2, 0, 0 });*/


	//ONE CUBE
	//auto cube = world.createGameObject<dx3d::GameObject>();
	//cube->createOrGetComponent<dx3d::CubeComponent>();
	//cube->objName = "Cube";
	//auto comp = cube->createOrGetComponent<dx3d::CubeComponent>();
	//comp->setMaterial(basicMat);
	//cube->getTransform().setScale({ 1.0f, 1.0f, 1.0f });
	//cube->getTransform().setPosition({ 0, 0.9, 0 });

	////ONE CUBE
	//auto cube2 = world.createGameObject<dx3d::GameObject>();
	//cube2->createOrGetComponent<dx3d::CubeComponent>();
	//cube2->objName = "Cube";
	//auto comp2 = cube2->createOrGetComponent<dx3d::CubeComponent>();
	//comp2->setMaterial(basicMat);
	//cube2->getTransform().setScale({ 1.0f, 1.0f, 1.0f });
	//cube2->getTransform().setPosition({ -1.5, 2.0, 0 });

	////ONE CUBE
	//auto cube3 = world.createGameObject<dx3d::GameObject>();
	//cube3->createOrGetComponent<dx3d::CubeComponent>();
	//cube3->objName = "Cube";
	//auto comp3 = cube3->createOrGetComponent<dx3d::CubeComponent>();
	//comp3->setMaterial(basicMat);
	//cube3->getTransform().setScale({ 1.0f, 1.0f, 1.0f });
	//cube3->getTransform().setPosition({ -1.5, 3.0, -2.0 });



	//CUBE
	/*int cubeCount = 0;
	for (auto y = -2; y < 3; y++)
	{
		for (auto x = -2; x < 3; x++)
		{
			auto cube = world.createGameObject<dx3d::GameObject>();
			cube->createOrGetComponent<dx3d::CubeComponent>();
			cube->objName = "Cube";
			auto height = (rand() % 120) + (80.0f);
			height /= 100.0f;

			auto width = (rand() % 600) + (200.0f);
			width /= 1000.0f;

			auto comp = cube->createOrGetComponent<dx3d::CubeComponent>();
			comp->setMaterial(basicMat);
			cube->getTransform().setScale({ width, height, width });
			cube->getTransform().setPosition({ x * 1.4f, (height / 2.0f) - 1.0f, y * 1.4f });
			cubeCount++;
		}
	}*/


	//std::cout << "THERE ARE " << cubeCount << "cubes" << std::endl;




	//BUNNY
	//PHYSICS OBJECT
	//for (int i = 0; i < 20; i++)
	//{
	//	auto bunny = world.createGameObject<PhysicsObject>();
	//	auto Bunnycomp = bunny->createOrGetComponent<dx3d::MeshComponent>();
	//	Bunnycomp->setMaterial(basicMat);
	//	Bunnycomp->assignMesh(bunnyMesh->getMesh());
	//	auto rotyBunny = (rand() % 628) / 100.0f;
	//	bunny->getTransform().setScale({ 5,5,5 });
	//	bunny->getTransform().setPosition({ 2,0,0 });
	//	bunny->getTransform().setRotation({ 0,rotyBunny,0 });

	//}



	//TEAPOT
	//auto teapot = world.createGameObject<PhysicsObject>();
	//teapot->getTransform().setPosition({ 2, 0,0 });
	//auto Teapotcomp = teapot->createOrGetComponent<dx3d::MeshComponent>();
	//Teapotcomp->setMaterial(brickMat);
	//Teapotcomp->assignMesh(teapotMesh->getMesh());
	//auto rotyTeaPot = (rand() % 628) / 100.0f;
	//teapot->getTransform().setScale({ 6.8,1,6.8 });
	//teapot->getTransform().setRotation({ 0,rotyTeaPot,0 });
	//teapot->initializePhysicsObject(true);

	//ARMADILLO
	/*auto arma = world.createGameObject<dx3d::GameObject>();
	auto Armacomp = arma->createOrGetComponent<dx3d::MeshComponent>();
	Armacomp->setMaterial(basicMat);
	Armacomp->assignMesh(armaMesh->getMesh());
	auto rotyArma = (rand() % 628) / 100.0f;
	arma->getTransform().setScale({ 0.2,0.2,0.2 });
	arma->getTransform().setPosition({ 3, 0,0 });
	arma->getTransform().setRotation({ 0,rotyArma,0 });*/

	{
		auto basicMat = getResourceManager().createResourceFromFile<dx3d::MaterialResource>(L"Game/Assets/Shaders/Basic.hlsl");
		if (basicMat)
		{
			auto matData = dx3d::Vec3(1, 1, 1);
			basicMat->setData(std::as_bytes(std::span{ &matData, 1 }));
			basicMat->setTexture(0, floorTex);
		}

	/*	auto floor = world.createGameObject<dx3d::GameObject>();
		floor->createOrGetComponent<dx3d::CubeComponent>();
		auto comp = floor->createOrGetComponent<dx3d::CubeComponent>();
		comp->setMaterial(basicMat);
		floor->getTransform().setScale({ 12.8f, 0.1f, 12.8f });
		floor->getTransform().setPosition({ 2, 0, -5 });*/
		//floor->initializePhysicsObject(true);
		
	}

	srand((unsigned int)time(NULL));

	auto player = world.createGameObject<Player>();
	player->objName = "Main Camera";
	player->getTransform().setPosition({ 0, 1, -2});

	//getInputSystem().setCursorLocked(true);
	//getInputSystem().setCursorVisible(false);
}


void MainGame::onUpdate(dx3d::f32 deltaTime)
{
	Game::onUpdate(deltaTime);
}
