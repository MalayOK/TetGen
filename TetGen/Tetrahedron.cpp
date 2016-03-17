#include "stdafx.h"
#include "Tetrahedron.h"

namespace TetGen
{
	Tetrahedron::Tetrahedron(Point3d& rPoint1, Point3d& rPoint2,
		Point3d& rPoint3, Point3d& rPoint4)
	{
		if (rPoint1 != rPoint2&& rPoint1 != rPoint3&& rPoint1 != rPoint4&&
			rPoint2 != rPoint3&& rPoint2 != rPoint4&& rPoint3 != rPoint4)
		{
			/*mpPoints = new Point3d[4];*/
			mpPoints.reserve(4);
			mpPoints[0] = std::make_shared<Point3d> (rPoint1);
			mpPoints[1] = std::make_shared<Point3d>(rPoint2);
			mpPoints[2] = std::make_shared<Point3d>(rPoint3);
			mpPoints[3] = std::make_shared<Point3d>(rPoint4);
		}
		else
			throw std::runtime_error("Points can not be equal");
	}

	//Tetrahedron::Tetrahedron(Triangle& pTriangle1, Triangle& pTriangle2,
	//	Triangle& pTriangle3, Triangle& pTriangle4)
	//{

	//}


	Tetrahedron::~Tetrahedron()
	{}
}