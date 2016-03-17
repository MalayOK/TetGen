#include "stdafx.h"
#include "Line.h"

namespace TetGen
{
	Line::Line(double x1, double y1, double z1, double x2, 
		double y2, double z2)
	{
		this->mpStartPoint->SetX(x1);
		this->mpStartPoint->SetY(y1);
		this->mpStartPoint->SetZ(z1);
		this->mpEndPoint->SetX(x2);
		this->mpEndPoint->SetY(y2);
		this->mpEndPoint->SetZ(z2);
	}

	Line::Line(const Point3d& rStartPoint, const Point3d& rEndPoint)
	{
		this->mpStartPoint = std::make_shared<Point3d>(rStartPoint);
		this->mpEndPoint = std::make_shared<Point3d>(rEndPoint);
	}

	Line::Line(const Line& rLineCopy)
	{
		*this = rLineCopy;
	}

	Line::~Line()
	{
	}
	////////////////////////////////////////////////////////////////////////////////////
	//Two lines are parallel if and only if their vector product direction vectors is 0.
	///////////////////////////////////////////////////////////////////////////////////
	bool Line::IsParalelLines(const Line& rLine1, const Line& rLine2)
	{
		Vector3d vector1(rLine1.mpEndPoint->GetPoint());
		Vector3d vector2(rLine2.mpEndPoint->GetPoint());
		Vector3d cross = vector1.CrossProduct(vector2);
		return IsAlmostEqualDouble(cross.GetVector().GetX(), 0) &&
			IsAlmostEqualDouble(cross.GetVector().GetY(), 0) &&
			IsAlmostEqualDouble(cross.GetVector().GetZ(), 0);
	}

	bool Line::IsPointInLine(const Point3d& rPoint)
	{
		double x0 = rPoint.GetX();
		double y0 = rPoint.GetY();
		double z0 = rPoint.GetZ();
		double x1 = this->mpStartPoint->GetX();
		double y1 = this->mpStartPoint->GetY();
		double z1 = this->mpStartPoint->GetZ();
		double x2 = this->mpEndPoint->GetX();
		double y2 = this->mpEndPoint->GetY();
		double z2 = this->mpEndPoint->GetZ();
		bool flag = IsAlmostEqualDouble((x0 - x1) * z2, (y0 - y1) * x2) &&
			IsAlmostEqualDouble((x0 - x1) * z2, (z0 - z1) * x2) &&
			IsAlmostEqualDouble((y0 - y1) * z2, (z0 - z1) * y2);
		return flag;
	}

	Point3d Line::GetStartPoint()const
	{
		return this->mpStartPoint->GetPoint();
	}

	Point3d Line::GetEndPoint()const
	{
		return this->mpEndPoint->GetPoint();
	}
	////////////////////////////////////////////////////////////////////////////////
	//if the mixed product of vectors! = 0,
	//then they lie in different planes, and can not intersect
	//if the vectors are collinear.The lines are parallel or coincide 
	//Create a system of linear equations and solve the Gauss method,
	//if the number of solutions is equal to 1, 
	//the lines intersect, and we return through the intersection point of reference
	///////////////////////////////////////////////////////////////////////////////
	bool Line::Intersection(Line& rLine, Point3d& rPoint)
	{
		/*Vector3d p1(this->GetEndPoint());
		Vector3d p2(rLine.GetEndPoint());
		Vector3d M1M2(rLine.GetStartPoint() - this->GetStartPoint());
		double result = p1.MixedProduct(p2, M1M2);
		if (result)                                      
			return false;
		bool isColinear = p1.IsTwoVectorsColinear(p2);
		if (isColinear)
			return false;*/

		Point3d CD = rLine.GetEndPoint() - rLine.GetStartPoint();
		Point3d AB = this->GetEndPoint() - this->GetStartPoint();
		double CDx = CD.GetX();
		double ABx = -AB.GetX();
		double coefX = this->mpStartPoint->GetX() - rLine.GetStartPoint().GetX();
		double CDy = CD.GetY();
		double ABy = -AB.GetY();
		double coefY = this->mpStartPoint->GetY() - rLine.GetStartPoint().GetY();
		double CDz = CD.GetZ();
		double ABz = -AB.GetZ();
		double coefZ = this->mpStartPoint->GetZ() - rLine.GetStartPoint().GetZ();
		std::vector<std::vector<double> > imatrix;
		std::vector<double> temp;
		temp.push_back(CDx);
		temp.push_back(ABx);
		temp.push_back(coefX);
		imatrix.push_back(temp);
		temp.clear();
		temp.push_back(CDy);
		temp.push_back(ABy);
		temp.push_back(coefY);
		imatrix.push_back(temp);
		temp.clear();
		temp.push_back(CDz);
		temp.push_back(ABz);
		temp.push_back(coefZ);
		imatrix.push_back(temp);
		temp.clear();
		vector<double> ansver;
		int res = Gauss(imatrix, ansver);
		if (res == 1)
		{
			double s = ansver.at(0);
			double x = s * CDx + rLine.GetStartPoint().GetX();
			double y = s * CDy + rLine.GetStartPoint().GetY();
			double z = s * CDz + rLine.GetStartPoint().GetZ();
			rPoint.SetX(x);
			rPoint.SetY(y);
			rPoint.SetZ(z);
			return true;
		}
		return false;
	}
}