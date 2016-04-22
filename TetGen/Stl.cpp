#include "stdafx.h"
#include "Stl.h"

namespace TetGen
{
	std::mutex gMutex;
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
	vector<double> Stl::GetMinMaxXYZ()const
	{
		std::list<std::shared_ptr<Triangle>>::const_iterator itList;
		itList = mpStlTriangle.begin();
		vector<double> temp;
		temp.reserve(6);
		temp.push_back( itList->get()->GetMin()[0]);
		temp.push_back(itList->get()->GetMin()[1]);
		temp.push_back(itList->get()->GetMin()[2]);
		temp.push_back(itList->get()->GetMax()[0]);
		temp.push_back(itList->get()->GetMax()[1]);
		temp.push_back(itList->get()->GetMax()[2]);
		for (itList; itList != mpStlTriangle.end(); itList++)
		{
			for (size_t i = 0; i<3; i++)
			{
				temp[i] = (temp[i] > itList->get()->GetMin()[i]) ?
					itList->get()->GetMin()[i] : temp[i];
			}
			for (size_t j = 3; j<6; j++)
			{
				temp[j] = (temp[j] < itList->get()->GetMax()[j-3]) ?
					itList->get()->GetMax()[j-3] : temp[j];
			}
		}
		return temp;
	}

