#include <birb2d/Renderwindow.hpp>
#include <birb2d/Entity.hpp>
#include <birb2d/Font.hpp>
#include <birb2d/Scene.hpp>
#include <birb2d/Values.hpp>

using namespace Birb;

/* Core variables */
static int width = 1280;
static int height = 720;

static ApplicationInfo appInfo;

static std::string mononoki_bold = appInfo.ResLocation + "/fonts/mononoki-Bold.ttf";
static std::string mononoki_regular = appInfo.ResLocation + "/fonts/mononoki-Regular.ttf";

/* Variables */
static int totalRam = 1024;
static int ramUsage = 1024;
static double CPUmax = 100;
static double CPUusage = 0;
