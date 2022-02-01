#include "../core/bepch.h"
#include "ModelComponent.h"

BoxerEngine::ModelComponent::ModelComponent(Entity* parent) : Component(type, parent)
{
}

void BoxerEngine::ModelComponent::UpdateUI()
{
	ImGui::Text("Model component here");
}

const char* BoxerEngine::ModelComponent::GetName() const
{
	return "Model";
}
