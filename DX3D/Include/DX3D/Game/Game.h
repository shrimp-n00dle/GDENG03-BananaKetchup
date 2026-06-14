#pragma once
#include <DX3D/Core/Base.h>
#include <DX3D/Core/Core.h>
#include <chrono>

namespace dx3d
{
	class Game
	{
		dx3d_disable_copy_and_move(Game)
	public:
		explicit Game(const GameDesc& desc);
		virtual ~Game();

		virtual World& getWorld() noexcept final;
		virtual Logger& getLogger() noexcept final;
		//final - cannot be inheriated/override
		virtual void run() final;

	protected:
		virtual void onCreate() {}
		virtual void onUpdate(f32 deltaTime) {}

	private:
		void onInternalUpdate();

	private:
		UniquePtr<Logger> m_logger{};
		RefPtr<RenderSystem> m_renderSystem{};
		UniquePtr<Display> m_display{};
		UniquePtr<World> m_world{};
		UniquePtr<GraphicsEngine> m_graphicsEngine{};
		bool isRunning{ true };
		std::chrono::steady_clock::time_point m_previousTime{};
	};
}

