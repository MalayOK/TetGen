#include "stdafx.h"
#include "Triangle.h"
namespace TetGen
{
	Triangle::Triangle()
	{}

	Triangle::Triangle(const Point3d& rPointNormal, const Point3d& rPointOne,
		const Point3d& rPointTwoo, const Point3d& rPointThree)
	{
		if (&rPointOne != &rPointTwoo && &rPointOne != &rPointThree &&
			&rPointTwoo != &rPointThree)
		{
			mpPoints = new Point3d[gAmountOfCoordinates];
			mpPoints[0] = rPointOne;
			mpPoints[1] = rPointTwoo;
			mpPoints[2] = rPointThree;
			mpNormal = new Point3d(rPointNormal);
			mMax[0] = mpPoints[0].GetX();
			mMax[1] = mpPoints[0].GetY();
			mMax[2] = mpPoints[0].GetZ();
			mMax[0] = mpPoints[0].GetX();
			mMax[1] = mpPoints[0].GetY();
			mMax[2] = mpPoints[0].GetZ();
		}
		else
			throw std::runtime_error("Points can not be equal");
	}
	/*Triangle::Triangle(const Line& rLine1, const Line& rLine2,
		const Line& rLine3, const Point3d& rPointNormal)
	{

	}*/

	Triangle::Triangle(const Triangle& rTriangleCopy)
	{
		mpPoints = new Point3d[gAmountOfCoordinates];
		for (size_t i = 0; i < 3; i++)
		{
			mpPoints[i] = rTriangleCopy.mpPoints[i];
		}
		mpNormal = new Point3d(*rTriangleCopy.mpNormal);
		for (size_t i = 0; i < 3; i++)
		{
			mMax[i] = rTriangleCopy.mMax[i];
			mMax[i] = rTriangleCopy.mMin[i];
		}
	}
	Triangle::~Triangle()
	{
		if (mpPoints != nullptr )
			delete[] mpPoints;
		if (mpNormal != nullptr)
			delete mpNormal;		
	}

	double Triangle::SquareOfTriangle()
	{
		double a = this->mpPoints[0].GetDistance(this->mpPoints[1]);
		double b = this->mpPoints[1].GetDistance(this->mpPoints[2]);
		double c = this->mpPoints[2].GetDistance(this->mpPoints[3]);
		// p - half Perimeter
		double p = (a + b + c)*0.5;
		// Heron formula to count area
		double s = sqrt(p*(p - a)*(p - b)*(p - c));
	return s;
	}
	Point3d Triangle::GetPoints(int i)const
	{
		return mpPoints[i];
	}

	////////////////////////////////////////////////////////////////
	//If the volume of the tetrahedron /////////////////////////////
	//constructed on four points is 0, then they lie in one plane///
	//
	bool Triangle::IsPointInTiangle(const Point3d& rPoint)
	{
		Vector3d OA(this->mpPoints[0] - rPoint);
		Vector3d OB(this->mpPoints[1] - rPoint);
		Vector3d OC(this->mpPoints[2] - rPoint);
		Vector3d AB(this->mpPoints[1] - this->mpPoints[0]);
		Vector3d AC(this->mpPoints[2] - this->mpPoints[0]);
		double mixProduct = OA.MixedProduct(OB, OC);
		if (!mixProduct)
			return false;
		if ((OA.CrossProduct(OB).Magnitude() + OA.CrossProduct(OC).Magnitude() +
			OB.CrossProduct(OC).Magnitude() -
			AB.CrossProduct(AC).Magnitude()) > TetGen::gRealEpsilon)
			return false;
		return true; 
	}
	
	bool Triangle::IsPointInTop(const Point3d& rPoint)
	{
		if (this->mpPoints[0] == rPoint || this->mpPoints[1] == rPoint ||
			this->mpPoints[2] == rPoint)
			return true;
		return false;
	}

	bool Triangle::operator==(const Triangle & rTriangle)
	{
		if (this->mpPoints[0] == rTriangle.mpPoints[0] &&
			this->mpPoints[1] == rTriangle.mpPoints[1] &&
			this->mpPoints[2] == rTriangle.mpPoints[2])
			return true;
		return false;

	}
	bool Triangle::operator!=(const Triangle& rTriangle)
	{
		return !(*this == rTriangle);
	}
	Triangle& Triangle::operator=(const Triangle & rTriangleCopy)
	{
		mpPoints = new Point3d[gAmountOfCoordinates];
		for (size_t i = 0; i < 3; i++)
		{
			mpPoints[i] = rTriangleCopy.mpPoints[i];
		}
		mpNormal = new Point3d(*rTriangleCopy.mpNormal);
		for (size_t i = 0; i < 3; i++)
		{
			mMax[i] = rTriangleCopy.mMax[i];
			mMax[i] = rTriangleCopy.mMin[i];
		}
		return *this;
	}
	
}