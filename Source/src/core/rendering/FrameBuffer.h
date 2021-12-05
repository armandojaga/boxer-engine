#pragma once
#include "Bindable.h"

namespace BoxerEngine
{
    class FrameBuffer : public Bindable
    {
    private:
        unsigned int FBO = 0;
        unsigned int TexId = 0;
        unsigned int DepthId = 0;

        int width, height;

    public:
        FrameBuffer(int width, int height);
        ~FrameBuffer();

        void Invalidate();

        void Bind() override;
        void Unbind() override;

        [[nodiscard]] unsigned GetFrameBuffer() const
        {
            return FBO;
        }

        void SetFrameBuffer(const unsigned fbo)
        {
            FBO = fbo;
        }

        [[nodiscard]] unsigned GetTextureId() const
        {
            return TexId;
        }

        void SetTextureId(const unsigned texId)
        {
            TexId = texId;
        }

        [[nodiscard]] unsigned GetDepthId() const
        {
            return DepthId;
        }

        void SetDepthId(const unsigned depthId)
        {
            DepthId = depthId;
        }
    };
}
