#include "stdafx.h"
#include "Stl.h"

namespace TetGen
{
	Stl::Stl(char* name)/* : mName(name)*/
	{
		mName = name;
	}

	Stl::~Stl()
	{}

	void Stl::ReadStlFile()
	{
		char name[30];
		ifstream readStl(mName, ios::in);
		if (!readStl)
		{
			system("cls");
			cout << "Wrong file name.\n";
			while (!readStl)
			{
				cout << "Enter right file name : ";
				cin >> name;
				readStl.open(name, ios::in);
				mName = name;
			}
		}
			char buffer[50]; 
			readStl >> buffer;
			bool isASCII = false;
			if (!strcmp(buffer,"solid"))
			{
				readStl.close();
				ReadAsciiStl();
			}
			readStl.close();
			ReadBinaryStl();
		
	}

	//An ASCII STL file begins with the line
	/*solid name
	where name is 
	an optional string
	(though if name is omitted there must still be 
	a space after solid).The file continues with any number of 
	triangles, each represented as follows :
	facet normal ni nj nk
	outer loop
	vertex v1x v1y v1z
	vertex v2x v2y v2z
	vertex v3x v3y v3z
	endloop
	endfacet
	where each n or v is a floating - point number in sign 
	- mantissa - "e" - sign - exponent format, e.g., "2.648000e-002" 
	(noting that each v must be non - negative).The file concludes with
	endsolid name*/
	//////////////////////////////////////////////////////////

	void Stl::ReadAsciiStl()
	{
		ifstream readFile(mName, ios::in);
		char buffer[50]; 
		readFile >> buffer;
		while (!readFile.eof()) {
			readFile >> buffer;
			list<std::shared_ptr<Point3d>> points;
			list<shared_ptr<Point3d>>::iterator iterPoint[4];
			if (!strcmp(buffer, "facet")) {
				while (strcmp(buffer, "endloop")) {
					readFile >> buffer;
					if (!strcmp(buffer, "normal") || !strcmp(buffer, "vertex")) {
						double value[3];
						for (int i = 0; i < 3; i++)
							readFile >> value[i];
						points.push_back(std::make_shared<Point3d>(value[0],
							value[1], value[2]));
					}
				}
				iterPoint[0] = points.begin();
				for (int i = 1; i < 4; i++) {
					iterPoint[i] = ++iterPoint[i - 1];
					iterPoint[i - 1]--;
				}
				std::shared_ptr<Triangle> readedTriangle = std::make_shared<Triangle>
					(iterPoint[0]->get()->GetPoint(),
						iterPoint[1]->get()->GetPoint(),
						iterPoint[2]->get()->GetPoint(),
						iterPoint[3]->get()->GetPoint());
				mpStlTriangle.push_back(readedTriangle);
				points.clear();
			}
		}
		readFile.close();
	}


