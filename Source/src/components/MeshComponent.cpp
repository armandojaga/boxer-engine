#include "MeshComponent.h"

BoxerEngine::MeshComponent::MeshComponent(Entity* parent)
	: Component(Component::Type::MESH, parent)
{
	SetupMesh();
}

void BoxerEngine::MeshComponent::SetupMesh()
{
}
