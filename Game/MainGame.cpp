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

	//RAINDBOW CUBE
	float shape_scale = 0.5f;
	auto cube = world.createGameObject<dx3d::GameObject>();
	cube->createOrGetComponent<dx3d::CubeComponent>();
	auto height = (rand() % 15) + (50.0f);
	height /= 100.0f;

	auto width = (rand() % 60) + (50.0f);
	width /= 100.0f;

	cube->getTransform().setScale({ shape_scale, shape_scale, shape_scale });
	cube->getTransform().setPosition({ -2 * 0.5f, -0.8, -2 });
	m_objects[0] = cube;




	auto player = world.createGameObject<Player>();
	player->getTransform().setPosition({ -0.66, -0.397, -2.736 });


	getInputSystem().setCursorLocked(true);
	getInputSystem().setCursorVisible(false);
}

void MainGame::onUpdate(dx3d::f32 deltaTime)
{
	Game::onUpdate(deltaTime);

	for (auto i = 0; i < 9; i++)
	{
		m_objects[0]->getTransform().setScale({ m_scale_x,m_scale_y,m_scale_z });
	}

}