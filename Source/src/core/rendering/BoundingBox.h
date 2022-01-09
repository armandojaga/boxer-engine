#pragma once
#include "MathGeoLib.h"

namespace BoxerEngine
{
	enum class BB_TYPE
	{
		AABB = 0,
		OBB
	};

	class BoundingBox
	{
	public:
		BoundingBox();
		BoundingBox(BB_TYPE type, const vec& minPoint, const vec& maxPoint);
		~BoundingBox();

		void Draw() const;

		// Axis align
		const AABB* GetAABB() const { return axis_aligned; }
		void SetAABB(AABB&& aabb) { axis_aligned = &aabb; }
		void SetAABB(const vec& minPoint, const vec& maxPoint) { axis_aligned = new AABB(minPoint, maxPoint); }
		
		// Object align

	private:
		AABB* axis_aligned = nullptr;
		std::vector<std::vector<int>> faces;
		std::vector<int> edges;
	};
}



