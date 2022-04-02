using namespace Birb;

Window window("Birb2D project template", Vector2int(width, height), 75, false);

/* Fonts */
Font TitleFont(mononoki_bold, 64);
Font MainMenuButtonFont(mononoki_bold, 32);

/* Scenes */
Scene MainMenu, EndScreen, Game;

/** Main menu **/
void PlayGame();

Entity titleText("Title text", Vector2int(50, 50), EntityComponent::Text("Need for RAM: Crash incoming", &TitleFont, &Colors::White));
Entity playButton("Play button", Vector2int(50, 200), EntityComponent::Text("Play", &MainMenuButtonFont, &Colors::White, &Colors::DarkGray));

/** Game **/
/* Functions */
void ToggleApplicationMenu();

/* Fonts and entities */
Rect taskBar(0, height - 24, width, 24);
Rect applicationMenu(0, 365, 200, height - 365 - taskBar.h);
Font taskBarButtonFont(mononoki_bold, 16);
Entity taskBarButtonText("Task bar button text", Vector2int(7, height - 21), EntityComponent::Text("Start", &taskBarButtonFont, &Colors::Black));

/** Resource monitor **/
Font resourceMonitorFont(mononoki_regular, 18);
Rect resourceMonitorBackground(1050, 20, 210, 100);
Entity ramCounterText("Ram usage counter", Vector2int(resourceMonitorBackground.x + 5, resourceMonitorBackground.y + 5), EntityComponent::Text("Ram: " + std::to_string(ramUsage) + "mb / " + std::to_string(totalRam) + "mb", &resourceMonitorFont, &Colors::Black));
