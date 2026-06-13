#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/RenderSystem.h>
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>
#include <DX3D/Graphics/VertexBuffer.h>
#include <DX3D/Graphics/IndexBuffer.h>
#include <DX3D/Math/Vec3.h>
#include <fstream>

using namespace catsup;

dx3d::GraphicsEngine::GraphicsEngine(const GraphicsEngineDesc& desc): Base(desc.base)
{
	m_renderSystem = std::make_shared<RenderSystem>(RenderSystemDesc{m_logger});

	auto& device = *m_renderSystem;
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
		//winding order: clockwise
		// 
		//front face indices
		0,1,2,  //first triangle
		2,3,0,  //second triangle
		//back face indices
		4,5,6,
		6,7,4,
		//top face indices
		1,6,5,
		5,2,1,
		//bottom face indices
		7,0,3,
		3,4,7,
		//right face indices
		3,2,5,
		5,4,3,
		//left face indices
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

dx3d::RenderSystem& dx3d::GraphicsEngine::getRenderSystem()noexcept
{
	// TODO: insert return statement here
	return *m_renderSystem;
}

void dx3d::GraphicsEngine::render(SwapChain& swapChain, f32 deltaTime)
{
	auto& context = *m_deviceContext;

	auto& cb = *m_cb;

	m_pos += deltaTime * 0.0f;
	m_rot += deltaTime * 0.707f;
	m_scale = std::abs(std::sin(m_rot));

	auto worldMat =
		Mat4x4::scale({ m_scale,m_scale,m_scale }) *
		Mat4x4::rotateX(m_rot) *
		Mat4x4::rotateY(m_rot) *
		Mat4x4::rotateZ(m_rot) *
		Mat4x4::translate({ m_pos,m_pos,0 });

	//orthographic camera setup
	auto size = swapChain.getSize();
	auto aspect = static_cast<f32>(size.width) / size.height;
	auto unitsPerScreenHeight = 2.0f;
	auto viewHeight = unitsPerScreenHeight;
	auto viewWidth = unitsPerScreenHeight * aspect;

	ConstantData data
	{
		worldMat,
		Mat4x4::orthoLH(viewWidth, viewHeight, -10.0f, 10.0f)
	};

	context.updateConstantBuffer(cb, &data);
	context.clearAndSetBackBuffer(swapChain, { 0.27f, 0.39f,0.55f, 1.0f });
	context.setGraphicsPipelineState(*m_pipeline);

	context.setViewportSize(swapChain.getSize());

	auto& vb = *m_vb;
	auto& ib = *m_ib;
	context.setVertexBuffer(vb);
	context.setConstantBuffer(cb);
	context.setIndexBuffer(ib);
	context.drawIndexedTriangleList(ib.getIndexListSize(), 0u, 0u);

	auto& device = *m_renderSystem;
	device.executeCommandList(context);
	swapChain.present();
}
