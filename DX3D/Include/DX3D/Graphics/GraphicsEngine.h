#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Core/Base.h>
#include <DX3D/Math/Vec3.h>
#include <DX3D/Math/Vec4.h>
#include <DX3D/Math/Mat4x4.h>
#include <vector>

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
	private:
		//MUST BE EXACT TO BASIC.HLSL or it wont work
		struct Vertex
		{
			Vec3 position;
			Vec4 color;
		};
		struct alignas(16) ConstantData
		{
			Mat4x4 world{};
		};

	private:
		RefPtr<RenderSystem> m_renderSystem{};
		RefPtr<DeviceContext> m_deviceContext{};
		RefPtr<GraphicsPipelineState> m_pipeline{};
		RefPtr<VertexBuffer> m_vb{};
		RefPtr<ConstantBuffer> m_cb{};

		f32 m_rot{}, m_scale{}, m_pos{ -1.0f };
	};
}

