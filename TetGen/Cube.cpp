#include "stdafx.h"
#include "Cube.h"

namespace TetGen
{
	Cube::Cube( vector<Point3d>& rVectorOfPoint)
	{
		if (rVectorOfPoint.size()!=8)
			throw std::runtime_error("incorrect number of points.Thee cube should be 8 points ");
		mpPoints.reserve(8);
		for (size_t i = 0; i < 8; i++)
		{
			mpPoints[i] = std::make_shared<Point3d>(rVectorOfPoint[i]);
		}
	}
	Cube::~Cube()
	{

	}

	bool Cube::IsPointInTop(const Point3d& rPoint)
	{
		for (size_t i = 0; i < 8; i++)
		{
			if (mpPoints[i]->GetPoint() != rPoint)
				return false;
		}
		return true;
	}

	Point3d Cube::GetPoitInTop(const int& rNumberOfTop)const
	{
		if (rNumberOfTop < 1 && rNumberOfTop>8)
			throw std::runtime_error("incorrect number of top.");
		return this->mpPoints[rNumberOfTop]->GetPoint();
	}
}