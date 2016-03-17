#pragma once
#include "stdafx.h"
#include "Point3d.h"
#include "Vector3d.h"
#include "Triangle.h"
#include "Mathematic.h"

namespace TetGen
{
	class Plane
	{
	public:
		Plane(const double& rA=0, const double& rB=0, 
			 const double& rC=0, const double& rD=0);
		Plane(const Point3d& rPoint1, const Point3d& rPoint2,
			const Point3d& rPoint3);
		Plane(const Triangle& rTriangle);
		~Plane();
		void SetABCD(const Point3d& rPoint1, const Point3d& rPoint2,
			const Point3d& rPoint3);
		bool IsParalelTwoPlanes(const Plane& rPlane);
		Plane& operator= (const Plane& rPlane);
		bool operator==(const Plane &);
		bool operator!=(const Plane &);
	private:
		double mA, mB, mC, mD;
	};
}