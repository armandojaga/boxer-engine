#pragma once
#include "Bindable.h"

namespace BoxerEngine
{
    class FrameBuffer final : public Bindable
    {
    public:
        FrameBuffer(int w, int h);
        ~FrameBuffer() override;

        void Resize(int width, int height);

        void Bind() override;
        void Unbind() override;

        [[nodiscard]] unsigned GetFrameBufferId() const
        {
            return fbo_id;
        }

        [[nodiscard]] unsigned GetTextureId() const
        {
            return texture_id;
        }

        [[nodiscard]] int GetWidth() const;
        [[nodiscard]] int GetHeight() const;

    private:
        unsigned int fbo_id = 0;
        unsigned int texture_id = 0;
        unsigned int rbo_id = 0;

        int width{};
        int height{};

        void Reset();
        void Create();
    };
}
