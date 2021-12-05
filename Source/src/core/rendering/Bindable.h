#pragma once

namespace BoxerEngine
{
    class Bindable
    {
    public:
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
    };
}
