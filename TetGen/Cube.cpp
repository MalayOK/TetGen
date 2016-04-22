#include "stdafx.h"
#include "Cube.h"

namespace TetGen
{
	Cube::Cube( vector< Point3d > rVectorOfPoint)
	{
		if (rVectorOfPoint.size()!=8)
			throw std::runtime_error("incorrect number of points.Thee cube should be 8 points ");
		mpPoints.reserve(8);
		for (size_t i = 0; i < 8; i++)
		{
			mpPoints.push_back( std::make_shared<Point3d>(rVectorOfPoint[i]));
		}
	}
	Cube::~Cube()
	{

	}

	bool Cube::IsPointInTop(const Point3d& rPoint)
	{
		for (size_t i = 0; i < 8; i++)
		{
			if (mpPoints[i]->GetPoint() != rPoint)
				return false;
		}
		return true;
	}

	Point3d Cube::GetPoitInTop(const int& rNumberOfTop)const
	{
		if (rNumberOfTop < 1 && rNumberOfTop>8)
			throw std::runtime_error("incorrect number of top.");
		return this->mpPoints[rNumberOfTop]->GetPoint();
	}

	char * Cube::GenerateStl()
	{
		char code[8000] = "";
		for(auto it:mpTetrahedrons)
			strcat_s(code,8000, it->GenerateStlTetra());
		return code;
	}

	void Cube::MakeTetraFullCubes()
	{
		this->mpTetrahedrons.push_back(std::make_shared<Tetrahedron>(
			this->mpPoints[7]->GetPoint(), this->mpPoints[1]->GetPoint(), this->mpPoints[3]->GetPoint(), 
			this->mpPoints[6]->GetPoint()));
		this->mpTetrahedrons.push_back(std::make_shared<Tetrahedron>(
			this->mpPoints[2]->GetPoint(), this->mpPoints[1]->GetPoint(), 
			this->mpPoints[6]->GetPoint(), this->mpPoints[3]->GetPoint()));
		this->mpTetrahedrons.push_back(std::make_shared<Tetrahedron>(
			this->mpPoints[5]->GetPoint(), this->mpPoints[6]->GetPoint(), this->mpPoints[1]->GetPoint(), 
			this->mpPoints[7]->GetPoint()));
		this->mpTetrahedrons.push_back(std::make_shared<Tetrahedron>(
			this->mpPoints[2]->GetPoint(), this->mpPoints[6]->GetPoint(), this->mpPoints[1]->GetPoint(), 
			this->mpPoints[0]->GetPoint()));
		this->mpTetrahedrons.push_back(std::make_shared<Tetrahedron>(
			this->mpPoints[6]->GetPoint(), this->mpPoints[0]->GetPoint(),
			this->mpPoints[4]->GetPoint(), this->mpPoints[1]->GetPoint()));
		this->mpTetrahedrons.push_back(std::make_shared<Tetrahedron>(
			this->mpPoints[6]->GetPoint(), this->mpPoints[1]->GetPoint(), 
			this->mpPoints[4]->GetPoint(), this->mpPoints[5]->GetPoint()));
	}

	void Cube::MakeTetraNotFullInObj()
	{
		if(this->mpPoints[7]->GetIsInBody()&& this->mpPoints[1]->GetIsInBody() && 
			this->mpPoints[3]->GetIsInBody() && this->mpPoints[6]->GetIsInBody())
		this->mpTetrahedrons.push_back(std::make_shared<Tetrahedron>(
			this->mpPoints[7]->GetPoint(), this->mpPoints[1]->GetPoint(),
			this->mpPoints[3]->GetPoint(), this->mpPoints[6]->GetPoint()));
		if (this->mpPoints[2]->GetIsInBody() && this->mpPoints[1]->GetIsInBody() &&
			this->mpPoints[6]->GetIsInBody() && this->mpPoints[3]->GetIsInBody())
		this->mpTetrahedrons.push_back(std::make_shared<Tetrahedron>(
			this->mpPoints[2]->GetPoint(), this->mpPoints[1]->GetPoint(), 
			this->mpPoints[6]->GetPoint(), this->mpPoints[3]->GetPoint()));
		if (this->mpPoints[5]->GetIsInBody() && this->mpPoints[6]->GetIsInBody() &&
			this->mpPoints[1]->GetIsInBody() && this->mpPoints[7]->GetIsInBody())
		this->mpTetrahedrons.push_back(std::make_shared<Tetrahedron>(
			this->mpPoints[5]->GetPoint(), this->mpPoints[6]->GetPoint(),
			this->mpPoints[1]->GetPoint(), this->mpPoints[7]->GetPoint()));
		if (this->mpPoints[2]->GetIsInBody() && this->mpPoints[6]->GetIsInBody() &&
			this->mpPoints[1]->GetIsInBody() && this->mpPoints[0]->GetIsInBody())
		this->mpTetrahedrons.push_back(std::make_shared<Tetrahedron>(
			this->mpPoints[2]->GetPoint(), this->mpPoints[6]->GetPoint(),
			this->mpPoints[1]->GetPoint(), this->mpPoints[0]->GetPoint()));
		if (this->mpPoints[6]->GetIsInBody() && this->mpPoints[0]->GetIsInBody() &&
			this->mpPoints[4]->GetIsInBody() && this->mpPoints[1]->GetIsInBody())
		this->mpTetrahedrons.push_back(std::make_shared<Tetrahedron>(
			this->mpPoints[6]->GetPoint(), this->mpPoints[0]->GetPoint(), 
			this->mpPoints[4]->GetPoint(), this->mpPoints[1]->GetPoint()));
		if (this->mpPoints[6]->GetIsInBody() && this->mpPoints[1]->GetIsInBody() &&
			this->mpPoints[4]->GetIsInBody() && this->mpPoints[5]->GetIsInBody())
		this->mpTetrahedrons.push_back(std::make_shared<Tetrahedron>(
			this->mpPoints[6]->GetPoint(), this->mpPoints[1]->GetPoint(),
			this->mpPoints[4]->GetPoint(), this->mpPoints[5]->GetPoint()));
	}
}