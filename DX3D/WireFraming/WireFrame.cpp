#include "WireFrame.h"

catsup::WireFrame::WireFrame()
{
	ZeroMemory(&wireframeDesc, sizeof(D3D11_RASTERIZER_DESC));

	wireframeDesc.FillMode = D3D11_FILL_WIREFRAME;
	wireframeDesc.CullMode = D3D11_CULL_NONE;
	wireframeDesc.FrontCounterClockwise = FALSE;
}

void catsup::WireFrame::drawWireFrame(ID3D11Device& device, DeviceContextPtr deviceContext)
{
	
	HRESULT hr = device.CreateRasterizerState(&wireframeDesc, _wf.GetAddressOf());
	if (FAILED(hr)) {
		// Handle error
	}

	//WIREFRAME STATE
	deviceContext.m_context.Get();//Get()->RSSetState(_wf.Get());

	// Draw your object(s)
	deviceContext->DrawIndexed(indexCount, 0, 0);

	// Restore default state afterwards (assuming you have a default state saved)
	deviceContext->RSSetState(defaultRasterizerState);
}
