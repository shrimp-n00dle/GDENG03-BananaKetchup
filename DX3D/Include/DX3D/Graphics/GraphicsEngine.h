#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Core/Base.h>
#include <DX3D/Math/Vec3.h>
#include <DX3D/Math/Vec4.h>
#include <vector>
#include <DX3D/Graphics/Spawner.h>

using namespace catsup;
namespace dx3d
{


	class GraphicsEngine final: public Base
	{
	public:
		explicit GraphicsEngine(const GraphicsEngineDesc& desc);
		virtual ~GraphicsEngine() override;

		RenderSystem& getRenderSystem() noexcept;

		void render(SwapChain& swapChain, f32 deltaTime);
	public:
		std::shared_ptr<RenderSystem> m_renderSystem{};
	private:
		//MUST BE EXACT TO BASIC.HLSL or it wont work
		struct Vertex
		{
			Vec3 position;
			Vec4 color;
		};
		struct alignas(16) ConstantData
		{
			f32 scale{};
		};

	private:
		RefPtr<RenderSystem> m_graphicsDevice{};
		RefPtr<DeviceContext> m_deviceContext{};
		RefPtr<GraphicsPipelineState> m_pipeline{};
		RefPtr<VertexBuffer> m_vb{};
		RefPtr<ConstantBuffer> m_cb{};

		f32 m_sum{};
		f32 m_scale{};
	};
}

