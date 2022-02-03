#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <string>
#include <string_view>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_map>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <execution>
#include <cstdarg>
#include <cstdio>
#include <random>
#include <tuple>
#include <ctime>

#include <thread>
#include <future>
#include <mutex>

#include <Windows.h>
#include <Psapi.h>

#include <SDL.h>

#include <optick.h>
#include <imgui.h>
#include <imgui_stdlib.h>
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"

#include <ImGuizmo.h>

#include <IconsMaterialDesign.h>

#include <yaml-cpp/yaml.h>

#include "Globals.h"
#include "Application.h"
#include "modules/Module.h"
#include "core/util/StringUtils.h"
#include "core/util/Files.h"
#include "rendering/Bindable.h"
#include "Entity.h"
#include "components/Component.h"
#include "ui/components/Panel.h"

#include "core/events/Event.h"
#include "core/events/EventManager.h"

#include "converters/TypeConverter.h"
