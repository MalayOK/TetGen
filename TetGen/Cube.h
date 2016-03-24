#pragma once
#include "stdafx.h"
#include "Point3d.h"
namespace TetGen
{
	class Cube
	{
	public:
		Cube(vector<Point3d>&);
		~Cube();
		bool IsPointInTop(const Point3d&);
		Point3d GetPoitInTop(const int&)const;
	private:
		std::vector < std::shared_ptr<Point3d>> mpPoints;
	};
}
