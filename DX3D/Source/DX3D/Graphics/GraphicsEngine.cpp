#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/RenderSystem.h>
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>
#include <DX3D/Graphics/VertexBuffer.h>
//#include <DX3D/Math/Vec3.h>
#include <fstream>

using namespace dx3d;
using namespace catsup;

dx3d::GraphicsEngine::GraphicsEngine(const GraphicsEngineDesc& desc): Base(desc.base)
{
	m_renderSystem = std::make_shared<RenderSystem>(RenderSystemDesc{m_logger});

	auto& device = *m_renderSystem;
	m_deviceContext = device.createDeviceContext();
	reloadShaders(device);

	//Baking shapes here
	//auto& spawner = *m_spawner;
	//m_vb = spawner.bakeShapes(1,device);
	
	const Vertex vertextList[] =
	{
		//Position            //Color
		{ {-0.25f,-0.25f,0.0f}, {1,0,0,1} },
		{ {-0.25f,0.25f,0.0f},  {0,1,0,1} },
		{ {0.25f,0.25f,0.0f},   {0,0,1,1} },

		
		{ {0.25f,0.25f,0.0f},   {0,0,1,1} },
		{ {0.25f,-0.25f,0.0f},  {0,0,1,1} },
		{ {-0.25f,-0.25f,0.0f}, {1,0,0,1} }
	};

	//Traingle Rainbow
	//const Vertex vertextList2[] =
	//{
	//	//Position            //Color
	//	{ {-0.9f,-0.25f,0.0f}, {1,0,0,1} },
	//	{ {-0.60f,0.25f,0.0f},  {0,1,0,1} },
	//	{ {-0.3f,-0.25f,0.0f},   {0,0,1,1} },
	//};

	//Green Rectangle
	//const Vertex vertextList3[] =
	//{
	//	//Position            //Color
	//	{ {0.4f,-0.25f,0.0f}, {0,1,0,1} },
	//	{ {0.4f,0.25f,0.0f},  {0,1,0,1} },
	//	{ {0.8f,0.25f,0.0f},   {0,1,0,1} },


	//	{ {0.8f,0.25f,0.0f},   {0,1,0,1} },
	//	{ {0.8f,-0.25f,0.0f},  {0,1,0,1} },
	//	{ {0.4f,-0.25f,0.0f}, {0,1,0,1} }
	//};

	m_vb = device.createVertexBuffer({vertextList, std::size(vertextList), sizeof(Vertex)});
	//m_vb2 = device.createVertexBuffer({ vertextList2, std::size(vertextList2), sizeof(Vertex) });
	//m_vb3 = device.createVertexBuffer({ vertextList3, std::size(vertextList3), sizeof(Vertex) });

}


dx3d::GraphicsEngine::~GraphicsEngine()
{
}

void dx3d::GraphicsEngine::reloadShaders(RenderSystem& device)
{
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
		"VSMain", ShaderType::VertexShader });

	auto ps = device.compileShader({ shaderFilePath,shaderSourceCode, shaderSourceCodeSize,
	"MovingColors", ShaderType::PixelShader });

	auto vsSig = device.createVertexShaderSignature({ vs });

	m_pipeline = device.createGraphicsPipelineState({ *vsSig, *ps });

}

RenderSystem& dx3d::GraphicsEngine::getRenderSystem()noexcept
{
	// TODO: insert return statement here
	return *m_renderSystem;
}

void dx3d::GraphicsEngine::render(SwapChain& swapChain)
{
	auto& context = *m_deviceContext;
	context.clearAndSetBackBuffer(swapChain, { 0.27f, 0.39f,0.55f, 1.0f });
	context.setGraphicsPipelineState(*m_pipeline);

	context.setViewportSize(swapChain.getSize());

	//Shoawing shapes here
	//auto& spawner = *m_spawner;
	//spawner.decoShapes(m_vb,context);

	/*auto& vb = spawner.getList();
	context.setVertexBuffer(vb);
	context.drawTriangleList(vb.getVertexListSize(), 0u);*/

	auto& vb = *m_vb;
	context.setVertexBuffer(vb);
	context.drawTriangleList(vb.getVertexListSize(),0u);

	////Triangle Rainbow
	//auto& vb2 = *m_vb2;
	//context.setVertexBuffer(vb2);
	//context.drawTriangleList(vb2.getVertexListSize(), 0u);

	////Rectangle Green
	//auto& vb3 = *m_vb3;
	//context.setVertexBuffer(vb3);
	//context.drawTriangleList(vb3.getVertexListSize(), 0u);

	auto& device = *m_renderSystem;
	device.executeCommandList(context);
	swapChain.present();

}
