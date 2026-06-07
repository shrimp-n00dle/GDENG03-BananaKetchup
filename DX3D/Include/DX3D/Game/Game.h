#pragma once
#include <DX3D/Core/Base.h>
#include <DX3D/Core/Core.h>
#include <DX3D/Graphics/GameTimer.h>


namespace dx3d
{
	class Game : public Base
	{
	public:
		explicit Game(const GameDesc& desc);
		virtual ~Game() override;

		//final - cannot be inheriated/override
		virtual void run() final;

	private:
		void onInternalUpdate();

	private:
		GameTimer timer;

		std::unique_ptr<Logger> m_loggerPtr{};
		std::unique_ptr<GraphicsEngine> m_graphicsEngine{};
		std::unique_ptr<Display> m_display{};
		bool isRunning{ true };
	};
}

