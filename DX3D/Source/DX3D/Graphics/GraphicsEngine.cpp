#include <DX3D/Graphics/GraphicsEngine.h>


using namespace catsup;

dx3d::GraphicsEngine::GraphicsEngine(const GraphicsEngineDesc& desc): Base(desc.base), m_renderSystem(desc.engine)
{
	auto& device = m_renderSystem;
	m_deviceContext = device.createDeviceContext();

	//Shader file path
	constexpr char shaderFilePath[] = "DX3D/Assets/Shaders/Basic.hlsl";
	std::ifstream shaderStream(shaderFilePath);
	if (!shaderStream) DX3DLogThrowError("shaderStream failed to open, from GE.cpp");
	std::string shaderFileData{
		std::istreambuf_iterator<char>(shaderStream),
		std::istreambuf_iterator<char>()
		};

	auto shaderSourceCode = shaderFileData.c_str();
	auto shaderSourceCodeSize = shaderFileData.length();

	auto vs = device.compileShader({ shaderFilePath,shaderSourceCode, shaderSourceCodeSize,
		"VSMain", ShaderType::VertexShader});

	auto ps = device.compileShader({ shaderFilePath,shaderSourceCode, shaderSourceCodeSize,
	"PSMain", ShaderType::PixelShader });

	auto vsSig = device.createVertexShaderSignature({vs});

	m_pipeline = device.createGraphicsPipelineState({*vsSig, *ps});

	//Create the shape
	const Vertex vertextList[] =
	{
		//Position            //Color
		{{-0.5f,-0.5f,-0.5f}, {1,0,0,1}},
		{{-0.5f,0.5f,-0.5f}, {0,1,0,1} },
		{{0.5f,0.5f,-0.5f},  {0,0,1,1}},
		{{0.5f,-0.5f,-0.5f}, {1,0,1,1}},

		{{0.5f,-0.5f,0.5f}, {1,0,1,1}},
		{{0.5f,0.5f,0.5f}, {0,0,1,1}},
		{{-0.5f,0.5f,0.5f}, {0,1,0,1}},
		{{-0.5f,-0.5f,0.5f}, {1,0,0,1}}
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

	//Create Plane
	const Vertex test[]
	{
		{ { -0.5f, 0.0f, 0.5f }, {1,0,0,1} },
		{ { 0.5f, 0.0f,  0.5f }, {1,0,0,1} },
		{ { 0.5f, 0.0f, -0.5f }, {1,0,0,1} },
		{ { -0.5f,0.0f, -0.5f }, {1,0,0,1} }

	};

	//Create Pyramid
	Vertex pyramids[] =
	{
		{ { -0.5f, -0.5f, -0.5f }, {1,0,0,1}}, 
		{ {  0.5f, -0.5f, -0.5f }, {0,1,0,1}},
		{ {  0.5f, -0.5f,  0.5f }, {0,0,1,1}}, 
		{ { -0.5f, -0.5f,  0.5f }, {1,0,1,1}}, 
		{ {  0.0f,  0.5f,  0.0f }, {1,0,1,1}} 
	};

	const ui32 pyramids_i[] =
	{
		0, 2, 1,

		0, 3, 2,

		3, 4, 2,

		1, 4, 0,

		0, 4, 3,

		2, 4, 1
	};

	m_vb_pyramid = device.createVertexBuffer({ pyramids, std::size(pyramids), sizeof(Vertex) });
	m_ib_pyramid = device.createIndexBuffer({ pyramids_i, std::size(pyramids_i) });

	m_vb = device.createVertexBuffer({ vertextList, std::size(vertextList), sizeof(Vertex) });
	m_cb = device.createConstantBuffer({ {}, sizeof(ConstantData) });
	m_vb2 = device.createVertexBuffer({ test, std::size(test), sizeof(Vertex) });
	m_ib = device.createIndexBuffer({ indexList, std::size(indexList) });

}


dx3d::GraphicsEngine::~GraphicsEngine()
{
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
	//Set Bg to black
	context.clearAndSetBackBuffer(swapChain, { 0.0f,0.0f,0.0f, 0.0f });
	context.setGraphicsPipelineState(*m_pipeline);
	context.setViewportSize(size);

	numComponents = 0u;
	ConstantData data{};
	{
		auto components = world.getComponents<CameraComponent>(numComponents);
		for (auto i : std::views::iota(0u, numComponents))
		{
			auto component = components[i];
			data.view = component->getViewMatrix();
			component->setViewportSize(size);
			data.proj = component->getProjectionMatrix();
			break;
		}
	}

	//FLOOR
{
	auto floorComponent = world.getComponents<PlaneComponent>(numComponents);

	for (auto i : std::views::iota(0u, numComponents))
	{
		auto component = floorComponent[i];
		auto& transform = component->getGameObject().getTransform();

		data.world = transform.getAffineWorldMatrix();

		auto& cb = *m_cb;
		context.updateConstantBuffer(cb, &data);

		auto& vb = *m_vb2;
		auto& ib = *m_ib;
		context.setVertexBuffer(vb);
		context.setConstantBuffer(cb);
		context.setIndexBuffer(ib);
		context.drawIndexedTriangleList(ib.getIndexListSize(), 0u, 0u);
	}
}

//Rendering Pyramids
{

	auto components = world.getComponents<PyramidComponent>(numComponents);


	for (auto i : std::views::iota(0u, numComponents - incCube))
	{
		auto component = components[i];
		auto& transform = component->getGameObject().getTransform();

		data.world = transform.getAffineWorldMatrix();

		auto& cb = *m_cb;
		context.updateConstantBuffer(cb, &data);

		auto& vb = *m_vb_pyramid;
		auto& ib = *m_ib_pyramid;
		context.setVertexBuffer(vb);
		context.setConstantBuffer(cb);
		context.setIndexBuffer(ib);
		context.drawIndexedTriangleList(ib.getIndexListSize(), 0u, 0u);
	}
	bDeleteAll = false;
}


	/*Rendering and spawning cubes*/
	{

		auto components = world.getComponents<CubeComponent>(numComponents);
		removeAllFromRender();
		

		for (auto i : std::views::iota(0u, numComponents - incCube))
		{
			auto component = components[i];
			auto& transform = component->getGameObject().getTransform();

			data.world = transform.getAffineWorldMatrix();

			auto& cb = *m_cb;
			context.updateConstantBuffer(cb, &data);

			auto& vb = *m_vb;
			auto& ib = *m_ib;
			context.setVertexBuffer(vb);
			context.setConstantBuffer(cb);
			context.setIndexBuffer(ib);
			context.drawIndexedTriangleList(ib.getIndexListSize(), 0u, 0u);
		}
		bDeleteAll = false;
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

void dx3d::GraphicsEngine::removeAllShapes()
{
	bDeleteAll = true;
}

void dx3d::GraphicsEngine::removeAllFromRender()
{
	if (bDeleteAll)
	{
		incCube = numComponents;
	}

}


