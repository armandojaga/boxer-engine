#pragma once

// TODO create singleton and factories for logging 
#include "ConsoleLogger.h"
#include "core/GameOptions.h"
#include "core/util/Timer.h"

inline BoxerEngine::ConsoleLogger logger;
inline BoxerEngine::Timer game_clock;
inline BoxerEngine::GameOptions game_options;

#define BE_LOG(format, ...) logger.Log(__FILE__, __LINE__, format, __VA_ARGS__);

enum update_status
{
    UPDATE_CONTINUE = 1,
    UPDATE_STOP,
    UPDATE_ERROR
};

#define ASSERTS_PATH "/assets/"
#define LICENSE_PATH "../licenses/LICENSE.TXT"

// Configuration -----------
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define TITLE "Boxer Engine"
#define GLSL_VERSION "#version 460"
#define BOXER_ENGINE_VERSION "0.1"
