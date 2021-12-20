#pragma once

#include "Globals.h"

class Application;

class Module
{
public:
    Module() = default;
    virtual ~Module() = default;

    virtual bool Init()
    {
        return true;
    }

    virtual bool Start()
    {
        return true;
    }

    virtual update_status PreUpdate(float delta)
    {
        return update_status::UPDATE_CONTINUE;
    }

    virtual update_status Update(float delta)
    {
        return update_status::UPDATE_CONTINUE;
    }

    virtual update_status PostUpdate(float delta)
    {
        return update_status::UPDATE_CONTINUE;
    }

    virtual bool CleanUp()
    {
        return true;
    }
};
