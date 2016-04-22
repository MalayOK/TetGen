#pragma once
#include "stdafx.h"
#include "Triangle.h"
#include "Cube.h"

namespace TetGen
{
	typedef std::list< std::shared_ptr<Cube> >& rListCubes;
	typedef std::list< std::shared_ptr<Line> >& rListLines;
	typedef std::vector< std::shared_ptr<Point3d> >& rIntersectionPoints;
	class Stl
	{
	public:
		Stl(char* name);
		~Stl();
		void ReadStlFile();
		void ReadBinaryStl();
		void ReadAsciiStl();
		vector<double> GetMinMaxXYZ()const;
		bool IsLineIntersectedTriangles(Line& rLine);
		void DrawLine(rListLines rListOfLines,
			int numberOfCubes, const int coordinate, double& rLength,double& rStep);
		void ScanObject(int numberOfCubes, rListLines rListX,
			rListLines rListY, rListLines rListZ, rIntersectionPoints rCrossPoints, std::vector<double>& lengths);
		void GenerateCubes(rListCubes rListFullInObject, rListCubes rListPartlyInObject,int numberOfCubes);
		void GenerateOutFile(rListCubes rCubesFull, rListCubes rCubesPart);
	private:
		char* mName;
		std::list<std::shared_ptr<Triangle>> mpStlTriangle;
	};

	struct TempStl
	{
		std::vector < std::shared_ptr<float>> mpNormal;
		std::vector < std::shared_ptr<float>> mpFirst;
		std::vector < std::shared_ptr<float>> mpSecond;
		std::vector < std::shared_ptr<float>> mpThird;
		short int mAttribute;
	};

	
}