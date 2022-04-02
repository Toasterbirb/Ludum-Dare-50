#pragma once

#include <birb2d/Renderwindow.hpp>
#include <birb2d/Entity.hpp>
#include <birb2d/Font.hpp>
#include <birb2d/Scene.hpp>
#include "Variables.hpp"

using namespace Birb;

static Window window("Birb2D project template", Vector2int(width, height), 75, false);

/* Fonts */
static Font TitleFont(mononoki_bold, 64);
static Font MainMenuButtonFont(mononoki_bold, 32);

/* Scenes */
static Scene MainMenu, EndScreen, Game;

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
static Font resourceMonitorFont(mononoki_regular, 18);
static Rect resourceMonitorBackground(1050, 20, 210, 100);
static Entity ramCounterText("Ram usage counter", Vector2int(resourceMonitorBackground.x + 5, resourceMonitorBackground.y + 5), EntityComponent::Text("Ram: " + std::to_string(ramUsage) + "mb / " + std::to_string(totalRam) + "mb", &resourceMonitorFont, &Colors::Black));
