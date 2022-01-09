#pragma once

#include <assimp/LogStream.hpp>
#include "Globals.h"

using namespace Assimp;

// Example stream
class AssimpLogger : public LogStream
{
public:
    // Constructor
    AssimpLogger()
    {
    }

    // Destructor
    ~AssimpLogger() override
    {
    }

    // Using our own logger
    void write(const char* message) override
    {
        BE_LOG("AssimpLogger says: %s", message);
    }
};
