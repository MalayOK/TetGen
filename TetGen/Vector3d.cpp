#include "stdafx.h"
#include "Point3d.h"
#include "Vector3d.h"
namespace TetGen
{
	Vector3d::Vector3d(const Point3d& rPoint)
	{
		mVector = rPoint;
	}

	Vector3d::Vector3d(double x, double y, double z)
	{
		mVector.SetX(x);
		mVector.SetY(y);
		mVector.SetZ(z);
	}

	Vector3d::Vector3d(Vector3d& rVector)
	{
		this->mVector = rVector.mVector;
	}

	Vector3d::~Vector3d()
	{
	}

	double Vector3d::Magnitude()
	{
		double result = sqrt(pow(this->mVector.GetX(), 2) +
			pow(this->mVector.GetY(), 2) +
			pow(this->mVector.GetZ(), 2));
		return result;
	}

	Vector3d Vector3d::Normalize()
	{
		double invertedMagnitude = 1.0f / this->Magnitude();
		this->mVector.SetX(this->mVector.GetX() * invertedMagnitude);
		this->mVector.SetY(this->mVector.GetY() * invertedMagnitude);
		this->mVector.SetZ(this->mVector.GetZ() * invertedMagnitude);
	return *this;
	}

	Point3d Vector3d::GetVector()const
	{
		return this->mVector;
	}
	Vector3d Vector3d::CrossProduct(const Vector3d& rVector1,
		const Vector3d& rVector2)
	{
		double x = rVector1.mVector.GetY()*rVector1.mVector.GetZ() -
			rVector1.mVector.GetY()*rVector1.mVector.GetZ();
		double y = rVector1.mVector.GetZ()*rVector2.mVector.GetX() -
			rVector2.mVector.GetZ()*rVector1.mVector.GetX();
		double z = rVector1.mVector.GetX()*rVector2.mVector.GetY() -
			rVector2.mVector.GetX()*rVector1.mVector.GetY();
		Vector3d cross(x, y, z);
		return cross;
	}

	Vector3d Vector3d::CrossProduct(const Vector3d& rVector)const
	{
		double x = this->mVector.GetY()*rVector.mVector.GetZ() 
			- rVector.mVector.GetY()*this->mVector.GetZ();
		double y = this->mVector.GetZ()*rVector.mVector.GetX()
			- rVector.mVector.GetZ()*this->mVector.GetX();
		double z = this->mVector.GetX()*rVector.mVector.GetY()
			- rVector.mVector.GetX()*this->mVector.GetY();
		Vector3d cross(x, y, z);
	return cross;
	}
	// MixedProduct a · (b x c) 
	double Vector3d::MixedProduct(const Vector3d& rVector2,	const Vector3d& rVector3)const
	{
		Vector3d cross = this->CrossProduct(rVector2);
		return  rVector3*cross;
	}

	bool Vector3d::IsTwoVectorsColinear(const Vector3d& rVector)const
	{
		double x1 = this->mVector.GetX();
		double y1 = this->mVector.GetY();
		double z1 = this->mVector.GetZ();
		double x2 = rVector.mVector.GetX();
		double y2 = rVector.mVector.GetY();
		double z2 = rVector.mVector.GetZ();
		bool flag = IsAlmostEqualDouble(x1 / x2, y1 / y2) &&
			IsAlmostEqualDouble(x1 / x2, z1 / z2) &&
			IsAlmostEqualDouble(z1 / z2, y1 / y2);
		return flag;
	}
	Vector3d Vector3d::operator+ (const Vector3d& rVector)const
	{
		double x = this->mVector.GetX() + rVector.mVector.GetX();
		double y = this->mVector.GetY() + rVector.mVector.GetY();
		double z = this->mVector.GetZ() + rVector.mVector.GetZ();
		Vector3d sum(x, y, z);
	return sum;
	}

	Vector3d Vector3d::operator- (const Vector3d& rVector)const
	{
		double x = this->mVector.GetX() - rVector.mVector.GetX();
		double y = this->mVector.GetY() - rVector.mVector.GetY();
		double z = this->mVector.GetZ() - rVector.mVector.GetZ();
		Vector3d difference(x, y, z);
		return	difference;
	}

	Vector3d Vector3d::operator* (const double& rScalar)const
	{
		double x = this->mVector.GetX() * rScalar;
		double y = this->mVector.GetY() * rScalar;
		double z = this->mVector.GetZ() * rScalar;
		Vector3d product(x, y, z);
		return	product;
	}

	double Vector3d::operator* (const Vector3d& rVector)const
	{
		double dotProduct = this->mVector.GetX() * rVector.mVector.GetX() +
			this->mVector.GetY() * rVector.mVector.GetY() +
			this->mVector.GetZ() * rVector.mVector.GetZ();
		return dotProduct;
	}

	Vector3d Vector3d::operator/(const double& rDivider)const
	{
		if (!rDivider)
			throw std::runtime_error("Diveder cannot be negative");
		double x = this->mVector.GetX() / rDivider;
		double y = this->mVector.GetY() / rDivider;
		double z = this->mVector.GetZ() / rDivider;
		Vector3d result(x, y, z);
		return	result;
	}

	Vector3d Vector3d::operator= (const Vector3d& rVector)
	{
		this->mVector = rVector.mVector;
	return *this;
	}
}