	bool Stl::IsLineIntersectedTriangles(Line& rLine)
	{
	std::vector<std::shared_ptr<Point3d>> intersectPoints;
	Point3d tempPoint;
	for (std::list<std::shared_ptr<Triangle>>::iterator
	it = mpStlTriangle.begin(); it != mpStlTriangle.end(); ++it)
	{
	if (it->get()->IsIntersectedLT(rLine, tempPoint))
	{
		intersectPoints.push_back(std::make_shared<Point3d>(tempPoint));
	}
	}
	if (intersectPoints.size() > 0)
	{
		rLine.SetPointOfIntersection(intersectPoints);
		return true;
	}
	
	return false;
	}
	void Stl::GenerateCubes(rListCubes rListFullInObject, rListCubes rListPartlyInObject, int numberOfCubes)
	{
		std::list< std::shared_ptr<Line> > ListX;
		std::list< std::shared_ptr<Line> > ListY;
		std::list< std::shared_ptr<Line> > ListZ;
		std::vector< std::shared_ptr<Point3d> > CrossPoints;
		std::vector<double> length;
		length.reserve(4);
		ScanObject(numberOfCubes, ListX, ListY, ListZ, CrossPoints, length);
		std::vector< Point3d > TempPoints;
		TempPoints.reserve(8);
		int maxX = (int)(length[0] / length[3])+1;
		int maxY = (int)(length[1] / length[3])+1;
		int maxZ = (int)(length[2] / length[3])+1;
		int k = maxZ;
		int p = maxY;
		std::cout <<"Size" <<CrossPoints.size() << endl;
		
		//for (int i = 0; i <k ; ++i)
		//int i = 0;
		//while(1)
		vector <double> MinMax = this->GetMinMaxXYZ();
		Point3d Min(MinMax[0], MinMax[1], MinMax[2]);
		Point3d Max(MinMax[3], MinMax[4], MinMax[5]);
		for (int i = 0;;i++)
		{
			if (i + maxZ*maxY + maxZ + 1 == CrossPoints.size())
				break;
			//i++;
			if (i == k-1)
			{
				k += k;
				continue;
			}
			if (i <= p*maxZ - 1 && i  >= p*maxZ - maxZ)
			{
				if (i == p)
					p += p;
				continue;
			}
			TempPoints.push_back(CrossPoints[i]->GetPoint());
			TempPoints.push_back(CrossPoints[i+1]->GetPoint());
			TempPoints.push_back(CrossPoints[i + maxZ]->GetPoint());
			TempPoints.push_back(CrossPoints[i + maxZ+1]->GetPoint());
			TempPoints.push_back(CrossPoints[i + maxZ*maxY]->GetPoint());
			TempPoints.push_back(CrossPoints[i + maxZ*maxY+1]->GetPoint());
			TempPoints.push_back(CrossPoints[i + maxZ*maxY+maxZ]->GetPoint());
			TempPoints.push_back(CrossPoints[i + maxZ*maxY + maxZ+1]->GetPoint());
			int pointsInObj = 0;
			for (auto it : TempPoints)
			{
				if (it.GetIsInBody())
					++pointsInObj;
				if (it.GetX()<Min.GetX())
					std::cout << " Cross X " << it.GetX();
				if (it.GetX()>Max.GetX())
					std::cout << " Cross X " << it.GetX();
				if (it.GetY()<Min.GetY())
					std::cout << " Cross Y " << it.GetY();
				if (it.GetY()>Max.GetY())
					std::cout << " Cross Y " << it.GetY();
				if (it.GetZ()<Min.GetZ())
					std::cout << " Cross Z " << it.GetZ();
				if (it.GetZ()>Max.GetZ())
					std::cout << " Cross Z " << it.GetZ();
			}
			if (pointsInObj >= 0 && pointsInObj < 8)
				rListPartlyInObject.push_back(std::make_shared<Cube>(TempPoints));
			if (pointsInObj ==8)
				rListFullInObject.push_back(std::make_shared<Cube>(TempPoints));
			TempPoints.clear();
		
		}

		

	}
	//method to generate lines for scanning 3d object in 3 axes .
	//Using three threads for faster scanning. 
	//The points of intersection with triangles, are stored in the object line
	//Return cross points by reference and 3 List of Lines
	void Stl::ScanObject(int numberOfCubes, rListLines rListX,
		rListLines rListY, rListLines rListZ, rIntersectionPoints rCrossPoints, std::vector<double>& lengths)
	{
		double lengthX;
		double lengthY;
		double lengthZ;
		double step;
		vector <double> MinMax = this->GetMinMaxXYZ();
		Point3d Min(MinMax[0], MinMax[1], MinMax[2]);
		Point3d Max(MinMax[3], MinMax[4], MinMax[5]);
		std::thread t1(&Stl::DrawLine,this, std::ref(rListX), numberOfCubes, 0, std::ref(lengthX), std::ref(step));
		std::thread t2(&Stl::DrawLine,this, std::ref(rListY), numberOfCubes, 1, std::ref(lengthY), std::ref(step));
		std::thread t3(&Stl::DrawLine,this, std::ref(rListZ), numberOfCubes, 2, std::ref(lengthZ), std::ref(step));
		t1.join();
		t2.join();
		t3.join();
		std::cout << "ListX.size() " << rListX.size() << endl;
		std::cout << "ListY.size() " << rListY.size() << endl;
		std::cout << "ListZ.size() " << rListZ.size() << endl;
		lengths.push_back(lengthX);
		lengths.push_back(lengthY);
		lengths.push_back(lengthZ);
		lengths.push_back(step);
		for (auto ItLX : rListX)
		{
			for (auto ItLY : rListY)
			{
				Point3d tmp;
				bool flag = ItLX->Intersection(*ItLY.get(), tmp);
				/*bool isInLineX = ItLX->IsPointInLineSegment(tmp);
				bool isInLineY = ItLY->IsPointInLineSegment(tmp);*/
				/*if (isInLineY)
				{
					tmp.SetIsInBody(true);
				}*/
				if (flag)
				{
					
					rCrossPoints.push_back(std::make_shared<Point3d>(tmp));
				}
			}
		}

		for (auto it : rCrossPoints)
		{
			if (it->GetX()<Min.GetX())
			std::cout << " Cross X " << it->GetX();
			if (it->GetX()>Max.GetX())
				std::cout << " Cross X " << it->GetX();
			if (it->GetY()<Min.GetY())
				std::cout << " Cross Y " << it->GetY();
			if (it->GetY()>Max.GetY())
				std::cout << " Cross Y " << it->GetY();
			if (it->GetZ()<Min.GetZ())
				std::cout << " Cross Z " << it->GetZ();
			if (it->GetZ()>Max.GetZ())
				std::cout << " Cross Z " << it->GetZ();
			
		}

	/*	for (auto it : rListX)
		{
			std::cout << " StartX X " << it->GetStartPoint().GetX();
			std::cout << " StartX  Y " << it->GetStartPoint().GetY();
			std::cout << " StartX  Z " << it->GetStartPoint().GetZ() << endl;
			std::cout << " EndX X " << it->GetEndPoint().GetX();
			std::cout << " EndX Y " << it->GetEndPoint().GetY();
			std::cout << " EndX Z " << it->GetEndPoint().GetZ() << endl;
		}*/

		/*for (auto it : rListZ)
		{
			std::cout << " StartZ X " << it->GetStartPoint().GetX();
			std::cout << " StartZ Y " << it->GetStartPoint().GetY();
			std::cout << " StartZ Z " << it->GetStartPoint().GetZ() << endl;
			std::cout << " EndZ X " << it->GetEndPoint().GetX();
			std::cout << " EndZ Y " << it->GetEndPoint().GetY();
			std::cout << " EndZ Z " << it->GetEndPoint().GetZ() << endl;
		}*/
	
			
		/*double minX = MinMax[0];
		double minY = MinMax[1];
		double minZ = MinMax[2];
		double maxX = MinMax[3];
		double maxY = MinMax[4];
		double maxZ = MinMax[5];
		while (minX <= maxX)
		{
			while (minY <= maxY)
			{
				while (minZ <= maxZ)
				{
					Point3d tmp(minX, minY, minZ);
					rCrossPoints.push_back(std::make_shared<Point3d>(tmp));
					minZ += step;
				}
				minY += step;
			}
			minX += step;
		}*/
		int inc = 0;
		int inc2 = 0;
		int Z = (int)lengthZ / step ;
		int maxZ= (int)(lengthZ / step)+1 ;
		int maxX = (int)(lengthX / step) + 1;
		int maxY = (int)(lengthY / step) + 1;
		for (auto ItLX : rListX)
		{
			for (int i = 0; i < Z;i++)
			{
				if (ItLX->IsPointInLineSegment(rCrossPoints[i + inc]->GetPoint()))
				{
					rCrossPoints[i + inc]->SetIsInBody(true);
					/*std::cout <<" X " <<rCrossPoints[i + inc]->GetX() ;
					std::cout << " Y "<<rCrossPoints[i + inc]->GetY() ;
					std::cout << " Z " << rCrossPoints[i + inc]->GetZ() << endl;*/
			
				}
			}
			inc+=maxZ;
		}
		for (auto ItLY : rListY)
		{
			for (int i = inc2; i < rCrossPoints.size(); i+=maxX*maxY)
			{
				if (ItLY->IsPointInLineSegment(rCrossPoints[i]->GetPoint()))
				{
					rCrossPoints[i]->SetIsInBody(true);
					/*std::cout <<" X " <<rCrossPoints[i + inc]->GetX() ;
					std::cout << " Y "<<rCrossPoints[i + inc]->GetY() ;
					std::cout << " Z " << rCrossPoints[i + inc]->GetZ() << endl;*/

				}
				//rCrossPoints[i]->SetIsInBody(false);
			}
			inc2++;
		}

		//for (auto ItLZ : rListZ)
		//{
		//	for (int i = 0; i < rCrossPoints.size(); i ++)
		//	{
		//		if (ItLZ->IsPointInLineSegment(rCrossPoints[i]->GetPoint()))
		//		{
		//			rCrossPoints[i]->SetIsInBody(true);
		//			/*std::cout <<" X " <<rCrossPoints[i + inc]->GetX() ;
		//			std::cout << " Y "<<rCrossPoints[i + inc]->GetY() ;
		//			std::cout << " Z " << rCrossPoints[i + inc]->GetZ() << endl;*/

		//		}
		//		//rCrossPoints[i]->SetIsInBody(false);
		//	}
	
		//}



		/*double minX = MinMax[0];
		double minY = MinMax[1];
		double minZ = MinMax[2];
		double maxX = MinMax[3];
		double maxY = MinMax[4];
		double maxZZ = MinMax[5];*/
		std::cout << "MinMax"<<endl;
		std::cout <<"minX"<< MinMax[0];
		std::cout << "minY" << MinMax[1];
		std::cout << "minZ" << MinMax[2];
		std::cout << "maxX" << MinMax[3];
		std::cout << "maxY" << MinMax[4];
		std::cout << "maxZ" << MinMax[5];

		/*for (auto ItLX : rListX)
		{
			for (auto ItLZ : rListZ)
			{
				Point3d tmp;
				bool flag = ItLX->Intersection(*ItLZ.get(), tmp);
				bool isInLineX = ItLX->IsPointInLineSegment(tmp);
				bool isInLineZ = ItLZ->IsPointInLineSegment(tmp);
				if (isInLineX || isInLineZ)
				{
					tmp.SetIsInBody(true);
				}
				if (flag)
				{
					rCrossPoints.push_back(std::make_shared<Point3d>(tmp));
				}
			}
		}

		for (auto ItLZ : rListZ)
		{
			for (auto ItLY : rListY)
			{
				Point3d tmp;
				bool flag = ItLZ->Intersection(*ItLY.get(), tmp);
				bool isInLineZ = ItLZ->IsPointInLineSegment(tmp);
				bool isInLineY = ItLY->IsPointInLineSegment(tmp);
				if (isInLineZ || isInLineY)
				{
					tmp.SetIsInBody(true);
				}
				if (flag)
				{
					rCrossPoints.push_back(std::make_shared<Point3d>(tmp));
				}
			}
		}*/

		std::cout << "IntersectionPoints.size() " << rCrossPoints.size() << endl;
		int k = 0;
		std::cout << "step " << lengthZ << endl;
		int incrementer = (int)(lengthZ / step);
		/*for (auto ItLZ : rListZ)
		{
			++k;
			std::cout << "k " << k << endl;
			for (int i = 0; i < rCrossPoints.size();i++)
			{
				bool isInLine= ItLZ->IsPointInLineSegment(rCrossPoints[i].get()->GetPoint());
				std::cout << "i " << i << endl;
				if (isInLine)
					rCrossPoints[i].get()->SetIsInBody(true);
			}
		}*/
		//return ListY;
	}
	void Stl::DrawLine(rListLines rListOfLines,
		int numberOfCubes,const int coordinate,double& rLength,double& rStep)
	{
		gMutex.lock();
		vector<double> minMax = this->GetMinMaxXYZ();
		double minLength = minMax[3] - minMax[0];//max x - min x
		minLength = (minLength > minMax[4] - minMax[1]) ? (minMax[4] - minMax[1]) : minLength;//max y - min y
		minLength = (minLength > minMax[5] - minMax[2]) ? (minMax[5] - minMax[2]) : minLength;//max z - min z
		double edge = minLength / numberOfCubes;
		rStep = edge;
		switch (coordinate)
		{
			
		case 0:
			rLength = minMax[3] - minMax[0];
			break;
		case 1:
			rLength = minMax[4] - minMax[1];
			break;
		case 2:
			rLength = minMax[5] - minMax[2];
			break;
		}
		double min;
		double max;
		double nextMin;
		double nextMax;
		double lineMin;
		double lineMax;
		Point3d tempStart;
		Point3d tempEnd;
		for (size_t i = 0; i < 3;i++)
		{
			if (coordinate == i)
			{
				min = minMax[i];
				max = minMax[i+3];
				if (i==0)
				{
					nextMin = minMax[i + 1];
					nextMax = minMax[i + 4];
					lineMin = minMax[i + 2];
					lineMax = minMax[i + 5];
				}
				if (i == 1)
				{
					nextMin = minMax[i + 1];
					nextMax = minMax[i + 4];
					lineMin = minMax[i - 1];
					lineMax = minMax[i + 2];
				}
				if (i == 2)
				{
					nextMin = minMax[i - 2];
					nextMax = minMax[i + 1];
					lineMin = minMax[i - 1];
					lineMax = minMax[i + 2];
				}
				
			}
		}

		int z = 0;
		int y = 0;
		int x = 0;
		for (min; min <= max; min += edge)
		{
			for (double m=nextMin; m <= nextMax; m += edge)
			{
				switch (coordinate)
				{
					
				case 0:
					++z;
					tempStart.SetX(min);
					tempStart.SetY(m);
					tempStart.SetZ(lineMin);
					tempEnd.SetX(min);
					tempEnd.SetY(m);
					tempEnd.SetZ(lineMax);
					rListOfLines.push_back(std::make_shared<Line>(tempStart, tempEnd));
					break;
				case 1:
					tempStart.SetX(lineMin);
					tempStart.SetY(min);
					tempStart.SetZ(m);
					tempEnd.SetX(lineMax);
					tempEnd.SetY(min);
					tempEnd.SetZ(m);
					rListOfLines.push_back(std::make_shared<Line>(tempStart, tempEnd));
					break;
				case 2:
					tempStart.SetX(m);
					tempStart.SetY(lineMin);
					tempStart.SetZ(min);
					tempEnd.SetX(m);
					tempEnd.SetY(lineMax);
					tempEnd.SetZ(min);
					rListOfLines.push_back(std::make_shared<Line>(tempStart, tempEnd));
					break;
				}
					
			}
		}
		std::list< std::shared_ptr<Line> >::iterator ItLines;
		ItLines = rListOfLines.begin();
		for (ItLines; ItLines != rListOfLines.end(); ItLines++)
		{
			bool flag=this->IsLineIntersectedTriangles(*ItLines->get());
			std::cout << flag << endl;
		}
		gMutex.unlock();
	}

	void Stl::GenerateOutFile( rListCubes rCubesFull, rListCubes rCubesPart)
	{
		cout << "Make result file\n";
		//sizeof(mName);
		char newName [40];
		strcpy_s(newName, 40,"New_");
		strcat_s(newName, 40, mName);
		ofstream newFile(newName, ios::out);
		newFile << "solid Malay\n";
		
		char buffer[8200];
		for(auto it: rCubesFull)
		{
			strcpy_s(buffer, 8200,it->GenerateStl());
			newFile << buffer;
		}
		/*for (auto it : rCubesPart)
		{
			strcpy_s(buffer, 8200, it->GenerateStl());
			newFile << buffer;
		}*/

		rCubesFull.clear();
		newFile.close();
		cout << "Work end. File \"" << newName << "\" created. Spent time = " << endl;
	}
}