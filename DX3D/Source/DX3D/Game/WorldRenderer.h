#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Core/Base.h>
#include <DX3D/Math/Vec3.h>
#include <DX3D/Math/Vec4.h>
#include <DX3D/Math/Vec2.h>
#include <DX3D/Math/Mat4x4.h>
#include <vector>

#include <DX3D/Graphics/ImGui/imgui.h>
#include <DX3D/Graphics/ImGui/imgui_impl_win32.h>
#include <DX3D/Graphics/ImGui/imgui_impl_dx11.h>
#include <d3d11.h>
#include <tchar.h>

namespace dx3d
{
	class WorldRenderer final: public Base
	{
	public:
		explicit WorldRenderer(const WorldRendererDesc& desc);
		void render(const World& world, SwapChain& swapChain, f32 deltaTime, ImDrawData* uiData);
	private:
		struct alignas(16) ObjectData
		{
			Mat4x4 world{};
		};
		struct alignas(16) CameraData
		{
			Mat4x4 view{};
			Mat4x4 proj{};
		};
	public:
		//For seatwork
		bool bSpawn = false;
		//void callSpawn();

		int incCube = 0;
		//void removeRecent();

		//void closeProgram();

	private:
		GraphicsDevice& m_graphicsDevice;
		RefPtr<DeviceContext> m_deviceContext{};
		RefPtr<ConstantBuffer> m_cameraCb{};
		RefPtr<ConstantBuffer> m_objectCb{};
		RefPtr<ConstantBuffer> m_materialCb{};
		RefPtr<Sampler> m_sampler{};

		std::vector<Texture*> m_textures{};
	};
}

