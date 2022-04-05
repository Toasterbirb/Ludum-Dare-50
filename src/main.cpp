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
	bool ApplicationRunning = true;

	/* Disable everything else but the main menu in the beginning */
	const int SCENE_COUNT = 3;

	MainMenuScene.Activate();
	GameScene.Deactivate();
	EndScene.Deactivate();

	UI interface;

	/* Add some objects to the main menu */
	SDL_Texture* mainMenuBackground = Resources::LoadTexture(appInfo.ResLocation + "/sprites/main_menu.png");
	Entity mainMenuBackgroundEntity("Ḿain menu background entity", Rect(0, 0, 1280, 720), mainMenuBackground);
	MainMenuScene.AddObject(&mainMenuBackgroundEntity);
	MainMenuScene.AddObject(&titleText);
	MainMenuScene.AddObject(&playButton);
	MainMenuScene.AddObject(&quitButton);
	interface.AddButton(&playButton);
	interface.AddButton(&quitButton);
	playButton.clickComponent = EntityComponent::Click(PlayGame);

	std::function<void()> quitHandler = std::bind(QuitGame, &ApplicationRunning);
	quitButton.clickComponent = EntityComponent::Click(quitHandler);

	/* Add some objects to the end scene */
	Rect blueScreenBackground(0, 0, 1280, 720, 0x000082);
	Entity blueScreenTitle("Bluescreen title", Vector2int(50, 50), EntityComponent::Text("Game over!", &bluescreenFontBig, &Colors::White));
	Entity blueScreenText("Bluescreen text", Vector2int(55, 140), EntityComponent::Text("", &bluescreenFontNormal, &Colors::White));
	Entity blueScreenContinue("Bluescreen continue", Vector2int(55, 140), EntityComponent::Text("Hit SPACE to reboot", &bluescreenFontNormal, &Colors::White));
	blueScreenContinue.CenterRelativeTo(Rect(0, 400, 1280, 320));
	EndScene.AddObject(&blueScreenBackground);
	EndScene.AddObject(&blueScreenTitle);
	EndScene.AddObject(&blueScreenText);
	EndScene.AddObject(&blueScreenContinue);

	/* Game variables */
	taskBar.color = 0x818181;

	/* Taskbar */
	taskBarButtonEntity.clickComponent = EntityComponent::Click(ToggleApplicationMenu);
	taskBarButtonEntity.clickComponent.active = false;

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


	GameScene.AddObject(&taskBar);
	GameScene.AddObject(&taskBarButton);
	GameScene.AddObject(&taskBarButtonCenter);
	GameScene.AddObject(&taskBarButtonText);
	GameScene.AddObject(&playTimerIndicator);

	/* Taskbar menu ram downloader */
	applicationMenu.renderingPriority = 3;
	applicationMenu.color = 0xA9A9A9;
	applicationMenu.active = false;
	GameScene.AddObject(&applicationMenu);

	ramDownloaderBackground.active = false;
	ramDownloaderBackground.renderingPriority = 4;
	ramDownloaderBackground.color = 0xCAECCD;
	GameScene.AddObject(&ramDownloaderBackground);

	ramDownloadButton.active = false;
	ramDownloadButton.clickComponent = EntityComponent::Click(DownloadRam);
	GameScene.AddObject(&ramDownloadButton);
	interface.AddButton(&ramDownloadButton);

	ramDownloaderText.renderingPriority = 5;
	ramDownloaderText.active = false;
	ramDownloaderText.CenterRelativeTo(ramDownloaderBackground);
	GameScene.AddObject(&ramDownloaderText);

	ramDownloadProgress.active = false;
	ramDownloadProgress.rect = Rect(ramDownloaderBackground.x, ramDownloaderBackground.y + ramDownloaderBackground.h + 10, ramDownloaderBackground.w, 15);
	ramDownloadProgress.progressBarComponent = EntityComponent::ProgressBar(2, &Colors::White, &Colors::DarkGray, &Colors::Green);
	ramDownloadProgress.renderingPriority = 6;
	ramDownloadProgress.progressBarComponent.minValue = 0;
	ramDownloadProgress.progressBarComponent.maxValue = 100;
	ramDownloadProgress.progressBarComponent.value = 45;
	GameScene.AddObject(&ramDownloadProgress);

	applicationMenuRightShadowLine.color = Colors::Black;
	applicationMenuRightShadowLine.renderingPriority = 5;
	applicationMenuRightShadowLine.active = false;
	GameScene.AddObject(&applicationMenuRightShadowLine);

	applicationMenuRightLightLine.color = Colors::White;
	applicationMenuRightLightLine.renderingPriority = 5;
	applicationMenuRightLightLine.active = false;
	GameScene.AddObject(&applicationMenuRightLightLine);


	/* Background */
	wallpaper = Rect(0, 0, GameWindow.dimensions.x, GameWindow.dimensions.y);
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
	//cpuCounterText.renderingPriority = 2;

	GameScene.AddObject(&resourceMonitorBorder);
	GameScene.AddObject(&resourceMonitorBackground);
	GameScene.AddObject(&ramCounterText);
	//GameScene.AddObject(&cpuCounterText);

	Random rand;
	Game::WindowManager winManager(&interface);
	timeUntilNextWindow = rand.RandomFloat(0.5, 3);

	
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

				/* Check if we are in the end scene */
				if (EndScene.isActive())
				{
					/* Check for spacebar click */
					if (GameWindow.event.type == SDL_KEYDOWN && GameWindow.event.key.keysym.sym == SDLK_SPACE)
					{
						Variables::totalRam = 1024;
						taskBarButtonEntity.clickComponent.active = true;
						GameScene.Activate();
						EndScene.Deactivate();
						playTimer.Start();
					}
				}
			}

			timeStep.Step();
		}

		if (GameScene.isActive())
		{
			if (Variables::ramUsage > Variables::totalRam)
			{
				winManager.ClearWindows();
				Variables::ramUsage = 0;
				GameScene.Deactivate();
				playTimer.Stop();
				taskBarButtonEntity.clickComponent.active = false;

				blueScreenText.SetText("Your PC ran out of RAM.\nYou managed to keep it alive for " + playTimer.DigitalFormat());

				EndScene.Activate();
			}
			else
			{
				/* Ram downloading */
				if (downloadingRam)
				{
					ramDownloaded += timeStep.deltaTime * 200;

					if (ramDownloaded > ramDownloadSize)
					{
						Variables::totalRam += ramDownloadSize;
						ramDownloadProgress.active = false;
						downloadingRam = false;
						RamUpgrade.play();
					}
					else if (ramDownloaded % 32 == 0)
					{
						ramDownloadProgress.progressBarComponent.value = ramDownloaded;
					}
				}
				/* --------------- */

				playTimerIndicator.SetText(PlayedTimeText());
				UpdateResourceMonitor();
			}
		}
		
		GameWindow.Clear();
		/** Handle rendering **/

		/* Render scenes */
		MainMenuScene.Render();
		GameScene.Render();
		EndScene.Render();
		if (GameScene.isActive())
		{
			if (windowSpawnTimer.ElapsedSeconds() > timeUntilNextWindow)
			{
				windowSpawnTimer.Start();
				timeUntilNextWindow = rand.RandomFloat(0.1, 5.0 - (playTimer.ElapsedSeconds() * 0.05));
				timeUntilNextWindow = Math::Clamp(timeUntilNextWindow, 0.1, 5.0);

				/* Spawn a new window */
				 winManager.SpawnWindow(rand);
				 PopupSound.play();
			}

			winManager.RenderWindows();
			//adWindow.Render();
		}

		/** End of rendering **/
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
	windowSpawnTimer.Start();
	taskBarButtonEntity.clickComponent.active = true;
}

