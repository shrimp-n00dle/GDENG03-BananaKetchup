#include <DX3D/Game/Game.h>
#include <DX3D/Window/Window.h>
#include <DX3D/Graphics/GraphicsDevice.h>
#include <DX3D/Core/Logger.h>
#include <DX3D/Input/InputSystem.h>
#include <DX3D/Game/Display.h>
#include <DX3D/Game/World.h>
#include <DX3D/Game/GameObject.h>
#include <DX3D/Game/WorldRenderer.h>
#include <DX3D/Resource/ResourceManager.h>


dx3d::Game::Game(const GameDesc& desc)
{
	m_logger = std::make_unique<Logger>(desc.logLevel);	

	std::clog << "BananaCatsup V 1.0" << "\n";
	std::clog << "--------------------------------------" << "\n";

	m_inputSystem = std::make_unique<InputSystem>(InputSystemDesc{ *m_logger });
	m_graphicsDevice = std::make_shared<GraphicsDevice>(GraphicsDeviceDesc{ *m_logger });
	m_display = std::make_unique<Display>(DisplayDesc{ {*m_logger,desc.windowSize},*m_graphicsDevice });
	
	auto context = SystemContext{ *m_graphicsDevice };
	//m_resourceManager = std::make_unique<ResourceManager>(ResourceManagerDesc{ {*m_logger},context });
	m_resourceManager = std::make_shared<ResourceManager>(ResourceManagerDesc{ {*m_logger},context });

	m_world = std::make_unique<World>(WorldDesc{ BaseDesc{*m_logger}, GameContext{*m_inputSystem, *m_resourceManager,*m_graphicsDevice} });
	m_worldRenderer = std::make_unique<WorldRenderer>(WorldRendererDesc{ {*m_logger},*m_graphicsDevice });

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(m_display->getHandle());
	ImGui_ImplDX11_Init(m_graphicsDevice->m_d3dDevice.Get(),m_graphicsDevice->m_d3dContext.Get());


	DX3DLogInfo("Game initialized.");
}

dx3d::Game::~Game()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
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

dx3d::ResourceManager& dx3d::Game::getResourceManager() noexcept
{
	return *m_resourceManager;
}

void dx3d::Game::onInternalUpdate()
{
	auto currentTime = std::chrono::steady_clock::now();
	std::chrono::duration<f32> delta = currentTime - m_previousTime;
	m_previousTime = currentTime;
	auto deltaTime = delta.count();

	//Rendering Shapes Input Handler

	/*Command* command = m_inputSystem->handleInput();
	if (command)
	{
		command->execute(*m_worldRenderer.get());
	}*/

	m_inputSystem->update();

	onUpdate(deltaTime);

	m_world->update(deltaTime);

	//ImGui
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	menuBar->initialize();

	aboutWin->setOpen(menuBar->getShow());
	aboutWin->initialize();
	
	if (menuBar->getShowColor())colorWin->initialize();
	ImGui::Render();

	m_worldRenderer->render(*m_world, m_display->getSwapChain(), deltaTime, ImGui::GetDrawData());
}
