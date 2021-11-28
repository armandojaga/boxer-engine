#pragma once

// TODO create singleton and factories for logging 
#include "ConsoleLogger.h"
#include "Timer.h"
inline BoxerEngine::ConsoleLogger logger;
inline BoxerEngine::Timer game_clock;

#define BE_LOG(format, ...) logger.Log(__FILE__, __LINE__, format, __VA_ARGS__);

enum update_status
{
    UPDATE_CONTINUE = 1,
    UPDATE_STOP,
    UPDATE_ERROR
};

#define LICENSE_PATH "../Source/licenses/LICENSE.TXT"

// Configuration -----------
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define FULLSCREEN false
#define VSYNC false
#define TITLE "Boxer Engine"
#define GLSL_VERSION "#version 460"
#define BOXER_ENGINE_VERSION "0.1"
#define FPS_LIMIT 250
