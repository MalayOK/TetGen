#pragma once
#include "stdafx.h"
#include "Point3d.h"
#include "Tetrahedron.h"
namespace TetGen
{
	class Cube
	{
	public:
		Cube(vector<Point3d>);
		~Cube();
		bool IsPointInTop(const Point3d&);
		Point3d GetPoitInTop(const int&)const;
		char* GenerateStl();
		void MakeTetraFullCubes();
		void MakeTetraNotFullInObj();
	private:
		std::vector < std::shared_ptr<Point3d>> mpPoints;
		std::list < std::shared_ptr<Tetrahedron> > mpTetrahedrons;
	};
}
