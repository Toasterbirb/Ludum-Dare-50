#pragma once

#include <birb2d/Renderwindow.hpp>
#include <birb2d/Entity.hpp>
#include <birb2d/Font.hpp>
#include <birb2d/Scene.hpp>
#include "Window.hpp"
#include "Variables.hpp"

using namespace Birb;

static Window window("Birb2D project template", Vector2int(width, height), 75, false);
static Game::WindowOpts adWindowOpts(
		"This is an advertisement",
		Rect(100, 100, 300, 300)
);

/* Fonts */
static Font TitleFont(mononoki_bold, 64);
static Font MainMenuButtonFont(mononoki_bold, 32);

/* Scenes */
static Scene MainMenuScene, EndScene, GameScene;

/** Main menu **/
void PlayGame();

static Entity titleText("Title text", Vector2int(50, 50), EntityComponent::Text("Need for RAM: Crash incoming", &TitleFont, &Colors::White));
static Entity playButton("Play button", Vector2int(50, 200), EntityComponent::Text("Play", &MainMenuButtonFont, &Colors::White, &Colors::DarkGray));

/** Game **/
/* Functions */
void ToggleApplicationMenu();

/* Fonts and entities */
static Rect taskBar(0, height - 24, width, 24);
static Rect applicationMenu(0, 365, 200, height - 365 - taskBar.h);
static Font taskBarButtonFont(mononoki_bold, 16);
static Entity taskBarButtonText("Task bar button text", Vector2int(7, height - 21), EntityComponent::Text("Start", &taskBarButtonFont, &Colors::Black));

/** Resource monitor **/

std::string CpuUsageText();
static Font resourceMonitorFont(mononoki_regular, 18);
static Rect resourceMonitorBackground(1050, 20, 210, 50);
static Entity ramCounterText("RAM usage counter", Vector2int(resourceMonitorBackground.x + 5, resourceMonitorBackground.y + 5), EntityComponent::Text("Ram: " + std::to_string(ramUsage) + "mb / " + std::to_string(totalRam) + "mb", &resourceMonitorFont, &Colors::Black));
static Entity cpuCounterText("CPU usage counter", Vector2int(resourceMonitorBackground.x + 5, resourceMonitorBackground.y + 25), EntityComponent::Text(CpuUsageText(), &resourceMonitorFont, &Colors::Black));
