#include "Windowmanager.hpp"

namespace Game
{
	WindowManager::WindowManager(UI* interface)
	{
		this->interface = interface;
	}

	void WindowManager::SpawnWindow(std::string winTitle)
	{
		Game::WindowOpts adWindowOpts(
			winTitle,
			Rect(rand.RandomInt(0, 900), rand.RandomInt(0, 570), rand.RandomInt(200, 320), rand.RandomInt(150, 320))
		);

		Game::Window adWindow(adWindowOpts);
		Vector2int contentWindowVector = Vector2int(0, 0);
		contentWindowVector.x += 0;
		Birb::Entity pogText = Birb::Entity("pogText", contentWindowVector, Birb::EntityComponent::Text("POG", &DefaultFont, &Birb::Colors::Blue));
		contentWindowVector.y += 20;
		//Birb::Entity wowText = Birb::Entity("wowText", contentWindowVector, Birb::EntityComponent::Text("Wow", &DefaultFont, &Birb::Colors::Blue));
		adWindow.AddChildComponent(pogText);
		//adWindow.AddChildComponent(wowText);
		adWindow.WireButtons(interface);

		windows.push_back(adWindow);
	}

	void WindowManager::RenderWindows()
	{
		for (int i = 0; i < windows.size(); i++)
		{
			windows[i].Render();
		}
	}
}
