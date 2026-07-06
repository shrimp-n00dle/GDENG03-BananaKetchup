#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Resource/MaterialResource.h>


using namespace catsup;

dx3d::GraphicsEngine::GraphicsEngine(const GraphicsEngineDesc& desc): Base(desc.base), m_renderSystem(desc.engine)
{
	auto& device = m_renderSystem;
	m_deviceContext = device.createDeviceContext();

	//Create the shape
	const Vertex vertextList[] =
	{
		{{-0.5f,-0.5f,-0.5f}},
		{{-0.5f,0.5f,-0.5f} },
		{{0.5f,0.5f,-0.5f}},
		{{0.5f,-0.5f,-0.5f}},

		{{0.5f,-0.5f,0.5f}},
		{{0.5f,0.5f,0.5f}},
		{{-0.5f,0.5f,0.5f}},
		{{-0.5f,-0.5f,0.5f}}
	};

	const ui32 indexList[] =
	{
		0,1,2,
		2,3,0,

		4,5,6,
		6,7,4,

		1,6,5,
		5,2,1,

		7,0,3,
		3,4,7,

		3,2,5,
		5,4,3,

		7,6,1,
		1,0,7
	};

	m_objectCb = device.createConstantBuffer({ {}, sizeof(ObjectData) });
	m_cameraCb = device.createConstantBuffer({ {}, sizeof(CameraData) });
	m_materialCb = device.createConstantBuffer({ {}, dx3d::MaterialResource::MaxDataSize });

	m_vb = device.createVertexBuffer({ vertextList, std::size(vertextList), sizeof(Vertex) });
	m_ib = device.createIndexBuffer({ indexList, std::size(indexList) });
}

void dx3d::GraphicsEngine::spawnTest(World& world)
{
	if (bSpawn)
	{
		srand(time(NULL));
		int coord = rand() % 3 - 2;


	
			auto cube = world.createGameObject<dx3d::GameObject>();
			cube->createOrGetComponent<dx3d::CubeComponent>();
			auto height = (rand() % 60) + (40.0f);
			height /= 50.0f;

			auto width = (rand() % 300) + (100.0f);
			width /= 500.0f;

			cube->getTransform().setScale({ width, height, width });
			cube->getTransform().setPosition({ coord * 0.5f, (height / 2.0f) - 1.0f, coord * 0.5f });

			bSpawn = false;
	}
		
}

void dx3d::GraphicsEngine::render(const World& world, SwapChain& swapChain, f32 deltaTime)
{
	//camera setup
	auto size = swapChain.getSize();

	auto& context = *m_deviceContext;
	context.clearAndSetBackBuffer(swapChain, { 0.27f, 0.39f, 0.55f, 1.0f });
	context.setViewportSize(size);

	auto numComponents = 0u;
	auto& cameraCb = *m_cameraCb;
	auto& objectCb = *m_objectCb;
	auto& materialCb = *m_materialCb;

	{
		CameraData cameraData{};
		auto components = world.getComponents<CameraComponent>(numComponents);
		for (auto i : std::views::iota(0u, numComponents))
		{
			auto component = components[i];
			cameraData.view = component->getViewMatrix();
			component->setViewportSize(size);
			cameraData.proj = component->getProjectionMatrix();
			context.updateConstantBuffer(cameraCb, std::as_bytes(std::span{ &cameraData, 1 }));
			break;
		}
	}

	/*Rendering and spawning cubes*/
	{
		ObjectData objectData{};
		auto components = world.getComponents<CubeComponent>(numComponents);
		

		for (auto i : std::views::iota(0u, numComponents))
		{
			auto component = components[i];
			auto& transform = component->getGameObject().getTransform();
			auto material = component->getMaterial();

			if (material)
			{
				objectData.world = transform.getAffineWorldMatrix();

				context.setGraphicsPipelineState(material->getGraphicsPipelineState());
				context.updateConstantBuffer(objectCb, std::as_bytes(std::span{ &objectData, 1 }));
				context.updateConstantBuffer(materialCb, material->getData());
				ConstantBuffer* cbs[] = { &objectCb, &cameraCb, &materialCb };
				context.setConstantBuffers(std::span<ConstantBuffer*>{cbs});

				auto& vb = *m_vb;
				auto& ib = *m_ib;
				context.setVertexBuffer(vb);
				context.setIndexBuffer(ib);
				context.drawIndexedTriangleList(ib.getIndexListSize(), 0u, 0u);
			}
		}
	}

	m_renderSystem.executeCommandList(context);
	swapChain.present();
}

void dx3d::GraphicsEngine::callSpawn()
{
	bSpawn = true;
}

void dx3d::GraphicsEngine::removeRecent()
{
	incCube++;
}

void dx3d::GraphicsEngine::closeProgram()
{
	PostQuitMessage(0);
}

