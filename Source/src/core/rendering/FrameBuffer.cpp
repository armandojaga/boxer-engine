#include "FrameBuffer.h"

#include "Application.h"
#include "Globals.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"
#include "GL/glew.h"

BoxerEngine::FrameBuffer::FrameBuffer(int w, int h) : width(w), height(h)
{
    Create();
}

BoxerEngine::FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(GL_FRAMEBUFFER, &fbo_id);
}

void BoxerEngine::FrameBuffer::Resize(const int width, const int height)
{
    if (this->width != width || this->height != height)
    {
        this->width = width;
        this->height = height;
        Reset();
        Create();
    }
}

void BoxerEngine::FrameBuffer::Reset()
{
    BE_LOG("Invalidating frame buffer, w: %d, h: %d", width, height);
    if (fbo_id)
    {
        glDeleteFramebuffers(GL_FRAMEBUFFER, &fbo_id);
        glDeleteTextures(1, &texture_id);
        glDeleteRenderbuffers(1, &rbo_id);
        texture_id = 0;
        rbo_id = 0;
        Unbind();
    }
}

void BoxerEngine::FrameBuffer::Create()
{
    //create frame buffer
    glCreateFramebuffers(1, &fbo_id);
    Bind();

    //TODO consider rendering to screen size instead of viewport size
    //create associated texture
    glCreateTextures(GL_TEXTURE_2D, 1, &texture_id);

    glTextureParameteri(texture_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(texture_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(texture_id, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTextureParameteri(texture_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(texture_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTextureStorage2D(texture_id, 1, GL_RGB8, width, height);

    glNamedFramebufferTexture(fbo_id, GL_COLOR_ATTACHMENT0, texture_id, 0);

    //create render buffer (depth)
    glCreateRenderbuffers(1, &rbo_id);
    glNamedRenderbufferStorage(rbo_id, GL_DEPTH24_STENCIL8, width, height);
    glNamedFramebufferRenderbuffer(fbo_id, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo_id);

    //check if creation was successful
    assert(glCheckNamedFramebufferStatus(rbo_id, GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

    Unbind();
}

void BoxerEngine::FrameBuffer::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo_id);
}

void BoxerEngine::FrameBuffer::Unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
