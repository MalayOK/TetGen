#pragma once
#include "stdafx.h"
using namespace std;
namespace TetGen
{
	const double gAbsEpsilon = 1e-12;
	static const double gRealEpsilon = 1e-8;
	const int gInfiniti = 999;
	bool IsAlmostEqualDouble(const double& a, const double& b);
	///Gauss function for solving systems of equations
	int Gauss(vector < vector<double> > a, vector<double> & ans); 
 
}
