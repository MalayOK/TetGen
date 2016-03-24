#include "stdafx.h"
#include "Point3d.h"
#include "Mathematic.h"
#include "Line.h"
#include "Triangle.h"
#include "Stl.h"
#include "Triangle.h"
using namespace TetGen;

int main()
{
	//Point3d A(1,4,-2);
	//Point3d B(3,8,6);
	//Point3d C(0, 4, 8);
	//Point3d D(6, 10, -10);
	//Line AB(A, B);
	//Line CD(C, D);
	//Point3d result;
	//bool flag = AB.Intersection(CD, result);
	//bool flag2 = AB.IsParalelLines(AB,CD);
	//double ij =result.GetX();
	//Triangle ABCD(A, B, C, D);
	//A = ABCD.GetPoints(2);
	//Stl stl("knot.stl");
	//stl.ReadStlFile();

	//double* x= stl.GetMinMaxXYZ();
	Point3d norm;
	Point3d A(2.2, 3.5, 4.656);
	Point3d B(3, 8, 6);
	Point3d C(500, 4, 8);
	Point3d f(1000000,6, 3);
	Point3d x(0, 4, 8);
	Line AB(f, x);
	Triangle ABC(norm,A, B, C);
	Point3d result(0,0,0);
	bool flag =ABC.IsIntersectedLineTriangle(AB,result);
	return 0;
}