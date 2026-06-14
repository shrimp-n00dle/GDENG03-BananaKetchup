#include <DX3D/Game/Game.h>
#include <DX3D/Window/Window.h>
#include <DX3D/Graphics/RenderSystem.h>
#include <DX3D/Core/Logger.h>
#include <DX3D/Input/InputSystem.h>
#include <DX3D/Game/Display.h>
#include <DX3D/Game/World.h>
#include <DX3D/Game/GameObject.h>
#include <DX3D/Graphics/GraphicsEngine.h>
#include <iostream>

dx3d::Game::Game(const GameDesc& desc)
{
	m_logger = std::make_unique<Logger>(desc.logLevel);

	std::clog << "BananaCatsup V 1.0" << "\n";
	std::clog << "--------------------------------------" << "\n";

	m_inputSystem = std::make_unique<InputSystem>(InputSystemDesc{ *m_logger });
	m_renderSystem = std::make_shared<RenderSystem>(RenderSystemDesc{ *m_logger });
	m_display = std::make_unique<Display>(DisplayDesc{ {*m_logger,desc.windowSize},*m_renderSystem });
	m_world = std::make_unique<World>(WorldDesc{ BaseDesc{*m_logger}, GameContext{*m_inputSystem} });
	m_graphicsEngine = std::make_unique<GraphicsEngine>(GraphicsEngineDesc{ {*m_logger},*m_renderSystem });

	m_inputSystem->setCursorLockArea(m_display->getClientAreaInScreenSpace());


	DX3DLogInfo("Game initialized.");

}
dx3d::Game::~Game()
{
	DX3DLogInfo("Game is shutting down.");
}

dx3d::World& dx3d::Game::getWorld() noexcept
{
	return *m_world;
}

dx3d::Logger& dx3d::Game::getLogger() noexcept
{
	return *m_logger;
}

dx3d::InputSystem& dx3d::Game::getInputSystem() noexcept
{
	return *m_inputSystem;
}

void dx3d::Game::onInternalUpdate()
{
	auto currentTime = std::chrono::steady_clock::now();
	std::chrono::duration<f32> delta = currentTime - m_previousTime;
	m_previousTime = currentTime;
	auto deltaTime = delta.count();

	m_inputSystem->update();

	onUpdate(deltaTime);

	m_world->update(deltaTime);

	m_graphicsEngine->render(*m_world, m_display->getSwapChain(), deltaTime);
}



