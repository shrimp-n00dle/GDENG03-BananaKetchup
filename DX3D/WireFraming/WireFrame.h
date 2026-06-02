#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <DX3D/Core/Core.h>

using namespace dx3d;

namespace catsup
{
	class WireFrame
	{
	public:
		WireFrame();
		~WireFrame();

		void drawWireFrame(ID3D11Device& device, DeviceContextPtr deviceContext);
	private:
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> _wf{};
		D3D11_RASTERIZER_DESC wireframeDesc;
	};
}
