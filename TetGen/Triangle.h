#pragma once
#include "stdafx.h"
#include "Point3d.h"
#include "Mathematic.h"
#include "Plane.h"

namespace TetGen
{
	const int gAmountOfCoordinates = 3;
	class Triangle
	{
	public:
		Triangle();
		Triangle(const Point3d& rPointNormal,const Point3d& rPointOne,
			const Point3d& rPointTwoo,const Point3d& rPointThree);
	/*	Triangle(const Line& rLine1, const Line& rLine2,
			const Line& rLine3, const Point3d& rPointNormal);*/
		Triangle(const Triangle& rTriangleCopy);
		~Triangle();
		double SquareOfTriangle();
		Point3d GetPoints(int i)const;
		bool IsIntersectedLT(const Line& rLine, Point3d& rResultPoint);
		bool IsPointInTop(const Point3d&);
		bool IsPointInTiangle(const Point3d& rPoint);
		char* GenerateStlTriangle();
		std::vector<double> GetMax();
		std::vector<double> GetMin();
		bool operator==(const Triangle &);
		bool operator!=(const Triangle &);
		Triangle & operator=(const Triangle &);
		bool IsINSameSide( Point3d&,  Point3d&,  Point3d&,  Point3d&);
	private:
		std::vector<std::shared_ptr<Point3d>> mpPoints;
		std::shared_ptr<Point3d> mpNormal;
		std::vector<double> mMax;
		std::vector<double> mMin;
	};
}