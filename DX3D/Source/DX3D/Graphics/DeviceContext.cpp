#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>

dx3d::DeviceContext::DeviceContext(const GraphicsResourceDesc& gDesc) 
	: GraphicsResource(gDesc)
{
	DX3DGraphicsLogErrorAndThrow(
		m_device.CreateDeferredContext(0, &m_context),
		"CreateDeferredContext failed from DeviceContext.cpp"
		);
}

void dx3d::DeviceContext::clearAndSetBackBuffer(const SwapChain& swapChain, const Vec4& color)
{
	//{ 0.0f, 0.2f, 0.4f, 1.0f };
	//{ color.x,color.y, color.z, color.w };
	f32 fColor[] = { color.x,color.y, color.z, color.w };
	auto rtv = swapChain.m_rtv.Get();

	m_context->ClearRenderTargetView(rtv, fColor);
	m_context->OMSetRenderTargets(1,&rtv, nullptr);
}
