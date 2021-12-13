#include "ModuleResources.h"

#include "Application.h"
#include "ModuleRender.h"
#include "core/rendering/Model.h"
#include "core/util/Files.h"
// #include <algorithm>

bool ModuleResources::Init()
{
    return Module::Init();
}

bool ModuleResources::CleanUp()
{
    return Module::CleanUp();
}

void ModuleResources::HandleResource(const char* path)
{
    ResourceType type = GetType(path);
    switch (type)
    {
    case ResourceType::MODEL:
        App->renderer->GetModel()->Load(path);
        break;
    // case ResourceType::TEXTURE:
    //
    //     break;
    }
}

ResourceType ModuleResources::GetType(const std::filesystem::path& path)
{
    if (!path.has_extension())
    {
        return ResourceType::UNKNOWN;
    }
    const std::filesystem::path extension = path.extension();

    auto isValidExtension = [&](const std::pair<ResourceType, std::string>& element)
    {
        return element.second.size() == extension.string().size() &&
            std::equal(element.second.begin(), element.second.end(), extension.string().begin(),
                       [](auto a, auto b) { return std::tolower(a) == std::tolower(b); });
    };

    const auto it = std::find_if(supported_extensions.begin(), supported_extensions.end(), isValidExtension);
    if (it != supported_extensions.end())
    {
        return it->first;
    }
    return ResourceType::UNKNOWN;
}