#include "core/bepch.h"
#include "BoundingBox.h"
#include <GL/glew.h>

namespace BoxerEngine
{
	BoundingBox::BoundingBox()
	{
	}

	BoundingBox::BoundingBox(BB_TYPE type, const vec& minPoint, const vec& maxPoint)
	{
		switch (type) 
		{
			case BB_TYPE::AABB:
				axis_aligned = new AABB(minPoint, maxPoint);
				break;
			case BB_TYPE::OBB:
				break;
		}
	}

	BoundingBox::~BoundingBox()
	{
		//delete axis_aligned;
	}

	void BoundingBox::Draw() const
	{
		vec corners[8];
		axis_aligned->GetCornerPoints(corners);

		for (int i = 1; i <= 8; ++i)
		{
			glBegin(GL_LINES);
			glVertex2f(corners[i-1].x, corners[i-1].y);
			glVertex2f(corners[i].x, corners[i].y);
			glEnd();
		}
	}
}

