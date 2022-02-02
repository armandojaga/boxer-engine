#include "core/bepch.h"
#include "Panel.h"

BoxerEngine::Panel::Panel(const std::string& title, const bool isVisible): visible(isVisible), title(title)
{
}

const std::string& BoxerEngine::Panel::GetTitle() const
{
    return title;
}

void BoxerEngine::Panel::SetVisible(const bool isVisible)
{
    this->visible = isVisible;
}

bool BoxerEngine::Panel::IsVisible() const
{
    return visible;
}

void BoxerEngine::Panel::Update()
{
}
