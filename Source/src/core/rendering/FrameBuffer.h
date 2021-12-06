#pragma once
#include "Bindable.h"

namespace BoxerEngine
{
    class FrameBuffer final: public Bindable
    {
    private:
        unsigned int FBO = 0;
        unsigned int TexId = 0;
        unsigned int DepthId = 0;

        bool binded = false;
        int width, height;

    public:
        FrameBuffer(int w, int h);
        ~FrameBuffer() override;

        void Resize(int width, int height);
        void Invalidate();

        void Bind() override;
        void Unbind() override;

        [[nodiscard]] unsigned GetFrameBufferId() const
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
