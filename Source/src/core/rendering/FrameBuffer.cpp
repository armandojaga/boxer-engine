#include "FrameBuffer.h"

#include "Application.h"
#include "Globals.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"
#include "GL/glew.h"

BoxerEngine::FrameBuffer::FrameBuffer(int w, int h) : width(w), height(h)
{
    Invalidate();
}

BoxerEngine::FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(GL_FRAMEBUFFER, &FBO);
}

void BoxerEngine::FrameBuffer::Resize(const int width, const int height)
{
    if (this->width != width || this->height != height)
    {
        this->width = width;
        this->height = height;
        Invalidate();
    }
}

void BoxerEngine::FrameBuffer::Invalidate()
{
    BE_LOG("Invalidating frame buffer, w: %d, h: %d", width, height);
    if (FBO)
    {
        glDeleteFramebuffers(GL_FRAMEBUFFER, &FBO);
        glDeleteTextures(1, &TexId);
        glDeleteTextures(1, &DepthId);
        TexId = 0;
        DepthId = 0;
        Unbind();
    }

    glGenFramebuffers(1, &FBO);
    Bind();

    glCreateTextures(GL_TEXTURE_2D, 1, &TexId);
    glBindTexture(GL_TEXTURE_2D, TexId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, TexId, 0);

    glCreateTextures(GL_TEXTURE_2D, 1, &DepthId);
    glBindTexture(GL_TEXTURE_2D, DepthId);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, width, height);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, DepthId, 0);
    Unbind();
}

void BoxerEngine::FrameBuffer::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}

void BoxerEngine::FrameBuffer::Unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
