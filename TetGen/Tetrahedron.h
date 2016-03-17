#pragma once
#include "stdafx.h"
#include "Point3d.h"
#include "Triangle.h"

namespace TetGen
{
	class Tetrahedron
	{
	public:
		Tetrahedron(Point3d&, Point3d&, Point3d&, Point3d&);
		/*Tetrahedron(Triangle&, Triangle&, Triangle&, Triangle&);*/
		~Tetrahedron();
	private:
		/*Triangle* mpTriangles;*/
		/*Point3d* mpPoints;*/
		std::vector < std::shared_ptr<Point3d>> mpPoints;
	};
}