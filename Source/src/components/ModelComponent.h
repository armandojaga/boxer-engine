#pragma once
#include "Component.h"

namespace BoxerEngine
{
	class ModelComponent : public Component
	{
	public:
		inline static Type type = Type::MODEL;

		explicit ModelComponent(Entity* parent);
		~ModelComponent() override = default;

		void UpdateUI() override;
		[[nodiscard]] const char* GetName() const override;
	};
}

