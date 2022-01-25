#include "core/bepch.h"
#include "MeshComponent.h"

BoxerEngine::MeshComponent::MeshComponent(Entity* parent)
	: Component(Type::MESH, parent)
{
	SetupMesh();
}

void BoxerEngine::MeshComponent::SetupMesh()
{
}
