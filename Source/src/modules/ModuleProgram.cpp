#include "ModuleProgram.h"

ModuleProgram::ModuleProgram()
{
    uniformsCache = std::make_unique<BoxerEngine::Cache<std::string, int>>([&](const std::string& key)
        {
            return glGetUniformLocation(program.id, key.c_str());
        }
    );
}

bool ModuleProgram::Init()
{
    return Module::Init();
}

bool ModuleProgram::CleanUp()
{
    return Module::CleanUp();
}

void ModuleProgram::Create(const std::string& vertex, const std::string& fragment)
{
    program.id = glCreateProgram();
    const auto vs = Load(ProgramType::VERTEX, vertex);
    const auto fs = Load(ProgramType::FRAGMENT, fragment);

    glAttachShader(program.id, vs);
    glAttachShader(program.id, fs);
    glLinkProgram(program.id);
    glValidateProgram(program.id);

    glDeleteShader(vs);
    glDeleteShader(fs);
}

unsigned int ModuleProgram::Load(ProgramType type, const std::string& source)
{
    const unsigned int glType = type == ProgramType::VERTEX ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;
    const auto id = glCreateShader(glType);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    return id;
}

void ModuleProgram::SetUniform(std::string& name, int value) const
{
    const int location = uniformsCache->Get(name);
    glUniform1i(location, value);
}

void ModuleProgram::SetUniform(std::string& name, float value) const
{
    const int location = uniformsCache->Get(name);
    glUniform1f(location, value);
}

void ModuleProgram::SetUniform(std::string& name, const float2& value) const
{
    const int location = uniformsCache->Get(name);
    glUniform2f(location, value.x, value.y);
}

void ModuleProgram::SetUniform(std::string& name, const float3& value) const
{
    const int location = uniformsCache->Get(name);
    glUniform3f(location, value.x, value.y, value.z);
}

void ModuleProgram::SetUniform(std::string& name, const float4x4& value) const
{
    const int location = uniformsCache->Get(name);
    glUniformMatrix4fv(location, 1, true, value.ptr()); // transposing by default to compensate matgeolib vs opengl 
}
