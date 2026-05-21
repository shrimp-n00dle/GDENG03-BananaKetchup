#include <DX3D/Graphics/RenderSystem.h>
#include <DX3D/Graphics/GraphicsLogUtils.h>
#include <DX3D/Graphics/SwapChain.h>
#include <DX3D/Graphics/DeviceContext.h>

using namespace dx3d;

dx3d::RenderSystem::RenderSystem(const RenderSystemDesc& desc) : Base(desc.base)
{
	D3D_FEATURE_LEVEL featureLevel{};
	UINT createDeviceFlags{};

	#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	#endif


	DX3DGraphicsLogErrorAndThrow(D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, NULL,
		0, D3D11_SDK_VERSION,
		&m_d3dDevice, &featureLevel, &m_d3dContext), "Direct3D11 initialization failed.");

	DX3DGraphicsLogErrorAndThrow
		(m_d3dDevice->QueryInterface(IID_PPV_ARGS(&m_dxgiDevice)),
		"QueryInterface failed to retrieve IDXGIDevice.");

	DX3DGraphicsLogErrorAndThrow
	(m_dxgiDevice->GetParent(IID_PPV_ARGS(&m_dxgiAdapter)),
		"GetParent() failed to retrieve IDXGIAdapter.");

	DX3DGraphicsLogErrorAndThrow
	(m_dxgiAdapter->GetParent(IID_PPV_ARGS(&m_dxgiFactory)),
		"GetParent() failed to retrieve IDXGIFactory.");
}

dx3d::RenderSystem::~RenderSystem()
{
}

SwapChainPtr dx3d::RenderSystem::createSwapChain(const SwapChainDesc& desc)
{
	return std::make_shared<SwapChain>(desc,getGraphicsResourceDesc());
}

DeviceContextPtr dx3d::RenderSystem::createDeviceContext()
{
	return std::make_shared<DeviceContext>(getGraphicsResourceDesc());
}

void dx3d::RenderSystem::executeCommandList(DeviceContext& context)
{
	Microsoft::WRL::ComPtr<ID3D11CommandList> list{};
	DX3DGraphicsLogErrorAndThrow(
		context.m_context->FinishCommandList(false, &list),
		"FinishCommandList() failed from RenderSystem.cpp");
	
	m_d3dContext->ExecuteCommandList(list.Get(), false);
}

GraphicsResourceDesc dx3d::RenderSystem::getGraphicsResourceDesc() const noexcept
{
	return { {m_logger},shared_from_this(), *m_d3dDevice.Get(), *m_dxgiFactory.Get() };
}
