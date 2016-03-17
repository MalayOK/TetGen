#include "stdafx.h"
#include "Plane.h"

namespace TetGen
{
	Plane::Plane(const double& rA , const double& rB ,
		 const double& rC , const double& rD ) : 
		mA(rA), mB(rB), mC(rC), mD(rD)
	{
	}

	Plane::Plane(const Point3d& rPoint1, const Point3d& rPoint2,
		const Point3d& rPoint3)
	{
		SetABCD(rPoint1, rPoint2, rPoint3);
	}

	Plane::Plane(const Triangle& rTriangle)
	{
		SetABCD(rTriangle.GetPoints(0), rTriangle.GetPoints(1),
			rTriangle.GetPoints(2));
	}

	Plane::~Plane()
	{}
	void Plane::SetABCD(const Point3d& rPoint1, const Point3d& rPoint2,
		const Point3d& rPoint3)
	{
		Vector3d AB(rPoint2 - rPoint1);
		Vector3d AC(rPoint3 - rPoint1);
		Vector3d N = AB.CrossProduct(AC);
		mA = N.GetVector().GetX();
		mB = N.GetVector().GetY();
		mC = N.GetVector().GetZ();
		mD = -mA * rPoint1.GetX() - mB * rPoint1.GetY()
			- mC * rPoint1.GetZ();
	}

	bool Plane::IsParalelTwoPlanes(const Plane& rPlane)
	{
		if (IsAlmostEqualDouble(this->mA / rPlane.mA,
			this->mB / rPlane.mB) && IsAlmostEqualDouble(this->mA / rPlane.mA,
				this->mC / rPlane.mC) && IsAlmostEqualDouble
			(this->mB / rPlane.mB, this->mC / rPlane.mC) &&
			!IsAlmostEqualDouble(this->mD / rPlane.mD, this->mC / rPlane.mC) &&
			!IsAlmostEqualDouble(this->mD / rPlane.mD, this->mB / rPlane.mB) &&
			!IsAlmostEqualDouble(this->mD / rPlane.mD, this->mA / rPlane.mA))
			return true;
		return false;
	}

	Plane& Plane::operator= (const Plane& rPlane)
	{
		this->mA = rPlane.mA;
		this->mB = rPlane.mB;
		this->mC = rPlane.mC;
		this->mD = rPlane.mD;
	return *this;
	}
	bool Plane::operator==(const Plane& rPlane)
	{
		if (IsAlmostEqualDouble(this->mA, rPlane.mA) &&
			IsAlmostEqualDouble(this->mB, rPlane.mB) &&
			IsAlmostEqualDouble(this->mC, rPlane.mC) &&
			IsAlmostEqualDouble(this->mD, rPlane.mD))
			return true;
		return false;
	}
	bool Plane::operator!=(const Plane& rPlane)
	{
		return !(*this == rPlane);
	}
}