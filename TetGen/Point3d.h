#pragma once
#include "stdafx.h"
#include "Mathematic.h"
namespace TetGen
{
	class Point3d
	{
		public:
			Point3d();
			Point3d(double X, double Y, double Z);
			~Point3d();
			double GetX()const;
			double GetY()const;
			double GetZ()const;
			double GetDistance(const Point3d& rPoint)const;
			Point3d GetPoint()const;
			void SetX(double X);
			void SetY(double Y);
			void SetZ(double Z);
			Point3d operator+(const Point3d& rPoint)const;
			Point3d operator-(const Point3d& rPoint)const;
			Point3d operator=(const Point3d& rPoint);
			bool operator==(const Point3d& rPoint);
			bool operator!=(const Point3d& rPoint);
		private:
			double mX;
			double mY;
			double mZ;
	
	};

}
