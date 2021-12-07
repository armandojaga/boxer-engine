#include "ModuleTexture.h"

bool ModuleTexture::Init()
{
    ilInit();
    iluInit();
    return true;
}

bool ModuleTexture::CleanUp()
{
    return Module::CleanUp();
}

unsigned ModuleTexture::Load(std::string&&)
{
    return 0;
}
