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
			mpPoints.reserve(4);
			mpPoints.push_back(std::make_shared<Point3d>(rPoint1));
			mpPoints.push_back(std::make_shared<Point3d>(rPoint2));
			mpPoints.push_back(std::make_shared<Point3d>(rPoint3));
			mpPoints.push_back(std::make_shared<Point3d>(rPoint4));
		}
		else
			throw std::runtime_error("Points can not be equal");
	}

	char* Tetrahedron::GenerateStlTetra()
	{
		char code[1200] = "";
		Point3d Normal(0.000000e+00, 0.000000e+00, 0.000000e+00);
		std::shared_ptr<Triangle> triangle;
		triangle = std::make_shared<Triangle>(Normal,this->mpPoints[0]->GetPoint(),
			this->mpPoints[1]->GetPoint(), this->mpPoints[2]->GetPoint());
		strcat_s(code, 1200,triangle->GenerateStlTriangle());
		triangle.reset();
		triangle = std::make_shared<Triangle>(Normal, this->mpPoints[0]->GetPoint(),
			this->mpPoints[1]->GetPoint(), this->mpPoints[3]->GetPoint());
		strcat_s(code, 1200,triangle->GenerateStlTriangle());
		triangle.reset();
		triangle = std::make_shared<Triangle>(Normal, this->mpPoints[3]->GetPoint(),
			this->mpPoints[1]->GetPoint(), this->mpPoints[2]->GetPoint());
		strcat_s(code,1200, triangle->GenerateStlTriangle());
		triangle.reset();
		triangle = std::make_shared<Triangle>(Normal, this->mpPoints[0]->GetPoint(),
			this->mpPoints[3]->GetPoint(), this->mpPoints[2]->GetPoint());
		strcat_s(code,1200, triangle->GenerateStlTriangle());
		return code;
	}

	//Tetrahedron::Tetrahedron(Triangle& pTriangle1, Triangle& pTriangle2,
	//	Triangle& pTriangle3, Triangle& pTriangle4)
	//{

	//}


	Tetrahedron::~Tetrahedron()
	{}
}