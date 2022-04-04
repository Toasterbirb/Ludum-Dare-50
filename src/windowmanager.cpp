#include "Windowmanager.hpp"

namespace Game
{
	WindowManager::WindowManager(UI* interface)
	{
		this->interface = interface;
	}

	void WindowManager::SpawnWindow(Random rand)
	{
		Rect randomRect(rand.RandomInt(0, 900), rand.RandomInt(0, 570), rand.RandomInt(200, 320), rand.RandomInt(150, 320));
		Game::WindowOpts adWindowOpts(titles[rand.RandomInt(0, TITLE_COUNT - 1)], randomRect);

		Game::Window *adWindow = new Window(adWindowOpts, rand);
		Vector2int contentWindowVector = Vector2int(0, 0);
		contentWindowVector.x += 0;
		Birb::Entity pogText = Birb::Entity("pogText", contentWindowVector, Birb::EntityComponent::Text("", &DefaultFont, &Birb::Colors::Blue));
		pogText.textComponent.wrapLength = randomRect.w - 25;

		/* Update the text entity so that new wrapping setting takes effect, since its not fully implemented 
		 * properly yet*/
		if (rand.RandomInt(0, 4) == 0)
			pogText.SetText("This window used up " + std::to_string(adWindow->windowRamUsage) + " megabytes of ram BTW");
		else if (rand.RandomInt(0, 4) == 0)
			pogText.SetText("Hello " + Variables::username);
		else
			pogText.SetText(windowContents[rand.RandomInt(0, CONTENT_COUNT - 1)]);

		contentWindowVector.y += 20;
		//Birb::Entity wowText = Birb::Entity("wowText", contentWindowVector, Birb::EntityComponent::Text("Wow", &DefaultFont, &Birb::Colors::Blue));
		adWindow->AddChildComponent(pogText);
		// adWindow->AddChildComponent(wowText);
		adWindow->WireButtons(interface);

		windows.push_back(adWindow);
	}

	void WindowManager::RenderWindows()
	{
		for (int i = 0; i < windows.size(); i++)
		{
			if (windows[i]->windowClosed == false)
				windows[i]->Render();
		}
	}

	void WindowManager::ClearWindows()
	{
		for (int i = 0; i < windows.size(); i++)
		{
			windows[i]->ClearScenes();
			//delete windows[i];
		}

		windows.clear();
	}
}
