#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Core/Base.h>
//#include <DX3D/Math/Vec3.h>
#include <DX3D/Math/Vec4.h>
#include <DX3D/Math/Vertex.h>
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

		void reloadShaders(RenderSystem& device);

		RenderSystem& getRenderSystem() noexcept;

		void render(SwapChain& swapChain);

		void moveColors();
	public:
		std::shared_ptr<RenderSystem> m_renderSystem{};
	private:
		std::vector<Vec4> colorList;
		DeviceContextPtr m_deviceContext{};
		GraphicsPipelineStatePtr m_pipeline{};
		VertexBufferPtr m_vb{};

		//Triangle
		VertexBufferPtr m_vb2{};

		//Green Rectangle
		VertexBufferPtr m_vb3{};

		SpawnerPtr m_spawner{};
	};
}

