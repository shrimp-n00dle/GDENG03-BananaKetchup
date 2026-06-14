#include <DX3D/Graphics/RenderSystem.h>
#include <DX3D/Graphics/GraphicsLogUtils.h>
#include <DX3D/Graphics/SwapChain.h>
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/ShaderBinary.h>
#include <DX3D/Graphics/GraphicsPipelineState.h>
#include <DX3D/Graphics/VertexBuffer.h>
#include <DX3D/Graphics/IndexBuffer.h>
#include <DX3D/Graphics/VertexShaderSignature.h>
#include <DX3D/Graphics/ConstantBuffer.h>

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

RefPtr<SwapChain> dx3d::RenderSystem::createSwapChain(const SwapChainDesc& desc)
{
	return std::make_shared<SwapChain>(desc,getGraphicsResourceDesc());
}

RefPtr<DeviceContext> dx3d::RenderSystem::createDeviceContext()
{
	return std::make_shared<DeviceContext>(getGraphicsResourceDesc());
}

RefPtr<ShaderBinary> dx3d::RenderSystem::compileShader(const ShaderCompileDesc& desc)
{
	return std::make_shared<ShaderBinary>(desc, getGraphicsResourceDesc());
}

RefPtr<GraphicsPipelineState> dx3d::RenderSystem::createGraphicsPipelineState(const GraphicsPipelineStateDesc& desc)
{
	return std::make_shared<GraphicsPipelineState>(desc, getGraphicsResourceDesc());
}

RefPtr<VertexBuffer> dx3d::RenderSystem::createVertexBuffer(const VertexBufferDesc& desc)
{
	return std::make_shared<VertexBuffer>(desc, getGraphicsResourceDesc());
}

RefPtr<VertexShaderSignature> dx3d::RenderSystem::createVertexShaderSignature(const VertexShaderSignatureDesc& desc)
{
	return std::make_shared<VertexShaderSignature>(desc, getGraphicsResourceDesc());
}

RefPtr<ConstantBuffer> dx3d::RenderSystem::createConstantBuffer(const ConstantBufferDesc& desc)
{
	return std::make_shared<ConstantBuffer>(desc, getGraphicsResourceDesc());
}

RefPtr<IndexBuffer> dx3d::RenderSystem::createIndexBuffer(const IndexBufferDesc& desc)
{
	return std::make_shared<IndexBuffer>(desc, getGraphicsResourceDesc());
}

void dx3d::RenderSystem::executeCommandList(DeviceContext& context)
{
	Microsoft::WRL::ComPtr<ID3D11CommandList> list{};
	auto hr = context.m_context->FinishCommandList(false, &list);
	if (FAILED(hr))
	{
		DX3DLogError("FinishCommandList failed.");
		return;
	}
	
	m_d3dContext->ExecuteCommandList(list.Get(), false);
}

GraphicsResourceDesc dx3d::RenderSystem::getGraphicsResourceDesc() const noexcept
{
	return { {m_logger},shared_from_this(), *m_d3dDevice.Get(), *m_dxgiFactory.Get() };
}
