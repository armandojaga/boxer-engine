#include "ModuleTexture.h"

#include "core/util/Files.h"
#include "core/util/StringUtils.h"

#include "IL/il.h"
#include "IL/ilu.h"

#include "GL/glew.h"

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

unsigned int ModuleTexture::Load(const char* texture, const char* modelPath)
{
    unsigned int textureId(INVALID_ID);
    unsigned int image{};

    std::filesystem::path relativePath;
    if (modelPath)
    {
        const std::filesystem::path model = modelPath;
        relativePath = BoxerEngine::StringUtils::Concat(model.string(), "./", texture);
    }
    std::string path;
    //use path in model
    if (BoxerEngine::Files::IsValidFilePath(texture))
    {
        path = texture;
        logger.Debug("Loading texture from model path");
    }
    //use relative path to model
    else if (BoxerEngine::Files::IsValidFilePath(absolute(relativePath)))
    {
        logger.Debug("Loading texture from relative path");
        path = absolute(relativePath).string();
    }
    //use path from textures folder
    if (path.empty())
    {
        const std::filesystem::path textPath = texture;
        const std::filesystem::path projectTexture =
            BoxerEngine::StringUtils::Concat(ASSETS_PATH, TEXTURES_DIR, textPath.filename().string());

        if (BoxerEngine::Files::IsValidFilePath(projectTexture))
        {
            path = projectTexture.string();
            logger.Debug("Loading texture from project folder");
        }
    }
    if (!path.empty())
    {
        ilGenImages(1, &image);
        ilBindImage(image);
        if (ilLoadImage(path.c_str()))
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
    }
    return textureId;
}
