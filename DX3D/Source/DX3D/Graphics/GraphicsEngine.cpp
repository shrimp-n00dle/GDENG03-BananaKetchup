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

	//For spheres
	auto vs_sphere = device.compileShader({ shaderFilePath,shaderSourceCode, shaderSourceCodeSize,
	"VSMain_Sphere", ShaderType::VertexShader });
	auto ps_sphere = device.compileShader({ shaderFilePath,shaderSourceCode, shaderSourceCodeSize,
	"PSMain_Sphere", ShaderType::PixelShader });


	auto vsSig = device.createVertexShaderSignature({vs});
	auto vsSig_Sphere = device.createVertexShaderSignature({ vs_sphere });

	m_pipeline = device.createGraphicsPipelineState({*vsSig, *ps, *vsSig_Sphere, *ps_sphere});

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

	m_vb = device.createVertexBuffer({ vertextList, std::size(vertextList), sizeof(Vertex) });
	m_cb = device.createConstantBuffer({ {}, sizeof(ConstantData) });
	m_ib = device.createIndexBuffer({ indexList, std::size(indexList) });

	//Create Plane
	const Vertex test[]
	{
		{ { -0.5f, 0.0f, 0.5f }, {1,0,0,1} },
		{ { 0.5f, 0.0f,  0.5f }, {1,0,0,1} },
		{ { 0.5f, 0.0f, -0.5f }, {1,0,0,1} },
		{ { -0.5f,0.0f, -0.5f }, {1,0,0,1} }

	};
	m_vb2 = device.createVertexBuffer({ test, std::size(test), sizeof(Vertex) });


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

	//Pyramid Stuff
	m_vb_pyramid = device.createVertexBuffer({ pyramids, std::size(pyramids), sizeof(Vertex) });
	m_ib_pyramid = device.createIndexBuffer({ pyramids_i, std::size(pyramids_i) });


	//Create Sphere

	std::vector<Vertex>  sphere_list;
	std::vector<ui32> sphere_indices;

	float radius = 0.1f;
	int numSlices = 20; 
	int numStacks = 20; 


	for (int i = 0; i <= numStacks; ++i) {
		float phi = i * DirectX::XM_PI / numStacks;

		for (int j = 0; j <= numSlices; ++j) {
			float theta = j * (2.0f * DirectX::XM_PI) / numSlices;

			Vertex sphere;
			sphere.position = { (radius * sinf(phi) * cosf(theta)),
								 (radius * cosf(phi)),
								(radius * sinf(phi) * sinf(theta)) };


			sphere.color = { 0,1,0,1 };

			sphere_list.push_back(sphere);
		}
	}

	std::cout << "SPHERE LIST SIZE IS: " << sphere_list.size() << std::endl;

	//Sphere Indices
	for (int i = 0; i < numStacks; ++i) {
		for (int j = 0; j < numSlices; ++j) {
			int current = i * (numSlices + 1) + j;
			int next = current + numSlices + 1;

			// Triangle 1
			sphere_indices.push_back(current);
			sphere_indices.push_back(next);
			sphere_indices.push_back(current + 1);

			// Triangle 2
			sphere_indices.push_back(current + 1);
			sphere_indices.push_back(next);
			sphere_indices.push_back(next + 1);
		}
	}

	std::cout << "SPHERE LIST SIZE IS: " << sphere_indices.size() << std::endl;

	const int sphere_size = sphere_list.size();


	
	Vertex sphere_vertices[441];

	for (int i = 0; i < sphere_list.size(); i++)
	{
		sphere_vertices[i] = sphere_list[i];
	}

	ui32 spheres_i[2400];

	for (int i = 0; i < sphere_indices.size(); i++)
	{
		spheres_i[i] = sphere_indices[i];
	}
	/*{
		sphere_list[0],
		sphere_list[1],
		sphere_list[2],
		sphere_list[3],
		sphere_list[4],
		sphere_list[5],
		sphere_list[6],
		sphere_list[7],
		sphere_list[8],
		sphere_list[9],
		sphere_list[10],
		sphere_list[11],
		sphere_list[12],
		sphere_list[13],
		sphere_list[14],
		sphere_list[15],
		sphere_list[16],
		sphere_list[17],
		sphere_list[18],
		sphere_list[19],

		sphere_list[20],
		sphere_list[21],
		sphere_list[22],
		sphere_list[23],
		sphere_list[24],
		sphere_list[25],
		sphere_list[26],
		sphere_list[27],
		sphere_list[28],
		sphere_list[29],
		sphere_list[30],
		sphere_list[31],
		sphere_list[32],
		sphere_list[33],
		sphere_list[34],
		sphere_list[35],
	};*/



	/*{
		sphere_indices[0],
		sphere_indices[1],
		sphere_indices[2],
		sphere_indices[3],
		sphere_indices[4],
		sphere_indices[5],
		sphere_indices[6],
		sphere_indices[7],
		sphere_indices[8],
		sphere_indices[9],
		sphere_indices[10],
		sphere_indices[11],
		sphere_indices[12],
		sphere_indices[13],
		sphere_indices[14],
		sphere_indices[15],
		sphere_indices[16],
		sphere_indices[17],
		sphere_indices[18],
		sphere_indices[19],


		sphere_indices[20],
		sphere_indices[21],
		sphere_indices[22],
		sphere_indices[23],
		sphere_indices[24],
		sphere_indices[25],
		sphere_indices[26],
		sphere_indices[27],
		sphere_indices[28],
		sphere_indices[29],
		sphere_indices[30],
		sphere_indices[31],
		sphere_indices[32],
		sphere_indices[33],
		sphere_indices[34],
		sphere_indices[35],
	};*/

	//Sphere Stuff
	std::cout << "ABOUT TO RENDER" << std::endl;
	 m_vb_sphere = device.createVertexBuffer({ sphere_vertices, std::size(sphere_vertices), sizeof(Vertex) });
	 m_ib_sphere = device.createIndexBuffer({ spheres_i, std::size(spheres_i) });
	 std::cout << "DONE" << std::endl;

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
//{
//
//	auto components = world.getComponents<PyramidComponent>(numComponents);
//
//
//	for (auto i : std::views::iota(0u, numComponents - incCube))
//	{
//		auto component = components[i];
//		auto& transform = component->getGameObject().getTransform();
//
//		data.world = transform.getAffineWorldMatrix();
//
//		auto& cb = *m_cb;
//		context.updateConstantBuffer(cb, &data);
//
//		auto& vb = *m_vb_pyramid;
//		auto& ib = *m_ib_pyramid;
//		context.setVertexBuffer(vb);
//		context.setConstantBuffer(cb);
//		context.setIndexBuffer(ib);
//		context.drawIndexedTriangleList(ib.getIndexListSize(), 0u, 0u);
//	}
//}



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



	//Rendering SPheres
	{
		auto floorComponent = world.getComponents<SphereComponent>(numComponents);

		for (auto i : std::views::iota(0u, numComponents))
		{
			auto component = floorComponent[i];
			auto& transform = component->getGameObject().getTransform();

			data.world = transform.getAffineWorldMatrix();

			auto& cb = *m_cb;
			context.updateConstantBuffer(cb, &data);

			auto& vb = *m_vb_sphere;
			auto& ib = *m_ib_sphere;
			context.setVertexBuffer(vb);
			context.setConstantBuffer(cb);
			context.setIndexBuffer(ib);
			context.drawIndexedTriangleList(ib.getIndexListSize(), 0u, 0u);
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


