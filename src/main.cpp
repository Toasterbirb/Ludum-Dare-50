#include <birb2d/Timestep.hpp>
#include <birb2d/Logger.hpp>
#include <birb2d/UI.hpp>
#include <birb2d/Vector.hpp>
#include <birb2d/Random.hpp>
#include "Main.hpp"
#include "Windowmanager.hpp"
#include <birb2d/Diagnostics.hpp>

int main(int argc, char **argv)
{
	TimeStep timeStep;
	timeStep.Init(&GameWindow);

	/* Disable everything else but the main menu in the beginning */
	const int SCENE_COUNT = 3;

	MainMenuScene.Activate();
	GameScene.Deactivate();
	EndScene.Deactivate();

	UI interface;

	/* Add some objects to the main menu */
	MainMenuScene.AddObject(&titleText);
	MainMenuScene.AddObject(&playButton);
	interface.AddButton(&playButton);
	playButton.clickComponent = EntityComponent::Click(PlayGame);

	/* Game variables */
	taskBar.color = 0x818181;

	/* Taskbar */
	Entity taskBarButtonEntity("Taskbar button");
	taskBarButtonEntity.clickComponent = EntityComponent::Click(ToggleApplicationMenu);

	/* taskBarButtonEntity */
	Rect taskBarButton(3, GameWindow.dimensions.y - 21, 100, 18);
	taskBarButton.color = 0xc3c3c3;
	taskBarButton.renderingPriority = 1;

	taskBarButtonEntity.rect = taskBarButton;
	interface.AddButton(&taskBarButtonEntity);

	/* taskBarButtonCenter */
	Rect taskBarButtonCenter(5, GameWindow.dimensions.y - 19, 96, 14);
	taskBarButtonCenter.color = 0xDCDCDC;
	taskBarButtonCenter.renderingPriority = 2;

	taskBarButtonText.renderingPriority = 3;

	Entity playTimerIndicator("playTimeIndicator", Vector2int(GameWindow.dimensions.x - 200, (int)taskBarButton.y), EntityComponent::Text(PlayedTimeText(), &DefaultFont, &Colors::White, &Colors::DarkGray));

	applicationMenu.color = 0xA9A9A9;
	applicationMenu.active = false;

	GameScene.AddObject(&taskBar);
	GameScene.AddObject(&taskBarButton);
	GameScene.AddObject(&taskBarButtonCenter);
	GameScene.AddObject(&taskBarButtonText);
	GameScene.AddObject(&playTimerIndicator);
	GameScene.AddObject(&applicationMenu);

	/* Background */
	Rect wallpaper(0, 0, GameWindow.dimensions.x, GameWindow.dimensions.y);
	wallpaper.renderingPriority = -1;
	wallpaper.color = 0x008080;

	GameScene.AddObject(&wallpaper);

	/* Resource monitor */
	Rect resourceMonitorBorder = resourceMonitorBackground;
	resourceMonitorBorder.x -= 4;
	resourceMonitorBorder.y -= 4;
	resourceMonitorBorder.w += 8;
	resourceMonitorBorder.h += 8;
	resourceMonitorBorder.color = 0x9E9E9E;

	resourceMonitorBackground.color = 0x818181;
	resourceMonitorBackground.renderingPriority = 1;

	ramCounterText.renderingPriority = 2;
	cpuCounterText.renderingPriority = 2;

	GameScene.AddObject(&resourceMonitorBorder);
	GameScene.AddObject(&resourceMonitorBackground);
	GameScene.AddObject(&ramCounterText);
	GameScene.AddObject(&cpuCounterText);

	Game::WindowManager winManager(&interface);
	for (int i = 0; i < 10; i++)
		winManager.SpawnWindow("LOL");

	Random rand;
	Game::WindowOpts adWindowOpts(
		"TEST",
		Rect(rand.RandomInt(0, 900), rand.RandomInt(0, 570), rand.RandomInt(200, 320), rand.RandomInt(150, 320))
	);

	Game::Window adWindow(adWindowOpts);
	Vector2int contentWindowVector = Vector2int(0, 0);
	contentWindowVector.x += 0;
	Birb::Entity pogText = Birb::Entity("pogText", contentWindowVector, Birb::EntityComponent::Text("POG", &DefaultFont, &Birb::Colors::Blue));
	contentWindowVector.y += 20;
	Birb::Entity wowText = Birb::Entity("wowText", contentWindowVector, Birb::EntityComponent::Text("Wow", &DefaultFont, &Birb::Colors::Blue));
	adWindow.AddChildComponent(pogText);
	adWindow.AddChildComponent(wowText);
	adWindow.WireButtons(&interface);


	bool ApplicationRunning = true;
	while (ApplicationRunning)
	{
		timeStep.Start();
		while (timeStep.Running())
		{
			/* Handle input stuff */
			while (GameWindow.PollEvents())
			{
				GameWindow.EventTick(GameWindow.event, &ApplicationRunning);
				interface.PollButtons(GameWindow);

				if (GameWindow.event.type == SDL_MOUSEBUTTONDOWN)
					Debug::Log(GameWindow.CursorPosition().toString());
			}

			timeStep.Step();
		}

		playTimerIndicator.SetText(PlayedTimeText());
		GameWindow.Clear();
		/* Handle rendering */

		/* Render scenes */
		MainMenuScene.Render();
		GameScene.Render();
		EndScene.Render();
		if (GameScene.isActive()) {
			winManager.RenderWindows();
			//adWindow.Render();
		}

		/* End of rendering */
		GameWindow.Display();

		timeStep.End();
	}

	return 0;
}

void PlayGame()
{
	Debug::Log("Starting game");
	playTimer.Start();
	ClickSound.play();
	MainMenuScene.Deactivate();
	GameScene.Activate();
}

void ToggleApplicationMenu()
{
	ClickSound.play();
	applicationMenu.active = !applicationMenu.active;
}

std::string CpuUsageText()
{
	if (CPUusage <= 0)
		return "CPU: 0%";
	else
		return "CPU: " + std::to_string(CPUusage / CPUmax) + "%";
}

std::string PlayedTimeText()
{
	return "Time Played: " + playTimer.DigitalFormat();
}
