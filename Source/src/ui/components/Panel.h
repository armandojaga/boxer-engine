#pragma once

namespace BoxerEngine
{
    class Panel
    {
    public:
        Panel(const std::string& title, bool isVisible);
        virtual ~Panel() = default;

        [[nodiscard]] const std::string& GetTitle() const;

        void SetVisible(bool);
        [[nodiscard]] bool IsVisible() const;

        virtual void Update();

    protected:
        bool visible = true;
    private:
        std::string title;
    };
}
