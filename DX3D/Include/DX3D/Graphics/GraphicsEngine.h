#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Core/Base.h>
#include <DX3D/Math/Vec3.h>
#include <DX3D/Math/Vec4.h>


//THE APPWINDOW ON THE PARDCODE TUTORIAL
namespace dx3d
{
	class GraphicsEngine final: public Base
	{
	public:
		explicit GraphicsEngine(const GraphicsEngineDesc& desc);
		virtual ~GraphicsEngine() override;

		RenderSystem& getRenderSystem() noexcept;

		void render(SwapChain& swapChain);
	private:
		//MUST BE EXACT TO BASIC.HLSL or it wont work
		struct Vertex
		{
			Vec3 position;
			Vec4 color;
		};
	private:
		std::shared_ptr<RenderSystem> m_renderSystem{};
		DeviceContextPtr m_deviceContext{};
		GraphicsPipelineStatePtr m_pipeline{};
		VertexBufferPtr m_vb{};

		//Triangle
		VertexBufferPtr m_vb2{};

		//Green Rectangle
		VertexBufferPtr m_vb3{};

		ConstantBufferPtr m_cb{};
	};
}

