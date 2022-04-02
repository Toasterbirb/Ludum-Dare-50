#include <birb2d/Timestep.hpp>
#include <birb2d/Logger.hpp>
#include <birb2d/UI.hpp>
#include "Main.hpp"

int main(int argc, char **argv)
{
    TimeStep timeStep;
    timeStep.Init(&window);

    /* Disable everything else but the main menu in the beginning */
    const int SCENE_COUNT = 3;

    MainMenu.Activate();
    Game.Deactivate();
    EndScreen.Deactivate();

    UI interface;

    /* Add some objects to the main menu */
    MainMenu.AddObject(&titleText);
    MainMenu.AddObject(&playButton);
    interface.AddButton(&playButton);
    playButton.clickComponent = EntityComponent::Click(PlayGame);

    /* Game variables */
    taskBar.color = 0x818181;

    /* Taskbar */
    Entity taskBarButtonEntity("Taskbar button");
    taskBarButtonEntity.clickComponent = EntityComponent::Click(ToggleApplicationMenu);

    /* taskBarButtonEntity */
    Rect taskBarButton(3, window.dimensions.y - 21, 100, 18);
    taskBarButton.color = 0xc3c3c3;
    taskBarButton.renderingPriority = 1;

    taskBarButtonEntity.rect = taskBarButton;
    interface.AddButton(&taskBarButtonEntity);

    /* taskBarButtonCenter */
    Rect taskBarButtonCenter(5, window.dimensions.y - 19, 96, 14);
    taskBarButtonCenter.color = 0xDCDCDC;
    taskBarButtonCenter.renderingPriority = 2;

    taskBarButtonText.renderingPriority = 3;

    applicationMenu.color = 0xA9A9A9;
    applicationMenu.active = false;

    Game.AddObject(&taskBar);
    Game.AddObject(&taskBarButton);
    Game.AddObject(&taskBarButtonCenter);
    Game.AddObject(&taskBarButtonText);
    Game.AddObject(&applicationMenu);

    /* Background */
    Rect wallpaper(0, 0, window.dimensions.x, window.dimensions.y);
    wallpaper.renderingPriority = -1;
    wallpaper.color = 0x008080;

    Game.AddObject(&wallpaper);

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

    Game.AddObject(&resourceMonitorBorder);
    Game.AddObject(&resourceMonitorBackground);
    Game.AddObject(&ramCounterText);
    Game.AddObject(&cpuCounterText);

    bool ApplicationRunning = true;
    while (ApplicationRunning)
    {
        timeStep.Start();
        while (timeStep.Running())
        {
            /* Handle input stuff */
            while (window.PollEvents())
            {
                window.EventTick(window.event, &ApplicationRunning);
                interface.PollButtons(window);

                if (window.event.type == SDL_MOUSEBUTTONDOWN)
                    Debug::Log(window.CursorPosition().toString());
            }

            timeStep.Step();
        }

        window.Clear();
        /* Handle rendering */

        /* Render scenes */
        MainMenu.Render();
        Game.Render();
        EndScreen.Render();

        /* End of rendering */
        window.Display();

        timeStep.End();
    }

    return 0;
}

void PlayGame()
{
    Debug::Log("Starting game");
    MainMenu.Deactivate();
    Game.Activate();
}

void ToggleApplicationMenu()
{
    applicationMenu.active = !applicationMenu.active;
}

std::string CpuUsageText()
{
	if (CPUusage <= 0)
		return "CPU: 0%";
	else
		return "CPU: " + std::to_string(CPUusage / CPUmax) + "%";
}
