#pragma once

#include <birb2d/Audio.hpp>
#include <birb2d/Font.hpp>
#include <birb2d/Values.hpp>

using namespace Birb;

/* Core variables */
static int width = 1280;
static int height = 720;

static ApplicationInfo appInfo("LD50.exe");

static std::string click_sound_path = appInfo.ResLocation + "/sounds/click.wav";
static Audio::SoundFile ClickSound(click_sound_path);
static Audio::SoundFile PopupSound(appInfo.ResLocation + "/sounds/window_popup.wav");
static Audio::SoundFile RamUpgrade(appInfo.ResLocation + "/sounds/ram_upgrade.wav");
static std::string mononoki_bold = appInfo.ResLocation + "/fonts/mononoki-Bold.ttf";
static std::string mononoki_regular = appInfo.ResLocation + "/fonts/mononoki-Regular.ttf";
static Font DefaultFont(mononoki_regular);

/* Variables */
struct Variables
{
public:
	static inline int totalRam = 1024;
	static inline int ramUsage = 0;
	static inline double CPUmax = 100;
	static inline double CPUusage = 0;
	static inline std::string username = getenv("USER");

};
