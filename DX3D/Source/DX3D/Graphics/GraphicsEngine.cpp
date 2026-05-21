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
	context.clearAndSetBackBuffer(swapChain, {1,0,0,1});

	auto& device = *m_renderSystem;
	device.executeCommandList(context);
	swapChain.present();

}
