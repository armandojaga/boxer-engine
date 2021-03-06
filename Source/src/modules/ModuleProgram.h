#pragma once
#include <memory>
#include <string>

#include "Module.h"
#include "core/util/Cache.h"

#include "GL/glew.h"
#include "Math/float2.h"
#include "Math/float3.h"
#include "Math/float4x4.h"

enum class ProgramType
{
    VERTEX = 1,
    FRAGMENT
};

struct Program
{
    unsigned int id;
    int model;
    int view;
    int projection;
    int color;
};

class ModuleProgram : public Module
{
private:
    Program program{};
    std::unique_ptr<BoxerEngine::Cache<std::string, int>> uniformsCache;
public:
    ModuleProgram();
    ~ModuleProgram() override = default;

    bool Init() override;
    bool CleanUp() override;

    void Create(const std::string& vertexPath, const std::string& fragmentPath);
    unsigned int Load(ProgramType, const std::string&);
    void UseProgram() const;

    void SetUniform(const std::string&, int value) const;
    void SetUniform(const std::string&, float value) const;
    void SetUniform(const std::string&, const float2& value) const;
    void SetUniform(const std::string&, const float3& value) const;
    void SetUniform(const std::string&, const float4x4& value) const;

    [[nodiscard]] const Program& GetProgram() const
    {
        return program;
    }
};
