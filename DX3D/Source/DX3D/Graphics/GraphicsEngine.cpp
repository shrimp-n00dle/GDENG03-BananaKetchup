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
		{ { 0.5f, 0.0f,  0.5f }, {0,1,0,1} },
		{ { 0.5f, 0.0f, -0.5f }, {0,0,1,1} },
		{ { -0.5f,0.0f, -0.5f }, {1,0,1,1} }

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


			sphere.color = randomizeColor();

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
	//Sphere Stuff
	 m_vb_sphere = device.createVertexBuffer({ sphere_vertices, std::size(sphere_vertices), sizeof(Vertex) });
	 m_ib_sphere = device.createIndexBuffer({ spheres_i, std::size(spheres_i) });


	 //CREATE CYLINDER
	 std::vector<Vertex>  cy_list;
	 std::vector<ui32> cy_indices;
	 float height = 20, stackCount = 20, sliceCount = 20;
	 float topRadius = 1.0f,bottomRadius = 1.0f;

	 float stackHeight = height / stackCount;
	 float radiusStep = (topRadius - bottomRadius) / stackCount;
	 UINT ringCount = stackCount + 1;


	 for (UINT i = 0; i < ringCount; ++i) {
		 float y = -0.5f * height + i * stackHeight;
		 float r = bottomRadius + i * radiusStep;

		 float dTheta = 2.0f * DirectX::XM_PI / sliceCount;
		 for (UINT j = 0; j <= sliceCount; ++j) {
			 float c = cosf(j * dTheta);
			 float s = sinf(j * dTheta);

			 Vertex v;
			 v.position = {r * c, y, r * s};
			 // Normals and UVs can be calculated here for lighting and texturing
			// v.Normal = DirectX::XMFLOAT3(c, 0.0f, s); // simplified
			// v.TexCoord = DirectX::XMFLOAT2((float)j / sliceCount, (float)i / stackCount);
			 v.color = randomizeColor();

			 cy_list.push_back(v);
		 }
	 }

	 // Add indices for the cylinder body
	 UINT ringVertexCount = sliceCount + 1;
	 for (UINT i = 0; i < stackCount; ++i) {
		 for (UINT j = 0; j < sliceCount; ++j) {
			 cy_indices.push_back(i * ringVertexCount + j);
			 cy_indices.push_back((i + 1) * ringVertexCount + j);
			 cy_indices.push_back(i * ringVertexCount + j + 1);
			 
			 cy_indices.push_back(i * ringVertexCount + j + 1);
			 cy_indices.push_back((i + 1) * ringVertexCount + j);
			 cy_indices.push_back((i + 1) * ringVertexCount + j + 1);
		 }
	 }

	 //BOTTOM AND TOP CAP
	 // --- BOTTOM CAP ---
	 UINT bottomCapStartIndex = (UINT)cy_list.size();
	 float yBottom = -0.5f * height;

	 // 1. Center vertex for the bottom cap
	 Vertex bottomCenter;
	 bottomCenter.position = { 0.0f, yBottom, 0.0f };
	 //bottomCenter.Normal = DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f);
	 //bottomCenter.TexCoord = DirectX::XMFLOAT2(0.5f, 0.5f);
	 cy_list.push_back(bottomCenter);

	 // 2. Ring vertices for the bottom cap
	 float dTheta = 2.0f * DirectX::XM_PI / sliceCount;
	 for (UINT i = 0; i <= sliceCount; ++i) {
		 float c = cosf(i * dTheta);
		 float s = sinf(i * dTheta);

		 Vertex v;
		 v.position = { bottomRadius * c, yBottom, bottomRadius * s };
		 v.color = randomizeColor();
		// v.Normal = DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f);
		 // Map texture coordinates to a flat circle
		// v.TexCoord = DirectX::XMFLOAT2(0.5f + 0.5f * c, 0.5f + 0.5f * s);
		 cy_list.push_back(v);
	 }

	 // 3. Bottom cap indices (Clockwise winding order looking from below)
	 for (UINT i = 0; i < sliceCount; ++i) {
		 cy_indices.push_back(bottomCapStartIndex);
		 cy_indices.push_back(bottomCapStartIndex + 1 + i + 1);
		 cy_indices.push_back(bottomCapStartIndex + 1 + i);
	 }

	 // --- TOP CAP ---
	 UINT topCapStartIndex = (UINT)cy_list.size();
	 float yTop = 0.5f * height;

	 // 1. Center vertex for the top cap
	 Vertex topCenter;
	 topCenter.position = { 0.0f, yTop, 0.0f };
	 topCenter.color = randomizeColor();
	 //topCenter.Normal = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
	// topCenter.TexCoord = DirectX::XMFLOAT2(0.5f, 0.5f);
	 cy_list.push_back(topCenter);

	 // 2. Ring vertices for the top cap
	 for (UINT i = 0; i <= sliceCount; ++i) {
		 float c = cosf(i * dTheta);
		 float s = sinf(i * dTheta);

		 Vertex v;
		 v.position = { topRadius * c, yTop, topRadius * s };
		 v.color = randomizeColor();
		// v.Normal = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
		 // Map texture coordinates to a flat circle
		// v.TexCoord = DirectX::XMFLOAT2(0.5f + 0.5f * c, 0.5f + 0.5f * s);
		 cy_list.push_back(v);
	 }

	 // 3. Top cap indices (Clockwise winding order looking from above)
	 for (UINT i = 0; i < sliceCount; ++i) {
		 cy_indices.push_back(topCapStartIndex);
		 cy_indices.push_back(topCapStartIndex + 1 + i);
		 cy_indices.push_back(topCapStartIndex + 1 + i + 1);
	 }
	 
	 std::cout << "CYLINDER SIZE IS " << cy_list.size() << std::endl;
	 std::cout << "CYLINDER INDCIDED SIZE IS " << cy_indices.size() << std::endl;

	 Vertex cy_vertices[485];

	 for (int i = 0; i < cy_list.size(); i++)
	 {
		 cy_vertices[i] = cy_list[i];
	 }

	 ui32 cy_i[2520];

	 for (int i = 0; i < cy_indices.size(); i++)
	 {
		 cy_i[i] = cy_indices[i];
	 }
	 //Cylinder Stuff
	 m_vb_cylinder = device.createVertexBuffer({ cy_vertices, std::size(cy_vertices), sizeof(Vertex) });
	 m_ib_cylinder = device.createIndexBuffer({ cy_i, std::size(cy_i) });


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
		//removeAllFromRender();
		

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
		//bDeleteAll = false;
	}



	//Rendering SPheres
	//{
	//	auto floorComponent = world.getComponents<SphereComponent>(numComponents);

	//	for (auto i : std::views::iota(0u, numComponents))
	//	{
	//		auto component = floorComponent[i];
	//		auto& transform = component->getGameObject().getTransform();

	//		data.world = transform.getAffineWorldMatrix();

	//		auto& cb = *m_cb;
	//		context.updateConstantBuffer(cb, &data);

	//		auto& vb = *m_vb_sphere;
	//		auto& ib = *m_ib_sphere;
	//		context.setVertexBuffer(vb);
	//		context.setConstantBuffer(cb);
	//		context.setIndexBuffer(ib);
	//		context.drawIndexedTriangleList(ib.getIndexListSize(), 0u, 0u);
	//	}
	//}

	//Rendering Cylinders
	{
		auto floorComponent = world.getComponents<CylinderComponent>(numComponents);

		for (auto i : std::views::iota(0u, numComponents))
		{
			auto component = floorComponent[i];
			auto& transform = component->getGameObject().getTransform();

			data.world = transform.getAffineWorldMatrix();

			auto& cb = *m_cb;
			context.updateConstantBuffer(cb, &data);

			auto& vb = *m_vb_cylinder;
			auto& ib = *m_ib_cylinder;
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

dx3d::Vec4 dx3d::GraphicsEngine::randomizeColor()
{
	dx3d::Vec4 color;

	if (colorIndex >= 4) colorIndex = 1;

	switch (colorIndex)
	{
		//R
	case 1: color = {1,0,0,1}; break;
		//G
	case 2: color = {0,1,0,1}; break;
		//B
	case 3: color = {0,0,1,1 }; break;
		//Purple
	default: color = {1,0,1,1}; break;
	}

	colorIndex++;
	
	return color;
}


