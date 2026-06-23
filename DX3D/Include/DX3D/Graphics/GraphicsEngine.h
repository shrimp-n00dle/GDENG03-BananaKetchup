#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Core/Base.h>
#include <DX3D/Math/Vec3.h>
#include <DX3D/Math/Vec4.h>
#include <DX3D/Math/Mat4x4.h>

#include <DX3D/Graphics/RenderSystem.h>
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>
#include <DX3D/Graphics/VertexBuffer.h>
#include <DX3D/Graphics/IndexBuffer.h>
#include <fstream>

#include <DX3D/Game/World.h>
#include <DX3D/Game/Component.h>
#include <DX3D/Game/GameObject.h>

#include <DX3D/Component/TransformComponent.h>
#include <DX3D/Component/CubeComponent.h>
#include <DX3D/Component/CameraComponent.h>
#include <ranges>

#include <DX3D/Command/Command.h>
#include <vector>

#include <DX3D/Window/Window.h>

#include <random>

using namespace catsup;
namespace dx3d
{


	class GraphicsEngine final: public Base
	{
	public:
		explicit GraphicsEngine(const GraphicsEngineDesc& desc);
		virtual ~GraphicsEngine() override;

		void spawnTest(World& world);

		void render(const World& world, SwapChain& swapChain, f32 deltaTime);
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
			Mat4x4 view{};
			Mat4x4 proj{};
		};

	public:
		//For seatwork
		bool bSpawn = false;
		void callSpawn();

		int incCube = 0;
		void removeRecent();

		void closeProgram();


	public:
		RenderSystem& m_renderSystem;
		RefPtr<DeviceContext> m_deviceContext{};
		RefPtr<GraphicsPipelineState> m_pipeline{};
		RefPtr<VertexBuffer> m_vb{};
		RefPtr<VertexBuffer> m_vb2{};
		RefPtr<ConstantBuffer> m_cb{};
		RefPtr<ConstantBuffer> m_cb2{};
		RefPtr<IndexBuffer> m_ib{};

		friend class Window;
	};
}

