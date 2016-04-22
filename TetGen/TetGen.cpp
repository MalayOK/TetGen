#include "stdafx.h"
//#include "Point3d.h"
//#include "Mathematic.h"
//#include "Line.h"
//#include "Triangle.h"
//#include "Stl.h"
//#include "Plane.h"
#include "Processing.h"

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
	//double min = 0.1;
	//double max = 0.8;
	//double step = 0.1;
	//double min2 = 0.2;
	//double max2 = 0.9;
	//double eps = 0.000000000001;
	//double tmp;
	//int mx = (max - min)/step;
	//int my = (max2 - min2) / step;
	///*for (double m=min; m < max + step; m += step)*/
	//while(!IsAlmostEqualDouble(min,max))
	//for (int i=0; i < mx; i++)
	//for (min; min < max; min += step)
	//{
	//	/*min += step;
	//	tmp = min;
	//	*/
	//	for (double m =min2;m<max2; m += step)
	//	{
	//		std::cout <<"y "<< m << endl;
	//		std::cout << "x " << min << endl;
	//		
	//	}
	//	
	//}
	//int x = 0;
	//cout << x;


	Processing();
	//Point3d norm(0, 0, 0);
	//Point3d A(0.1, 1, 0.1);
	//Point3d B(10, 0.1, 0.1);
	//Point3d C(5, 5, 0.1);
	//Point3d x(2.5, 4, -1);
	//Point3d y(2.5, 4, 5);
	//Triangle ABC(norm ,A, B, C);
	//Line xy(x, y);
	//Point3d result;
	//ABC.IsIntersectedLT(xy, result);

	//double minX = 0.1;
	//double minY = 0.2;
	//double minZ = 0.3;
	//double maxX = 1;
	//double maxY = 2;
	//double maxZ = 3;
	//double step = 0.5;
	//std::vector< std::shared_ptr<Point3d> > rCrossPoints;
	//for (double m0 = minX; m0< maxY; m0 += step)
	//{
	//	for (double m1 = minY; m1 < maxY;m1+=step)
	//	{
	//		for (double m1 = minZ; m1 < maxZ; m1 += step)
	//		{
	//			Point3d tmp(minX, minY, minZ);
	//			rCrossPoints.push_back(std::make_shared<Point3d>(tmp));
	//			minZ += step;
	//			std::cout << minX<<minY<<minZ << endl;
	//		}
	//		minY += step;
	//	}
	//	minX += step;
	//}
	/*Point3d A(1, 1, 4);
	Point3d B(2, 8, 2);
	Line AB(A, B);
	Point3d A1(1.00000001, 1, 4);
	AB.IsPointInLine(A1);*/
	
	/*std::vector <Point3d> v;
	for (int i = 0; i < 8; i++)
	{
		v.push_back(Point3d(i, i, i));
	}
	Cube N(v);*/
	/*
	Stl stl("Cone.stl");
	stl.ReadStlFile();
	std::list< std::shared_ptr<Cube> > rFullListCubes;
	std::list< std::shared_ptr<Cube> > rPartListCubes;
	stl.GenerateCubes(rFullListCubes, rPartListCubes, 10);

	Point3d A(0.5, 0.7, 1);
	Point3d B(0.5, 0.3, 1);
	Line line(A, B);*/
	/*vector<double> result;
	result = stl.GetMinMaxXYZ();
	bool isTrue = stl.IsLineIntersectedTriangles(line);
	std::list< std::shared_ptr<Line> > ListX;
	std::list< std::shared_ptr<Line> > ListY;
	std::list< std::shared_ptr<Line> > ListZ;
	std::vector< std::shared_ptr<Point3d> > CrossPoints;
    stl.ScanObject(6, ListX, ListY, ListZ, CrossPoints);
	int i = 0;
	for (auto it : CrossPoints)
	{
		if (it->GetIsInBody())
			std::cout << "i=" << i++ << endl;
	}

	Point3d C(500, 4, 8);*/
	/*Point3d norm;

	Point3d f(1000000,6, 3);
	Point3d x(0, 4, 8);
	Line AB(f, x);
	Triangle ABC(norm,A, B, C);
	Point3d result(0,0,0);
	bool flag =ABC.IsIntersectedLT(AB,result);*/
	int e;


	return 0;
}