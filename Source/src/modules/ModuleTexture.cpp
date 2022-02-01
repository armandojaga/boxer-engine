#include "core/bepch.h"

#include "ModuleTexture.h"

#include <IL/il.h>
#include <IL/ilu.h>
#include <GL/glew.h>

#include "core/preferences/PreferenceManager.h"
#include "core/preferences/editor/ResourcesPreferences.h"

bool ModuleTexture::Init()
{
    if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION)
    {
        /* wrong DevIL version */
        return false;
    }
    ilInit();
    iluInit();
    return true;
}

bool ModuleTexture::CleanUp()
{
    return Module::CleanUp();
}

unsigned int ModuleTexture::Load(const char* texture_name)
{
    std::filesystem::path name(texture_name);
    name.replace_extension();

    auto texture = textures_loaded.find(name.string().c_str());
    if (texture != textures_loaded.end())
    {
        return texture->second;
    }

    unsigned int tex_id = LoadNew(name.string().c_str());

    textures_loaded.emplace(name.string().c_str(), tex_id);

    return tex_id;
}

unsigned int ModuleTexture::LoadNew(const char* texture_name)
{
    unsigned int textureId(INVALID_ID);
    unsigned int image{};

    auto preferences =
        static_cast<BoxerEngine::ResourcesPreferences*>(App->preferences->GetPreferenceDataByType(BoxerEngine::Preferences::Type::RESOURCES));

    std::string library_path(preferences->GetLibraryPath(BoxerEngine::ResourceType::TEXTURE));
    library_path.append(texture_name);

    YAML::Node node = YAML::LoadFile(library_path.c_str());
    std::string texture_path = std::move(node["file_path"].as<std::string>());

    ilGenImages(1, &image);
    ilBindImage(image);
    if (ilLoadImage(texture_path.c_str()))
    {
        const bool success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
        if (!success)
        {
            return INVALID_ID;
        }

        const int width = ilGetInteger(IL_IMAGE_WIDTH);
        const int height = ilGetInteger(IL_IMAGE_HEIGHT);

        glCreateTextures(GL_TEXTURE_2D, 1, &textureId);

        glTextureParameteri(textureId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTextureParameteri(textureId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glTextureStorage2D(textureId, 1, ilGetInteger(IL_IMAGE_BPP), width, height);
        glTextureSubImage2D(textureId, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData());

        glGenerateTextureMipmap(textureId);
    }
    ilDeleteImages(1, &image);
    return textureId;
}
