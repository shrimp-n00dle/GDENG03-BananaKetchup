#include <DX3D/Game/Game.h>
#include <Windows.h>

void dx3d::Game::run()
{
	MSG msg;
	m_previousTime = std::chrono::steady_clock::now();
	while (isRunning)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				isRunning = false;
				break;
			}
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
		onInternalUpdate();
	}
}