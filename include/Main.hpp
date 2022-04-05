#pragma once

#include <birb2d/Renderwindow.hpp>
#include <birb2d/Entity.hpp>
#include <birb2d/Font.hpp>
#include <birb2d/Scene.hpp>
#include "Window.hpp"
#include "Variables.hpp"

using namespace Birb;

static Window GameWindow("LD50.exe", Vector2int(width, height), 75, false);

/* Fonts */
static Font TitleFont(mononoki_bold, 64);
static Font MainMenuButtonFont(mononoki_bold, 40);
static Font bluescreenFontBig(appInfo.ResLocation + "/fonts/manaspace/manaspc.ttf", 64);
static Font bluescreenFontNormal(appInfo.ResLocation + "/fonts/manaspace/manaspc.ttf", 32);
static Font ramDownloadFont(mononoki_regular, 16);

/* Scenes */
static Scene MainMenuScene, EndScene, GameScene;

/** Main menu **/
void PlayGame();
void QuitGame(bool* ApplicationRunning);

/* Timers */
static Timer playTimer;
std::string PlayedTimeText();
static Timer windowSpawnTimer;
static double timeUntilNextWindow = 0;

static Entity titleText("Title text", Vector2int(50, 50), EntityComponent::Text("LD50.exe", &TitleFont, &Colors::White));
static Entity playButton("Play button", Vector2int(50, GameWindow.dimensions.y - 200), EntityComponent::Text("Play", &MainMenuButtonFont, &Colors::White, &Colors::DarkGray));
static Entity quitButton("Quit button", Vector2int(50, GameWindow.dimensions.y - 130), EntityComponent::Text("Quit", &MainMenuButtonFont, &Colors::White, &Colors::DarkGray));

/** Game **/
/* Functions */
void ToggleApplicationMenu();
static Rect wallpaper;

/* Fonts and entities */
void DownloadRam();
static int ramDownloaded;
static int ramDownloadSize = 256;
static bool downloadingRam = false;
static Entity taskBarButtonEntity("Taskbar button");
static Rect taskBar(0, height - 24, width, 24);
static Rect applicationMenu(0, 365, 200, height - 365 - taskBar.h);
static Line applicationMenuRightShadowLine(Vector2f(applicationMenu.x + applicationMenu.w, applicationMenu.y), Vector2f(applicationMenu.x + applicationMenu.w, applicationMenu.y + applicationMenu.h));
static Line applicationMenuRightLightLine(Vector2f(applicationMenu.x, applicationMenu.y), Vector2f(applicationMenu.x + applicationMenu.w, applicationMenu.y));
static Rect ramDownloaderBackground(10, applicationMenu.y + 10, applicationMenu.w - 20, 50);
static Entity ramDownloadButton("Ram download button", ramDownloaderBackground);
static Entity ramDownloaderText("Ram download text", Vector2int(0, 0), EntityComponent::Text("Download RAM", &ramDownloadFont, &Colors::Blue));
static Entity ramDownloadProgress("Ram downloading progressbar");

static Font taskBarButtonFont(mononoki_bold, 16);

static Entity taskBarButtonText("Task bar button text", Vector2int(7, height - 21), EntityComponent::Text("Start", &taskBarButtonFont, &Colors::Black));

/** Resource monitor **/
void UpdateResourceMonitor();
std::string CpuUsageText();
static Font resourceMonitorFont(mononoki_regular, 18);
static Rect resourceMonitorBackground(1050, 20, 210, 30);
static Entity ramCounterText("RAM usage counter", Vector2int(resourceMonitorBackground.x + 5, resourceMonitorBackground.y + 5), EntityComponent::Text("Ram: " + std::to_string(Variables::ramUsage) + "mb / " + std::to_string(Variables::totalRam) + "mb", &resourceMonitorFont, &Colors::Black));
//static Entity cpuCounterText("CPU usage counter", Vector2int(resourceMonitorBackground.x + 5, resourceMonitorBackground.y + 25), EntityComponent::Text(CpuUsageText(), &resourceMonitorFont, &Colors::Black));
