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

unsigned int ModuleTexture::Load(const char* texture_path)
{
    unsigned int textureId(INVALID_ID);
    unsigned int image{};
    
    ilGenImages(1, &image);
    ilBindImage(image);
    if (ilLoadImage(texture_path))
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
