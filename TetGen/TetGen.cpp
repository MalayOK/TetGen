#include "stdafx.h"
#include "Point3d.h"
#include "Mathematic.h"
#include "Line.h"
#include "Triangle.h"
#include "Stl.h"
using namespace TetGen;

int main()
{
	/*Point3d A(1,4,-2);
	Point3d B(3,8,6);
	Point3d C(0, 4, 8);
	Point3d D(6, 10, -10);
	Line AB(A, B);
	Line CD(C, D);
	Point3d result;
	bool flag = AB.Intersection(CD, result);
	bool flag2 = AB.IsParalelLines(AB,CD);
	double ij =result.GetX();
	Triangle ABCD(A, B, C, D);
	A = ABCD.GetPoints(2);*/
	Stl stl("Cone.stl");
	stl.ReadStlFile();
	return 0;
}