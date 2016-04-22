#pragma once
#include "stdafx.h"
#include "Point3d.h"
#include "Mathematic.h"
#include "Vector3d.h"
//#include "Triangle.h"

namespace TetGen
{
	class Line
	{
	public:
		Line(double x1, double y1, double z1, double x2,
			double y2, double z2 );
		Line(const Point3d& rStartPoint, const Point3d& rEndPoint);
		Line(const Line& rLineCopy);
		~Line();
		bool IsParalelLines(const Line& rLine1, const Line& rLine2);
		Line GetLine()const;
		Point3d GetStartPoint()const;
		Point3d GetEndPoint()const;
		void DeleteRepeatingPoints();
		//bool IsEqualTwoLines(const Line& rLine1, const Line& rLine2);
		bool Intersection(Line& rLine,Point3d& rPoint);
		bool IsPointInLine(const Point3d& rPoint);
		bool IsPointInLineSegment(const Point3d& rPoint);
		void SetPointOfIntersection(const std::vector< std::shared_ptr<Point3d> >& rListOfPoints);
		std::vector<std::shared_ptr<Point3d>> GetIntersectionPoints()const;
	private:
		std::shared_ptr<Point3d> mpStartPoint;
		std::shared_ptr<Point3d> mpEndPoint;
		std::vector<std::shared_ptr<Point3d>> mpIntersectionPoints;
		bool mIsIntersectedObject;
	};
}
