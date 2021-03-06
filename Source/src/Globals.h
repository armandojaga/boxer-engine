#pragma once

// TODO create singleton and factories for logging 
#include "core/logging/ConsoleLogger.h"
#include "core/GameOptions.h"
#include "core/util/Timer.h"

inline BoxerEngine::ConsoleLogger logger;
inline BoxerEngine::Timer game_clock;
inline BoxerEngine::GameOptions game_options;

#define BE_LOG(format, ...) logger.Log(__FILE__, __LINE__, format, __VA_ARGS__);

enum class update_status
{
    UPDATE_CONTINUE = 1,
    UPDATE_STOP,
    UPDATE_ERROR
};

#define ASSETS_PATH "./assets/"
#define TEXTURES_DIR "textures/"
#define MODELS_DIR "models/"
#define SHADERS_DIR "shaders/"

#define LICENSE_PATH "../licenses/LICENSE.TXT"
#define CONFIG_PATH "./data/config/be.cfg"

constexpr int INVALID_ID = 0;

// Configuration -----------
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define TITLE "Boxer Engine"
#define GLSL_VERSION "#version 460"
#define BOXER_ENGINE_VERSION "Alpha 2"