void QuitGame(bool* ApplicationRunning)
{
	*ApplicationRunning = false;
}

void ToggleApplicationMenu()
{
	ClickSound.play();
	applicationMenu.active = !applicationMenu.active;
	ramDownloaderBackground.active = !ramDownloaderBackground.active;
	ramDownloaderText.active = !ramDownloaderText.active;
	ramDownloadButton.active = !ramDownloadButton.active;
	applicationMenuRightShadowLine.active = !applicationMenuRightShadowLine.active;
	applicationMenuRightLightLine.active = !applicationMenuRightLightLine.active;

	if (!downloadingRam)
		ramDownloadProgress.active = false;
	else
		ramDownloadProgress.active = applicationMenu.active;
}

void DownloadRam()
{
	downloadingRam = true;
	ramDownloadProgress.progressBarComponent.value = 0;

	ramDownloaded = 0;

	ramDownloadProgress.progressBarComponent.maxValue = ramDownloadSize;
	ramDownloadProgress.active = true;
}

std::string CpuUsageText()
{
	if (Variables::CPUusage <= 0)
		return "CPU: 0%";
	else
		//return "CPU: " + std::to_string(Variables::CPUusage) + "%";
		return "CPU: " + std::to_string(Variables::CPUusage / Variables::CPUmax) + "%";
}

std::string PlayedTimeText()
{
	return "Time Played: " + playTimer.DigitalFormat();
}

void UpdateResourceMonitor()
{
	float interpolation = 0;
	if (Variables::ramUsage != 0)
		interpolation = ((float)Variables::ramUsage / (float)Variables::totalRam);
	wallpaper.color.r = Math::Lerp(0, 128, interpolation);
	wallpaper.color.g = Math::Lerp(128, 0, interpolation);
	wallpaper.color.b = Math::Lerp(128, 0, interpolation);
	ramCounterText.SetText("Ram: " + std::to_string(Variables::ramUsage) + "mb / " + std::to_string(Variables::totalRam) + "mb");
	//cpuCounterText.SetText(CpuUsageText());
}
