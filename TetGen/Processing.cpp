#include "stdafx.h"
#include "Processing.h"
namespace TetGen
{
	void Processing()
	{
		Stl stl("2.stl");
		stl.ReadStlFile();
		std::list< std::shared_ptr<Cube> > rFullListCubes;
		std::list< std::shared_ptr<Cube> > rPartListCubes;
		std::cout << "enter the minimum number of cubes" << endl;
		unsigned int numberOfCubes;
		std::cin >> numberOfCubes;
		stl.GenerateCubes(rFullListCubes, rPartListCubes, numberOfCubes);
		for (auto it : rFullListCubes)
			it->MakeTetraFullCubes();
		for (auto it : rPartListCubes)
			it->MakeTetraNotFullInObj();
			//it->MakeTetraFullCubes();
		stl.GenerateOutFile(rFullListCubes,rPartListCubes);
	}
}

