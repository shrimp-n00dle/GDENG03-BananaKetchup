#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/RenderSystem.h>
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>
#include <DX3D/Graphics/VertexBuffer.h>
//#include <DX3D/Math/Vec3.h>
#include <fstream>
#include <DX3D/Math/BufferTimer.h>

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
		{ {-0.25f,0.25f,0.0f},  {1,0,0,1} },
		{ {0.25f,0.25f,0.0f},   {1,0,0,1} },

		
		{ {0.25f,0.25f,0.0f},   {1,0,0,1} },
		{ {0.25f,-0.25f,0.0f},  {1,0,0,1} },
		{ {-0.25f,-0.25f,0.0f}, {1,0,0,1} }
	};

	for (int i = 0; i < 6; i++)
	{
		colorList.push_back(vertextList[i].color);
	}

	D3D11_BUFFER_DESC buffDesc{};
	buffDesc.Usage = D3D11_USAGE_DYNAMIC;
	buffDesc.ByteWidth = static_cast<UINT>(sizeof(BufferTimer)+ (16 - (sizeof(BufferTimer) & 16)));
	buffDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buffDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	buffDesc.MiscFlags = 0;
	buffDesc.StructureByteStride = 0;

	m_vb = device.createVertexBuffer({vertextList, std::size(vertextList), sizeof(Vertex)});

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
	"PSMain", ShaderType::PixelShader });

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

	/*moveColors(dt);*/
	auto& context = *m_deviceContext;
	context.clearAndSetBackBuffer(swapChain, { 0.27f, 0.39f,0.55f, 1.0f });
	context.setGraphicsPipelineState(*m_pipeline);

	context.setViewportSize(swapChain.getSize());

	//TIme update
	BufferTimer timer;
	timer.delta_time = 0.0f;//getDeltaTime();
	std::cout << getDeltaTime() << std::endl;
	D3D11_MAPPED_SUBRESOURCE mappedR;
	context.getContext()->Map(cbuffer.Get(),0,D3D11_MAP_WRITE_DISCARD,0, &mappedR);
	CopyMemory(mappedR.pData, &timer, sizeof(BufferTimer));
	context.getContext()->Unmap(cbuffer.Get(),0);
	context.getContext()->VSSetConstantBuffers(0,1,cbuffer.GetAddressOf());

	reloadShaders(getRenderSystem());

	auto& vb = *m_vb;
	context.setVertexBuffer(vb);
	context.drawTriangleList(vb.getVertexListSize(),0u);

	auto& device = *m_renderSystem;
	device.executeCommandList(context);
	swapChain.present();
}

void dx3d::GraphicsEngine::moveColors(float dt)
{
	increment += dt;
	colorList.at(0).y = increment;
	colorList.at(1).y = increment;
	colorList.at(2).y = increment;
	colorList.at(3).y = increment;
	colorList.at(4).y = increment;
	colorList.at(5).y = increment;


}

void dx3d::GraphicsEngine::setDeltaTime(float dt)
{
	delta_time = dt;
}

float dx3d::GraphicsEngine::getDeltaTime()
{
	return delta_time;
}
