#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/RenderSystem.h>
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>

using namespace dx3d;

dx3d::GraphicsEngine::GraphicsEngine(const GraphicsEngineDesc& desc): Base(desc.base)
{
	m_renderSystem = std::make_shared<RenderSystem>(RenderSystemDesc{m_logger});

	auto& device = *m_renderSystem;
	m_deviceContext = device.createDeviceContext();

	constexpr char shaderSourceCode[] =
		R"(
void VSMain()
{
float3 p = float4(1,1,1,1);
}
void PSMain()
{
}
		)";
	constexpr char shaderSourceName[] = "Basic";
	constexpr auto shaderSourceCodeSize = std::size(shaderSourceCode);

	auto vs = device.compileShader({shaderSourceName,shaderSourceCode, shaderSourceCodeSize,
		"VSMain", ShaderType::VertexShader});

	auto ps = device.compileShader({ shaderSourceName,shaderSourceCode, shaderSourceCodeSize,
	"PSMain", ShaderType::PixelShader });

	m_pipeline = device.createGraphicsPipelineState({*vs, *ps});
}


dx3d::GraphicsEngine::~GraphicsEngine()
{
}

RenderSystem& dx3d::GraphicsEngine::getRenderSystem()noexcept
{
	// TODO: insert return statement here
	return *m_renderSystem;
}

void dx3d::GraphicsEngine::render(SwapChain& swapChain)
{
	auto& context = *m_deviceContext;
	context.clearAndSetBackBuffer(swapChain, { 1, 0, 0, 1 });
	context.setGraphicsPipelineState(*m_pipeline);

	auto& device = *m_renderSystem;
	device.executeCommandList(context);
	swapChain.present();

}
