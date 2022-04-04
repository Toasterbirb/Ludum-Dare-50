#pragma once

#include <vector>
#include "Window.hpp"
#include <birb2d/UI.hpp>
#include <birb2d/Random.hpp>

namespace Game
{
	class WindowManager
	{
	public:
		WindowManager(UI* interface);
		void SpawnWindow(std::string winTitle);
		void RenderWindows();

	private:
		std::vector<Game::Window> windows;
		UI* interface;
		Random rand;
	};
}
