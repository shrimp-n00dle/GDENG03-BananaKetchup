#pragma once
#include <DX3D/Core/Base.h>
#include <DX3D/Core/Core.h>
#include <DX3D/Command/Command.h>
#include <chrono>

#include <DX3D/GUI/AboutWin.h>
#include <DX3D/GUI/WinBase.h>
#include <DX3D/GUI/ColorWin.h>
#include <DX3D/GUI/MenuBar.h>

//Physics System
#include <reactphysics3d/reactphysics3d.h>


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
		virtual InputSystem& getInputSystem() noexcept final;
		virtual ResourceManager& getResourceManager() noexcept final;

		//final - cannot be inheriated/override
		virtual void run() final;
	protected:
		virtual void onCreate() {}
		virtual void onUpdate(f32 deltaTime) {}
	private:
		void onInternalUpdate();


	protected:
		MenuBar* menuBar = new MenuBar();
		ColorWin* colorWin = new ColorWin();
		AboutWin* aboutWin = new AboutWin();
		UniquePtr<Logger> m_logger{};
		UniquePtr<InputSystem> m_inputSystem{};
		RefPtr<GraphicsDevice> m_graphicsDevice{};
		UniquePtr<Display> m_display{};
		UniquePtr<ResourceManager> m_resourceManager{};
		//RefPtr<ResourceManager> m_resourceManager{};
		UniquePtr<World> m_world{};	
		
		UniquePtr<WorldRenderer> m_worldRenderer{};

		bool m_isRunning{ true };

		std::chrono::steady_clock::time_point m_previousTime{};

		reactphysics3d::PhysicsCommon* physicsCommon;
		reactphysics3d::PhysicsWorld* physicsWorld;

	};
}
