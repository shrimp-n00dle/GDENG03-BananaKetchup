#include <DX3D/Game/Game.h>
#include <DX3D/Window/Window.h>
#include <DX3D/Graphics/GraphicsDevice.h>
#include <DX3D/Core/Logger.h>
#include <DX3D/Input/InputSystem.h>
#include <DX3D/Game/PhysicsSystem.h>
#include <DX3D/Game/Display.h>
#include <DX3D/Game/World.h>
#include <DX3D/Game/GameObject.h>
#include <DX3D/Game/WorldRenderer.h>
#include <DX3D/Resource/ResourceManager.h>

#include <span>
#include <DX3D/Resource/MaterialResource.h>
#include <DX3D/Resource/TextureResource.h>


dx3d::Game::Game(const GameDesc& desc)
{
	m_logger = std::make_unique<Logger>(desc.logLevel);	

	std::clog << "BananaCatsup V 1.0" << "\n";
	std::clog << "--------------------------------------" << "\n";

	m_inputSystem = std::make_unique<InputSystem>(InputSystemDesc{ *m_logger });
	m_graphicsDevice = std::make_shared<GraphicsDevice>(GraphicsDeviceDesc{ *m_logger });
	m_display = std::make_unique<Display>(DisplayDesc{ {*m_logger,desc.windowSize},*m_graphicsDevice });
	
	auto context = SystemContext{ *m_graphicsDevice };
	m_resourceManager = std::make_unique<ResourceManager>(ResourceManagerDesc{ {*m_logger},context });
	//m_resourceManager = std::make_shared<ResourceManager>(ResourceManagerDesc{ {*m_logger},context });

	m_physicsSystem = std::make_shared<PhysicsSystem>(PhysicsSystemDesc{ *m_logger });

	m_world = std::make_unique<World>(WorldDesc{ BaseDesc{*m_logger}, GameContext{*m_inputSystem, *m_resourceManager,*m_graphicsDevice, *m_physicsSystem} });
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

	//Command* command = m_inputSystem->handleInput();
	//if (command)
	//{
	//	command->execute(*m_worldRenderer.get());
	//}

	m_inputSystem->update();

	//Physics
	m_physicsSystem->getPhysicsWorld()->update(deltaTime);

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

	if (menuBar->getShowLoad()) bLoad = true;

	ImGui::Render();

	if (bLoad)
	{

		auto& world = getWorld();

		string curr_path = "Unity_Scene.json";
		std::string filepath = curr_path.empty() ? "test.json" : curr_path;
		std::cout << "Loading scene from filename: " << filepath << std::endl;

		std::ifstream file(filepath, std::ios::in);
		if (!file.is_open()) {
			std::cerr << "Error: Could not open file " << filepath << " for reading." << std::endl;
			return;
		}

		Json::Value root;
		Json::CharReaderBuilder readerBuilder;
		std::string errs;


		bool parsingSuccessful = Json::parseFromStream(readerBuilder, file, &root, &errs);
		file.close();

		if (!parsingSuccessful) {
			std::cerr << "Error: Failed to parse JSON file. Parse errors:\n" << errs << std::endl;
			return;
		}
		if (!root.isMember("objects") || !root["objects"].isArray()) {
			std::cerr << "Error: Invalid JSON format. 'objects' array not found." << std::endl;
			return;
		}

		const Json::Value& objectsArray = root["objects"];

		for (const auto& objJson : objectsArray)
		{
			std::string objName = objJson.isMember("name") ? objJson["name"].asString() : "Default_Object";

			float posX = 0.0f, posY = 0.0f, posZ = 0.0f;
			if (objJson.isMember("position")) {
				posX = objJson["position"].get("x", 0.0f).asFloat();
				posY = objJson["position"].get("y", 0.0f).asFloat();
				posZ = objJson["position"].get("z", 0.0f).asFloat();
			}

			float rotX = 0.0f, rotY = 0.0f, rotZ = 0.0f;
			if (objJson.isMember("rotation")) {
				rotX = objJson["rotation"].get("x", 0.0f).asFloat();
				rotY = objJson["rotation"].get("y", 0.0f).asFloat();
				rotZ = objJson["rotation"].get("z", 0.0f).asFloat();
			}

			float scaleX = 1.0f, scaleY = 1.0f, scaleZ = 1.0f;
			if (objJson.isMember("scale")) {
				scaleX = objJson["scale"].get("x", 1.0f).asFloat();
				scaleY = objJson["scale"].get("y", 1.0f).asFloat();
				scaleZ = objJson["scale"].get("z", 1.0f).asFloat();
			}

			auto brickTex = getResourceManager().createResourceFromFile<dx3d::TextureResource>(L"Game/Assets/Textures/brick.jpg");
			auto basicMat = getResourceManager().createResourceFromFile<dx3d::MaterialResource>(L"Game/Assets/Shaders/Basic.hlsl");
			if (basicMat)
			{
				auto matData = dx3d::Vec3(1, 1, 1);
				basicMat->setData(std::as_bytes(std::span{ &matData, 1 }));
				basicMat->setTexture(0, brickTex);
			}

			if (objName == "Cube")
			{
				auto obj = world.createGameObject<dx3d::GameObject>();
				obj->createOrGetComponent<dx3d::CubeComponent>();
				auto comp = obj->createOrGetComponent<dx3d::CubeComponent>();
				comp->setMaterial(basicMat);
				obj->getTransform().setScale({ scaleX,scaleY, scaleZ });
				obj->getTransform().setPosition({ posX, posY, posZ });
				obj->getTransform().setRotation({ rotX, rotY, rotZ });
			}

			else if (objName == "Sphere")
			{
				auto obj = world.createGameObject<dx3d::GameObject>();
				obj->createOrGetComponent<dx3d::SphereComponent>();
				auto comp = obj->createOrGetComponent<dx3d::SphereComponent>();
				comp->setMaterial(basicMat);
				obj->getTransform().setPosition({ posX, posY, posZ });
				obj->getTransform().setRotation({ rotX, rotY, rotZ });
				obj->getTransform().setScale({ scaleX ,scaleY , scaleZ });
			}

			else if (objName == "Plane")
			{
				auto obj = world.createGameObject<dx3d::GameObject>();
				obj->createOrGetComponent<dx3d::CubeComponent>();
				auto comp = obj->createOrGetComponent<dx3d::CubeComponent>();
				comp->setMaterial(basicMat);
				obj->getTransform().setPosition({ posX, posY, posZ });
				obj->getTransform().setRotation({ rotX, rotY, rotZ });
				obj->getTransform().setScale({ scaleX ,scaleY , scaleZ });
			}

			else if (objName == "Capsule")
			{
				auto obj = world.createGameObject<dx3d::GameObject>();
				obj->createOrGetComponent<dx3d::CapsuleComponent>();
				auto comp = obj->createOrGetComponent<dx3d::CapsuleComponent>();
				comp->setMaterial(basicMat);
				obj->getTransform().setPosition({ posX, posY, posZ });
				obj->getTransform().setRotation({ rotX, rotY, rotZ });
				obj->getTransform().setScale({ scaleX,scaleY, scaleZ });
			}
			else if (objName == "") std::cout << "pass" << std::endl;
	

		}

		std::cout << "Successfully loaded scene from " << filepath << std::endl;

		bLoad = false;
	}



	m_worldRenderer->render(*m_world, 
		m_display->getSwapChain(), 
		deltaTime, 
		ImGui::GetDrawData(),
		menuBar);
}
