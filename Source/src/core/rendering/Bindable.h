#pragma once

namespace BoxerEngine
{
    class Bindable
    {
    public:
        virtual ~Bindable() = default;
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
    };
}
