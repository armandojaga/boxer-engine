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
    ~AssimpLogger()
    {
    }

    // Using our own logger
    void write(const char* message)
    {
        BE_LOG("AssimpLogger says: %s", message);
    }
};
