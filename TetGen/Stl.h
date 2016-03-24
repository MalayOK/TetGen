#pragma once
#include "stdafx.h"
#include "Triangle.h"

namespace TetGen
{
	class Stl
	{
	public:
		Stl(char* name);
		~Stl();
		void ReadStlFile();
		void ReadBinaryStl();
		void ReadAsciiStl();
		double* GetMinMaxXYZ()const;
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