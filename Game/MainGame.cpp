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


	srand((unsigned int)time(NULL));


	//MANUALLY ADDING THE CARDS 
	float shape_scale = 0.2f;
	float rotation_value = 8.22f;
	//CARD1
	auto plane = world.createGameObject<dx3d::GameObject>();
	plane ->createOrGetComponent<dx3d::PlaneComponent>();

	plane->getTransform().setScale({shape_scale +0.2f,shape_scale,shape_scale+0.2f});
	plane->getTransform().setPosition({ 0, 0, 0 });
	plane->getTransform().setRotation({ rotation_value, 1, 0 });
	CubeCount++;

	//CARD2
	auto plane2 = world.createGameObject<dx3d::GameObject>();
	plane2->createOrGetComponent<dx3d::PlaneComponent>();
	plane2->getTransform().setScale({ shape_scale + 0.2f,shape_scale,shape_scale + 0.2f });
	plane2->getTransform().setPosition({ 0.1, 0, 0.1 });
	plane2->getTransform().setRotation({ -rotation_value,1, 0 });
	CubeCount++;

	//CARD3
	auto plane3 = world.createGameObject<dx3d::GameObject>();
	plane3->createOrGetComponent<dx3d::PlaneComponent>();
	plane3->getTransform().setScale({ shape_scale + 0.2f,shape_scale,shape_scale + 0.2f });
	plane3->getTransform().setPosition({0.2, 0, 0.2 });
	plane3->getTransform().setRotation({ rotation_value, 1, 0 });
	CubeCount++;

	//CARD4
	auto plane4 = world.createGameObject<dx3d::GameObject>();
	plane4->createOrGetComponent<dx3d::PlaneComponent>();
	plane4->getTransform().setScale({ shape_scale + 0.2f,shape_scale,shape_scale + 0.2f });
	plane4->getTransform().setPosition({ 0.3, 0, 0.3 });
	plane4->getTransform().setRotation({ -rotation_value, 1, 0 });
	CubeCount++;

	//CARD5
	auto plane5 = world.createGameObject<dx3d::GameObject>();
	plane5->createOrGetComponent<dx3d::PlaneComponent>();
	plane5->getTransform().setScale({ shape_scale + 0.2f,shape_scale,shape_scale + 0.2f });
	plane5->getTransform().setPosition({ 0.4, 0, 0.4 });
	plane5->getTransform().setRotation({ rotation_value, 1, 0 });
	CubeCount++;


	//CARD6
	auto plane6 = world.createGameObject<dx3d::GameObject>();
	plane6->createOrGetComponent<dx3d::PlaneComponent>();
	plane6->getTransform().setScale({ shape_scale + 0.2f,shape_scale,shape_scale + 0.2f });
	plane6->getTransform().setPosition({ 0.5, 0, 0.5 });
	plane6->getTransform().setRotation({ -rotation_value, 1, 0 });
	CubeCount++;

	//SECOND LAYER
	auto plane7 = world.createGameObject<dx3d::GameObject>();
	plane7->createOrGetComponent<dx3d::PlaneComponent>();
	plane7->getTransform().setScale({ shape_scale + 0.15f,shape_scale,shape_scale+0.2f});
	plane7->getTransform().setPosition({ 0.13, 0.2, 0.13 });
	plane7->getTransform().setRotation({ 0, 2.5, 0 });
	CubeCount++;
	auto plane8 = world.createGameObject<dx3d::GameObject>();
	plane8->createOrGetComponent<dx3d::PlaneComponent>();
	plane8->getTransform().setScale({ shape_scale + 0.15f,shape_scale,shape_scale +0.2f});
	plane8->getTransform().setPosition({ 0.38, 0.2, 0.38 });
	plane8->getTransform().setRotation({ 0, 2.5, 0 });
	CubeCount++;

	//CARD9
	auto plane9 = world.createGameObject<dx3d::GameObject>();
	plane9->createOrGetComponent<dx3d::PlaneComponent>();
	plane9->getTransform().setScale({ shape_scale + 0.2f,shape_scale,shape_scale + 0.2f });
	plane9->getTransform().setPosition({ 0.1, 0.4, 0.1 });
	plane9->getTransform().setRotation({ rotation_value, 0.9, 0 });
	CubeCount++;

	//CARD10
	auto plane10 = world.createGameObject<dx3d::GameObject>();
	plane10->createOrGetComponent<dx3d::PlaneComponent>();
	plane10->getTransform().setScale({ shape_scale + 0.2f,shape_scale,shape_scale + 0.2f });
	plane10->getTransform().setPosition({ 0.2, 0.4, 0.2 });
	plane10->getTransform().setRotation({ -rotation_value, 0.9, 0 });
	CubeCount++;

	//CARD11
	auto plane11 = world.createGameObject<dx3d::GameObject>();
	plane11->createOrGetComponent<dx3d::PlaneComponent>();
	plane11->getTransform().setScale({ shape_scale + 0.2f,shape_scale,shape_scale + 0.2f });
	plane11->getTransform().setPosition({ 0.3, 0.4, 0.3 });
	plane11->getTransform().setRotation({ rotation_value, 0.9, 0 });
	CubeCount++;

	//CARD12
	auto plane12 = world.createGameObject<dx3d::GameObject>();
	plane12->createOrGetComponent<dx3d::PlaneComponent>();
	plane12->getTransform().setScale({ shape_scale + 0.2f,shape_scale,shape_scale + 0.2f });
	plane12->getTransform().setPosition({ 0.4, 0.4, 0.4 });
	plane12->getTransform().setRotation({ -rotation_value, 0.9, 0 });
	CubeCount++;

	//LAST LAYER
	auto plane13 = world.createGameObject<dx3d::GameObject>();
	plane13->createOrGetComponent<dx3d::PlaneComponent>();
	plane13->getTransform().setScale({ shape_scale + 0.15f,shape_scale,shape_scale + 0.15f });
	plane13->getTransform().setPosition({ 0.25, 0.6, 0.25 });
	plane13->getTransform().setRotation({ 0, 0.9, 0 });
	CubeCount++;

	//CARD14
	auto plane14 = world.createGameObject<dx3d::GameObject>();
	plane14->createOrGetComponent<dx3d::PlaneComponent>();
	plane14->getTransform().setScale({ shape_scale + 0.2f,shape_scale,shape_scale + 0.2f });
	plane14->getTransform().setPosition({ 0.2, 0.8, 0.2 });
	plane14->getTransform().setRotation({ rotation_value, 0.9, 0 });
	CubeCount++;

	//CARD15
	auto plane15 = world.createGameObject<dx3d::GameObject>();
	plane15->createOrGetComponent<dx3d::PlaneComponent>();
	plane15->getTransform().setScale({ shape_scale + 0.2f,shape_scale,shape_scale + 0.2f });
	plane15->getTransform().setPosition({ 0.3, 0.8, 0.3 });
	plane15->getTransform().setRotation({ -rotation_value, 0.9, 0 });
	CubeCount++;


	std::cout << "TOTAL NUMBER OF CARDS IS " << CubeCount << std::endl;

	auto player = world.createGameObject<Player>();
	player->getTransform().setPosition({ -0.39, 0.60,0.21 });
	//player->getTransform().setRotation({1.253,-1.423,0});
	player->getTransform().setRotation({ 0.502,2.547,0 });


	getInputSystem().setCursorLocked(true);
	getInputSystem().setCursorVisible(false);
}

void MainGame::onUpdate(dx3d::f32 deltaTime)
{
	Game::onUpdate(deltaTime);

}