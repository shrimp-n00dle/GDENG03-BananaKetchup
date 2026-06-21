#include "Player.h"
#include <iostream>


Player::Player(const dx3d::GameObjectDesc& desc) : dx3d::GameObject(desc)
{
}

Player::~Player()
{
}

Player* Player::getPlayer()
{
	return this;
}

const void Player::test()
{
	std::cout << "WORKING" << std::endl;
}

dx3d::GameObject* Player::spawnCube()
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

void Player::onCreate()
{
	createOrGetComponent<dx3d::CameraComponent>();
}

void Player::onUpdate(dx3d::f32 deltaTime)
{
	auto& input = getInputSystem();


	auto sensitivity = 0.001f;
	auto rot = getTransform().getRotation();
	rot.x += getInputSystem().getMouseDelta().y * sensitivity;
	rot.y += getInputSystem().getMouseDelta().x * sensitivity;
	if (rot.x > 1.57f) rot.x = 1.57f;
	else if (rot.x < -1.57f) rot.x = -1.57f;
	getTransform().setRotation(rot);


	auto pos = getTransform().getPosition();
	auto forward = 0.0f;
	auto right = 0.0f;
	auto speed = 3.0f;
	if (getInputSystem().isKeyDown(dx3d::KeyCode::W)) forward = 1.0f;
	if (getInputSystem().isKeyDown(dx3d::KeyCode::S)) forward = -1.0f;
	if (getInputSystem().isKeyDown(dx3d::KeyCode::D)) right = 1.0f;
	if (getInputSystem().isKeyDown(dx3d::KeyCode::A)) right = -1.0f;

	//Handlw Seatwork Commands
	dx3d::Command* command = getInputSystem().handleInput();
	if (command)
	{
		Player* p = getPlayer();
		Player& p2 = *p;
		command->execute(p2);
	}


	auto forwardDir = getTransform().forward() * forward;
	auto rightDir = getTransform().right() * right;
	auto direction = dx3d::Vec3::normalize(forwardDir + rightDir);
	pos = pos + direction * speed * deltaTime;
	getTransform().setPosition(pos);
}