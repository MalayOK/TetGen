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
			mpPoints.reserve(gAmountOfCoordinates);
			mpPoints.push_back(std::make_shared<Point3d>(rPointOne));
			mpPoints.push_back(std::make_shared<Point3d>(rPointTwoo));
			mpPoints.push_back(std::make_shared<Point3d>(rPointThree));
			mpNormal = std::make_shared<Point3d>(rPointNormal);
			this->mMax[0] = mpPoints[0].get()->GetX();
			this->mMax[1] = mpPoints[0].get()->GetY();
			this->mMax[2] = mpPoints[0].get()->GetZ();
			this->mMin[0] = mpPoints[0].get()->GetX();
			this->mMin[1] = mpPoints[0].get()->GetY();
			this->mMin[2] = mpPoints[0].get()->GetZ();
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
		mpPoints.reserve(gAmountOfCoordinates);
		for (size_t i = 0; i < 3; i++)
		{
			mpPoints.push_back(std::make_shared<Point3d>
				(rTriangleCopy.mpPoints[i].get()->GetPoint()));
		}
		mpNormal = std::make_shared<Point3d>(rTriangleCopy.mpNormal->GetPoint());
		for (size_t i = 0; i < 3; i++)
		{
			mMax[i] = rTriangleCopy.mMax[i];
			mMin[i] = rTriangleCopy.mMin[i];
		}
	}
	Triangle::~Triangle()
	{	
	}

	double Triangle::SquareOfTriangle()
	{
		double a = this->mpPoints[0]->GetDistance(this->mpPoints[1]->GetPoint());
		double b = this->mpPoints[1]->GetDistance(this->mpPoints[2]->GetPoint());
		double c = this->mpPoints[2]->GetDistance(this->mpPoints[3]->GetPoint());
		// p - half Perimeter
		double p = (a + b + c)*0.5;
		// Heron formula to count area
		double s = sqrt(p*(p - a)*(p - b)*(p - c));
	return s;
	}
	Point3d Triangle::GetPoints(int i)const
	{
		return mpPoints[i]->GetPoint();
	}

	////////////////////////////////////////////////////////////////
	//If the volume of the tetrahedron /////////////////////////////
	//constructed on four points is 0, then they lie in one plane///
	//
	bool Triangle::IsPointInTiangle(const Point3d& rPoint)const
	{
		Vector3d OA(this->mpPoints[0]->GetPoint() - rPoint);
		Vector3d OB(this->mpPoints[1]->GetPoint() - rPoint);
		Vector3d OC(this->mpPoints[2]->GetPoint() - rPoint);
		Vector3d AB(this->mpPoints[1]->GetPoint() - this->mpPoints[0]->GetPoint());
		Vector3d AC(this->mpPoints[2]->GetPoint() - this->mpPoints[0]->GetPoint());
		double mixProduct = OA.MixedProduct(OB, OC);
		if (!mixProduct)
			return false;
		if ((OA.CrossProduct(OB).Magnitude() + OA.CrossProduct(OC).Magnitude() +
			OB.CrossProduct(OC).Magnitude() -
			AB.CrossProduct(AC).Magnitude()) > TetGen::gRealEpsilon)
			return false;
		return true; 
	}
	bool Triangle::IsIntersectedLineTriangle(const Line& rLine,Point3d& rResultPoint)
	{
		Plane tryIntersect(this->mpPoints[0].get()->GetPoint(),
			this->mpPoints[1].get()->GetPoint(),
			this->mpPoints[2].get()->GetPoint());
		Point3d tryPoint;
		if (!tryIntersect.IsLineIntersectedPlane(rLine.GetLine(), tryPoint))
			return false;
		if (!this->IsPointInTiangle(tryPoint))
			return false;
		rResultPoint = tryPoint;
		return true;
	}
	bool Triangle::IsPointInTop(const Point3d& rPoint)
	{
		if (this->mpPoints[0].get()->GetPoint() == rPoint ||
			this->mpPoints[1].get()->GetPoint() == rPoint ||
			this->mpPoints[2].get()->GetPoint() == rPoint)
			return true;
		return false;
	}

	double* Triangle::GetMax()
	{
		for (size_t i = 0; i < 3; i++)
		{
			if (mMax[0] < mpPoints[i].get()->GetX())
				mMax[0] = mpPoints[i].get()->GetX();
			if (mMax[1] < mpPoints[i].get()->GetY())
				mMax[1] = mpPoints[i].get()->GetY();
			if (mMax[2] < mpPoints[i].get()->GetZ())
				mMax[2] = mpPoints[i].get()->GetZ();
			return mMax;
		}
	}
	double* Triangle::GetMin()
	{
		for (size_t i = 0; i < 3; i++)
		{
			if (mMin[0] > mpPoints[i].get()->GetX())
				mMin[0] = mpPoints[i].get()->GetX();
			if (mMin[1] > mpPoints[i].get()->GetY())
				mMin[1] = mpPoints[i].get()->GetY();
			if (mMin[2] > mpPoints[i].get()->GetZ())
				mMin[2] = mpPoints[i].get()->GetZ();
			return mMin;
		}
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
		mpPoints.reserve(gAmountOfCoordinates);
		for (size_t i = 0; i < 3; i++)
		{
			mpPoints.push_back (std::make_shared<Point3d>
				(rTriangleCopy.mpPoints[i].get()->GetPoint()));
		}
		mpNormal = std::make_shared<Point3d>(rTriangleCopy.mpNormal.get()->GetPoint());
		for (size_t i = 0; i < 3; i++)
		{
			mMax[i] = rTriangleCopy.mMax[i];
			mMax[i] = rTriangleCopy.mMin[i];
		}
		return *this;
	}
	
}