#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/RenderSystem.h>
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>
#include <DX3D/Graphics/VertexBuffer.h>
#include <DX3D/Graphics/IndexBuffer.h>
#include <DX3D/Math/Vec3.h>
#include <fstream>

#include <DX3D/Game/World.h>
#include <DX3D/Game/Component.h>
#include <DX3D/Game/GameObject.h>

#include <DX3D/Component/TransformComponent.h>
#include <DX3D/Component/CubeComponent.h>
#include <DX3D/Component/CameraComponent.h>
#include <ranges>

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

	m_vb = device.createVertexBuffer({ vertextList, std::size(vertextList), sizeof(Vertex) });
	m_cb = device.createConstantBuffer({ {}, sizeof(ConstantData) });
	m_ib = device.createIndexBuffer({ indexList, std::size(indexList) });
}


dx3d::GraphicsEngine::~GraphicsEngine()
{
}

void dx3d::GraphicsEngine::spawnTest(World& world)
{

	/*auto cube = world.createGameObject<dx3d::GameObject>();
	cube->createOrGetComponent<dx3d::CubeComponent>();
	auto height = (rand() % 120) + (80.0f);
	height /= 100.0f;

	auto width = (rand() % 600) + (200.0f);
	width /= 1000.0f;

	cube->getTransform().setScale({ width, height, width });
	cube->getTransform().setPosition({ -3 * 1.4f, (height / 2.0f) - 1.0f, -2 * 1.4f });*/

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

	auto numComponents = 0u;
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


	/*Rendering and spawning cubes*/
	{
		auto components = world.getComponents<CubeComponent>(numComponents);
		

		for (auto i : std::views::iota(0u, numComponents))
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
	}

	m_renderSystem.executeCommandList(context);
	swapChain.present();
}
