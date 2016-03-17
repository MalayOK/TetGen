#pragma once
#include "stdafx.h"
#include "Point3d.h"
namespace TetGen
{
	class Vector3d
	{
	public:
		Vector3d(const Point3d& rPoint);
		Vector3d(double x, double y, double z);
		Vector3d(Vector3d& rVector);
		~Vector3d();
		double Magnitude();//Length of vector
		Vector3d Normalize();
		Point3d GetVector()const;
		Vector3d CrossProduct(const Vector3d& rVector1, const Vector3d& rVector2);
		Vector3d CrossProduct(const Vector3d& rVector)const;
		double MixedProduct( const Vector3d& rVector2,const Vector3d& rVector3)const;
		bool IsTwoVectorsColinear(const Vector3d& rVector)const;
		Vector3d operator+ (const Vector3d& rVector)const;
		Vector3d operator- (const Vector3d& rVector)const;
		Vector3d operator* (const double& rScalar)const;//Scalar multiplication
		double operator* (const Vector3d& rVector)const;//DotProduct
		Vector3d operator/(const double& rDivider)const;
		Vector3d operator= (const Vector3d& rVector);
	private:
		Point3d mVector;
	};

}
