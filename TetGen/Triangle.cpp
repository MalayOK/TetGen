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
			mMax.reserve(gAmountOfCoordinates);
			mMin.reserve(gAmountOfCoordinates);
			mpPoints.reserve(gAmountOfCoordinates);
			mpPoints.push_back(std::make_shared<Point3d>(rPointOne));
			mpPoints.push_back(std::make_shared<Point3d>(rPointTwoo));
			mpPoints.push_back(std::make_shared<Point3d>(rPointThree));
			mpNormal = std::make_shared<Point3d>(rPointNormal);
			this->mMax.push_back( mpPoints[0].get()->GetX());
			this->mMax.push_back( mpPoints[0].get()->GetY());
			this->mMax.push_back(mpPoints[0].get()->GetZ());
			this->mMin.push_back(mpPoints[0].get()->GetX());
			this->mMin.push_back(mpPoints[0].get()->GetY());
			this->mMin.push_back(mpPoints[0].get()->GetZ());
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

	bool Triangle::IsIntersectedLT(const Line& rLine, Point3d& rResultPoint)
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

	////////////////////////////////////////////////////////////////
	//If the volume of the tetrahedron /////////////////////////////
	//constructed on four points is 0, then they lie in one plane///
	//
	bool Triangle::IsPointInTiangle(const Point3d& rPoint)
	{
		//// Compute vectors        
		//v0 = C - A
		//	v1 = B - A
		//	v2 = P - A

		//	// Compute dot products
		//	dot00 = dot(v0, v0)
		//	dot01 = dot(v0, v1)
		//	dot02 = dot(v0, v2)
		//	dot11 = dot(v1, v1)
		//	dot12 = dot(v1, v2)

		//	// Compute barycentric coordinates
		//	invDenom = 1 / (dot00 * dot11 - dot01 * dot01)
		//	u = (dot11 * dot02 - dot01 * dot12) * invDenom
		//	v = (dot00 * dot12 - dot01 * dot02) * invDenom

		//	// Check if point is in triangle
		//	return (u >= 0) && (v >= 0) && (u + v < 1)
		Vector3d v0(this->mpPoints[2]->GetPoint() - this->mpPoints[0]->GetPoint());
		Vector3d v1(this->mpPoints[1]->GetPoint() - this->mpPoints[0]->GetPoint());
		Vector3d v2(rPoint - this->mpPoints[0]->GetPoint());
		double dot00 = v0*v0;
		double dot01 = v0*v1;
		double dot02 = v0*v2;
		double dot11= v1*v1;
		double dot12 = v1*v2;
		double invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
		double u = (dot11 * dot02 - dot01 * dot12) * invDenom;
		double v = (dot00 * dot12 - dot01 * dot02) * invDenom;
		if (u >= 0 && v >= 0 && u + v < 1)
			return true;
		return false;
		/*if (IsINSameSide(rPoint.GetPoint(), mpPoints[0]->GetPoint(),
			mpPoints[1]->GetPoint(), mpPoints[2]->GetPoint()) &&
			IsINSameSide(rPoint.GetPoint(), mpPoints[1]->GetPoint(),
				mpPoints[0]->GetPoint(), mpPoints[2]->GetPoint()) &&
			IsINSameSide(rPoint.GetPoint(), mpPoints[2]->GetPoint(),
				mpPoints[0]->GetPoint(), mpPoints[1]->GetPoint()))
			return true;*/
		/*Vector3d OA(this->mpPoints[0]->GetPoint() - rPoint);
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
		return true; */
	}
	bool Triangle::IsINSameSide( Point3d& rPoint1, Point3d& rPoint2,
		 Point3d& rPoint3,  Point3d& rPoint4)
	{
		Vector3d vec1(rPoint1 - rPoint3);
		Vector3d vec2(rPoint4 - rPoint3);
		Vector3d vec3(rPoint2 - rPoint3);
		Vector3d cp1 = vec1.CrossProduct(vec2);
		Vector3d cp2 = vec2.CrossProduct(vec2);
		if (cp1*cp2 >= 0)
			return true;
		return false;
	}

	char* Triangle::GenerateStlTriangle()
	{
		char buffer[300] = "";

		sprintf_s(buffer, "facet normal %e %e %e"
			"\nouter loop\nvertex %e %e %e\n"
			"vertex %e %e %e\n"
			"vertex %e %e %e\n"
			"endloop endfacet\n",
			mpNormal->GetX(), mpNormal->GetY(), mpNormal->GetZ(),
			mpPoints[0]->GetX(), mpPoints[0]->GetY(), mpPoints[0]->GetZ(),
			mpPoints[1]->GetX(), mpPoints[1]->GetY(), mpPoints[1]->GetZ(),
			mpPoints[2]->GetX(), mpPoints[2]->GetY(), mpPoints[2]->GetZ());

		return buffer;
	}
	
	bool Triangle::IsPointInTop(const Point3d& rPoint)
	{
		if (this->mpPoints[0].get()->GetPoint() == rPoint ||
			this->mpPoints[1].get()->GetPoint() == rPoint ||
			this->mpPoints[2].get()->GetPoint() == rPoint)
			return true;
		return false;
	}

	std::vector<double> Triangle::GetMax()
	{
		vector<double>;
		for (size_t i = 0; i < 3; i++)
		{
			if (mMax[0] < mpPoints[i].get()->GetX())
				mMax[0] = mpPoints[i].get()->GetX();
			if (mMax[1] < mpPoints[i].get()->GetY())
				mMax[1] = mpPoints[i].get()->GetY();
			if (mMax[2] < mpPoints[i].get()->GetZ())
				mMax[2] = mpPoints[i].get()->GetZ();
		}
		return mMax;
	}
	std::vector<double> Triangle::GetMin()
	{
		for (size_t i = 0; i < 3; i++)
		{
			if (mMin[0] > mpPoints[i].get()->GetX())
				mMin[0] = mpPoints[i].get()->GetX();
			if (mMin[1] > mpPoints[i].get()->GetY())
				mMin[1] = mpPoints[i].get()->GetY();
			if (mMin[2] > mpPoints[i].get()->GetZ())
				mMin[2] = mpPoints[i].get()->GetZ();
		}
		return mMin;
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