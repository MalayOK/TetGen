#include "stdafx.h"
#include "Point3d.h"
namespace TetGen
{
	Point3d::Point3d()
	{
		mX = 0;
		mY = 0;
		mZ = 0;
	}

	Point3d::Point3d(double X, double Y, double Z) :mX(X), mY(Y), mZ(Z)
	{
	}

	Point3d::~Point3d()
	{
	}

	double Point3d::GetX()const
	{
		return mX;
	}

	double Point3d::GetY()const
	{
		return mY;
	}

	double Point3d::GetZ()const
	{
		return mZ;
	}
	Point3d Point3d::GetPoint()const
	{
		return *this;
	}
	double Point3d::GetDistance(const Point3d& rPoint)const
	{
		double Distance = sqrt(pow(this->GetX() - rPoint.GetX(), 2) +
			pow(this->GetY() - rPoint.GetY(), 2) +
			pow(this->GetZ() - rPoint.GetZ(), 2));
		return Distance;
	}

	void Point3d::SetX(double X)
	{
		mX = X;
	}
	void Point3d::SetY(double Y)
	{
		mY = Y;
	}

	void Point3d::SetZ(double Z)
	{
		mZ = Z;
	}

	Point3d Point3d::operator+(const Point3d& rPoint)const
	{
		Point3d Result;
		    Result.SetX(this->GetX() + rPoint.GetX());
			Result.SetY(this->GetY() + rPoint.GetY());
			Result.SetZ(this->GetZ() + rPoint.GetZ());
		return Result;
	}

	Point3d Point3d::operator-(const Point3d& rPoint)const
	{
		Point3d Result;
		Result.SetX(this->GetX() - rPoint.GetX());
		Result.SetY(this->GetY() - rPoint.GetY());
		Result.SetZ(this->GetZ() - rPoint.GetZ());
	return Result;
	}

	Point3d Point3d::operator=(const Point3d& rPoint)
	{
		this->SetX(rPoint.GetX());
		this->SetY(rPoint.GetY());
		this->SetZ(rPoint.GetZ());
	return *this;
	}

	bool Point3d::operator==(const Point3d& rPoint)
	{
		if (IsAlmostEqualDouble(this->GetX(), rPoint.GetX()) &&
			IsAlmostEqualDouble(this->GetY(), rPoint.GetY()) &&
			IsAlmostEqualDouble(this->GetZ(), rPoint.GetZ()))
		return true;
		return false;
	}

	bool Point3d::operator!=(const Point3d& rPoint)
	{
		return !(*this == rPoint);
	}
}