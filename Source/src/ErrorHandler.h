#pragma once

namespace BoxerEngine
{
    class ErrorHandler
    {
    public:
        static void HandleOpenGlError(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* data)
        {
            const char* _source;
            const char* _type;
            const char* _severity;

            switch (source)
            {
            case GL_DEBUG_SOURCE_API:
                _source = "API";
                break;

            case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
                _source = "WINDOW SYSTEM";
                break;

            case GL_DEBUG_SOURCE_SHADER_COMPILER:
                _source = "SHADER COMPILER";
                break;

            case GL_DEBUG_SOURCE_THIRD_PARTY:
                _source = "THIRD PARTY";
                break;

            case GL_DEBUG_SOURCE_APPLICATION:
                _source = "APPLICATION";
                break;

            case GL_DEBUG_SOURCE_OTHER:
            default:
                _source = "UNKNOWN";
                break;
            }

            switch (type)
            {
            case GL_DEBUG_TYPE_ERROR:
                _type = "ERROR";
                break;

            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
                _type = "DEPRECATED BEHAVIOR";
                break;

            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
                _type = "UDEFINED BEHAVIOR";
                break;

            case GL_DEBUG_TYPE_PORTABILITY:
                _type = "PORTABILITY";
                break;

            case GL_DEBUG_TYPE_PERFORMANCE:
                _type = "PERFORMANCE";
                break;

            case GL_DEBUG_TYPE_OTHER:
                _type = "OTHER";
                break;

            case GL_DEBUG_TYPE_MARKER:
                _type = "MARKER";
                break;

            default:
                _type = "UNKNOWN";
                break;
            }

            switch (severity)
            {
            case GL_DEBUG_SEVERITY_HIGH:
                _severity = "HIGH";
                break;

            case GL_DEBUG_SEVERITY_MEDIUM:
                _severity = "MEDIUM";
                break;

            case GL_DEBUG_SEVERITY_LOW:
                _severity = "LOW";
                break;

            case GL_DEBUG_SEVERITY_NOTIFICATION:
                _severity = "NOTIFICATION";
                break;

            default:
                _severity = "UNKNOWN";
                break;
            }

            BE_LOG("[%s] <%s> (%s) %d: %s", _severity, _type, _source, id, msg);
        }
    };
}