	//////////////////////////////////////
	//UINT8[80] – Header
	//UINT32 – Number of triangles
	//	foreach triangle
	//	REAL32[3] – Normal vector
	//	REAL32[3] – Vertex 1
	//	REAL32[3] – Vertex 2
	//	REAL32[3] – Vertex 3
	//	UINT16 – Attribute byte count
	//	end
	void Stl::ReadBinaryStl()
	{
		char name[80];
		int numberOfTriangles = 0;
		FILE *file;
		std::list<std::shared_ptr<Triangle>>::iterator iterTriangle;//temp
		/*file = */fopen_s(&file,mName, "rb");
		fread(name, sizeof(char[80]), 1, file);
		fread(&numberOfTriangles, sizeof(int), 1, file);
		for (int i = 0; i < numberOfTriangles; i++)
		{
			float temp;
			TempStl triangle ;
			triangle.mpNormal.reserve(3);
			triangle.mpFirst.reserve(3);
			triangle.mpSecond.reserve(3);
			triangle.mpThird.reserve(3);
			/*for (int i = 0; i < 3; i++)
			{
				triangle.mpNormal[i] = std::make_shared<float>;
				triangle.mpFirst.assign = std::make_shared<float>(0);
				triangle.mpSecond.assign = std::make_shared<float>(0);
				triangle.mpThird.assign = std::make_shared<float>(0);
			}*/
			for (int k = 0; k < 3; k++)
			{
				fread(&temp, sizeof(float), 1, file);
				triangle.mpNormal.push_back(std::make_shared<float>(temp));
			}
			for (int k = 0; k < 3; k++)
			{
				fread(&temp, sizeof(float), 1, file);
				triangle.mpFirst.push_back(std::make_shared<float>(temp));
			}
			for (int k = 0; k < 3; k++)
			{
				fread(&temp, sizeof(float), 1, file);
				triangle.mpSecond.push_back(std::make_shared<float>(temp));
			}
				
			for (int k = 0; k < 3; k++)
			{
				fread(&temp, sizeof(float), 1, file);
				triangle.mpThird.push_back(std::make_shared<float>(temp));
			}
				
			fread(&triangle.mAttribute, sizeof(short int), 1, file);
			list<std::shared_ptr<Point3d>> points;
			list<std::shared_ptr<Point3d>>::iterator iterPoint[4];
			points.push_back(std::make_shared<Point3d>(double(*triangle.mpNormal[0].get()),
				double(*triangle.mpNormal[1].get()), double(*triangle.mpNormal[2].get())));
			points.push_back(std::make_shared<Point3d>(double(*triangle.mpFirst[0].get()),
				double(*triangle.mpFirst[1].get()), double(*triangle.mpFirst[2].get())));
			points.push_back(std::make_shared<Point3d>(double(*triangle.mpSecond[0].get()),
				double(*triangle.mpSecond[1].get()), double(*triangle.mpSecond[2].get())));
			points.push_back(std::make_shared<Point3d>(double(*triangle.mpThird[0].get()),
				double(*triangle.mpThird[1].get()), double(*triangle.mpThird[2].get())));
			iterPoint[0] = points.begin();
			for (int i = 1; i < 4; i++) {
				iterPoint[i] = ++iterPoint[i - 1];
				iterPoint[i - 1]--;
			}
			std::shared_ptr<Triangle> readedTriangle = std::make_shared<Triangle>
				(iterPoint[0]->get()->GetPoint(),
					iterPoint[1]->get()->GetPoint(),
					iterPoint[2]->get()->GetPoint(),
					iterPoint[3]->get()->GetPoint());
			mpStlTriangle.push_back(readedTriangle);
			points.clear();
			triangle.mpNormal.clear();
			triangle.mpFirst.clear();
			triangle.mpSecond.clear();
			triangle.mpThird.clear();
		}
		fclose(file);
	}
	///return minimal and maximal x y z 
	///temp[0]-min x temp[1]-min y temp[2]-min z
	///temp[3]-max x temp[4]-max y temp[5]-max z
	double* Stl::GetMinMaxXYZ()const
	{
		std::list<std::shared_ptr<Triangle>>::const_iterator itList;
		itList = mpStlTriangle.begin();
		double temp[6];
		temp[0] = itList->get()->GetMin()[0];
		temp[1] = itList->get()->GetMin()[1];
		temp[2] = itList->get()->GetMin()[2];
		temp[3] = itList->get()->GetMax()[3];
		temp[4] = itList->get()->GetMax()[4];
		temp[5] = itList->get()->GetMax()[5];
		for (itList; itList != mpStlTriangle.end(); itList++)
		{
			for (size_t i = 0; i<3; i++)
			{
				temp[i] = (temp[i] > itList->get()->GetMin()[i]) ?
					itList->get()->GetMin()[i] : temp[i];
			}
			for (size_t j = 3; j<6; j++)
			{
				temp[j] = (temp[j] < itList->get()->GetMax()[j]) ?
					itList->get()->GetMax()[j] : temp[j];
			}
		}
		return temp;
	}
}