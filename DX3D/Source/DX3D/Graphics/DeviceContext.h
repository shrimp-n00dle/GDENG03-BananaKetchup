#pragma once
#include <DX3D/Graphics/GraphicsResource.h>
#include <DX3D/Math/Vec4.h>

namespace dx3d
{
	class DeviceContext final: public GraphicsResource
	{
	public:
		explicit DeviceContext(const GraphicsResourceDesc& gDesc);
		void clearAndSetBackBuffer(const SwapChain& swapChain, const Vec4& color);
		void setGraphicsPipelineState(const GraphicsPipelineState& pipeline);
		void setGraphicsPipelineStateSphere(const GraphicsPipelineState& pipeline);
		void setVertexBuffer(const VertexBuffer& buffer);
		void setIndexBuffer(const IndexBuffer& buffer);
		void setViewportSize(const Rect& size);

		//Constant Buffers
		void setConstantBuffer(const ConstantBuffer& buffer);
		void updateConstantBuffer(const ConstantBuffer& buffer, const void* data);

		void drawTriangleList(ui32 vertextCount, ui32 startVertexLocation);

		void drawIndexedTriangleList(ui32 indexCount, ui32 startVertexIndex, ui32 startIndexLocation);

		Microsoft::WRL::ComPtr<ID3D11DeviceContext> getContext();

	private:
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_context{};
		friend class RenderSystem;
	};
}

