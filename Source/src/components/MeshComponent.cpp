#include "core/bepch.h"
#include "MeshComponent.h"

BoxerEngine::MeshComponent::MeshComponent(Entity* parent)
	: Component(Component::Type::MESH, parent)
{
	SetupMesh();
}

void BoxerEngine::MeshComponent::UpdateUI()
{
	ImGui::Text("Mesh component");
}

const char* BoxerEngine::MeshComponent::GetName() const
{
	return "Mesh";
}

void BoxerEngine::MeshComponent::SetupMesh()
{
}
