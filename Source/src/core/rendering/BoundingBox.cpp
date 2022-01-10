#include "core/bepch.h"
#include "BoundingBox.h"
#include <GL/glew.h>

namespace BoxerEngine
{
	BoundingBox::BoundingBox()
	{
		Setup();
	}

	BoundingBox::BoundingBox(BB_TYPE type, const vec& minPoint, const vec& maxPoint)
	{
		Setup(type, minPoint, maxPoint);
	}

	BoundingBox::~BoundingBox()
	{
		delete axis_aligned;
	}

	void BoundingBox::Draw() const
	{
		vec corners[8];
		axis_aligned->GetCornerPoints(corners);
		for (int i = 0; i < faces.size(); ++i)
		{
			glBegin(GL_LINES);
			for (int j = 0 ; j < edges.size(); ++j)
			{
				glVertex3f(
					corners[faces[i][edges[j]]].x,
					corners[faces[i][edges[j]]].y,
					corners[faces[i][edges[j]]].z);
			}
			
			glEnd();
		}
	}

	void BoundingBox::Setup(BB_TYPE type, const vec& minPoint, const vec& maxPoint)
	{
		// Each face has 4 indices that are bounding box corners
		faces.push_back({ 0,1,2,3 });
		faces.push_back({ 1,3,5,7 });
		faces.push_back({ 0,2,4,6 });
		faces.push_back({ 4,5,6,7 });

		// This patterns define how to draw bounding box edges
		edges = { 0,1, 0,2, 0,3, 1,2, 1,3, 2,3 };
		axis_aligned = new AABB(minPoint, maxPoint);
	}
}

