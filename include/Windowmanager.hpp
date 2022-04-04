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
		void SpawnWindow(Random rand);
		void RenderWindows();
		void ClearWindows();

	private:
		std::vector<Game::Window*> windows;
		UI* interface;

		static const int TITLE_COUNT = 11;
		const std::string titles[TITLE_COUNT] = {
			"Notification",
			"Click me!",
			"Hello World",
			"Attention required",
			"Message from your mom",
			"Untitled window",
			"LD50.exe",
			"Wannalaugh.exe",
			"...",
			":)",
			"SystemD"
	};

		static const int CONTENT_COUNT = 24;
		const std::string windowContents[CONTENT_COUNT] = {
			"Soo... this is some randomized text that will fill a window quite nicely",
			"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.",
			"There's only 7 hours left to finish this game...",
			"What can I put into these windows? I'm out of ideas...",
			"Segfault is just around the corner",
			"C++ is the best programming language out there BTW.",
			"This game was originally supposed to poke fun at how much ram Discord uses",
			"I wonder what causes these windows to popup",
			"That start button at the bottom left corner is quite scary",
			"Running out of RAM is similar to having a burnout. Computers have feelings too!",
			"Hmmh... I found your homework directory. Interesting :3",
			"I'd just like to interject for a moment.  What you're referring to as Linux, is in fact, GNU/Linux, or as I've recently taken to calling it, GNU plus Linux.",
			"void WindowManager::SpawnWindow()",
			"game.cpp",
			"main.cpp",
			"window.cpp",
			"windowmanager.cpp",
			"Do you know what to do when you get malware on your PC?",
			"Have you tried turning it off and back on again?",
			"How do you shutdown a PC when you can't access its powerplug...",
			"Jengi on suolasta",
			"I really hope you aren't going to download more ram. That would totally ruin my plans of overpowering this PC",
			"This PC has been pwned by your mom",
			"This game engine sucks btw #notprogrammer #notprogrammingadvice"
		};
	};
}
