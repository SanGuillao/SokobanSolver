#include "Sokoban.h"

Sokoban::Stage::Stage()
{
	this->row = 0;
	this->col = 0;
	this->isDead = false;
}

Sokoban::Stage::Stage(int r, int c)
{
	this->row = r;
	this->col = c;
	this->isDead = false;
	this->matrix = new char *[this->row];
	for (int i = 0; i < this->row; i++)
	{
		this->matrix[i] = new char[this->col];
		for (int j = 0; j < this->col; j++)
		{
			this->matrix[i][j] = ' ';
		}
	}
}

Sokoban::Stage::Stage(const Stage& obj)
{
	this->row = obj.row;
	this->col = obj.col;
	this->isDead = obj.isDead;
	this->matrix = new char *[this->row];
	for (int i = 0; i < this->row; i++)
	{
		this->matrix[i] = new char [this->col];
		for (int j = 0; j < this->col; j++)
		{
			this->matrix[i][j] = obj.matrix[i][j];
		}
	}
}

Sokoban::Stage::~Stage()
{
	for (int i = 0; i < this->row; i++)
	{
		// delete individual row from matrix
		delete[] this->matrix[i];
	}

	// delete matrix as a whole
	delete[] this->matrix;
	//std::cerr << "Deleted" << endl;
}

Sokoban::StorageLoc::StorageLoc()
{
	this->row = -1;
	this->col = -1;
}

Sokoban::StorageLoc::StorageLoc(int r, int c)
{
	this->row = r;
	this->col = c;
}

Sokoban::RobotLoc::RobotLoc()
{
	this->row = -1;
	this->col = -1;
}

Sokoban::RobotLoc::RobotLoc(int r, int c)
{
	this->row = r;
	this->col = c;
}

void Sokoban::GetRobot(Stage& current)
{
	for (int i = 0; i < current.GetRow(); i++)
	{
		for (int j = 0; j < current.GetCol(); j++)
		{
			if (current.matrix[i][j] == 'R')
			{
				locationOfRobot.row = i;
				locationOfRobot.col = j;
			}
		}
	}
}

bool Sokoban::GetDimensionMatrix(std::ifstream& inFile, Stage& current)
{
	int r = 0, c = 0;
	std::string temp;
	std::getline(inFile, temp);
	r++;
	c = temp.length();
	while (getline(inFile, temp))
		r++;

	current.SetRow(r);
	current.SetCol(c);

	inFile.clear();
	inFile.seekg(0, ios::beg);

	//std::cerr << r << " : " << c << endl;
	return true;
}

bool Sokoban::Initialize(Stage& current)
{
	std::ifstream inFile;
	int r = 0 , c = 0;
	inFile.open("Puzzles.txt", std::ifstream::in);

	if (!inFile)
	{
		cout << "Could not open Puzzles.txt file, please check to make sure you have the file with the program" << endl;
		return false;
	}

	GetDimensionMatrix(inFile, current);

	//std::cerr << current.GetRow() << " : " << current.GetCol() << endl;

	current.matrix = new char *[current.GetRow()];
	for (int i = 0; i < current.GetRow(); i++)
	{
		current.matrix[i] = new char [current.GetCol()];
		for (int j = 0; j < current.GetCol(); j++)
		{
			current.matrix[i][j] = inFile.get();
			if (current.matrix[i][j] == 'S')
			{
				listOfStorageLoc.push_back(StorageLoc(i, j));
			}
		}
		inFile.ignore();
	}

	//Display(current);

	return true;
}

bool Sokoban::OutputList(list<Stage>& closedList, std::string fileName)
{
	double difference = 0;
	std::ofstream outFile;
	fileName += "_Output.txt";
	outFile.open(fileName.c_str(), std::ofstream::out);

	if (!outFile)
	{
		cout << "Could not create/open BFS_Outfile.txt file" << endl;
		return false;
	}

	for (list<Stage>::iterator itr = closedList.begin(); itr != closedList.end(); itr++)
	{
		for (int i = 0; i < itr->GetRow(); i++)
		{
			for (int j = 0; j < itr->GetCol(); j++)
			{
				outFile << itr->matrix[i][j];
			}
			outFile << endl;
		}
	}

	difference = difftime(end, begin);
	outFile << "\nThis search took: " << difference << " secs" << endl;

	return true;
}

const void Sokoban::Display(Stage& current)
{
	for (int i = 0; i < current.GetRow(); i++)
	{
		for (int j = 0; j < current.GetCol(); j++)
		{
			cout << current.matrix[i][j];
		}
		cout << endl;
	}
}

const void Sokoban::Display(list<Stage>& closeList)
{
	for (list<Stage>::iterator itr = closeList.begin(); itr != closeList.end(); itr++)
	{
		Display(*itr);
	}
}

void Sokoban::PutSBack(Stage& current)
{
	for (list<StorageLoc>::iterator itr = listOfStorageLoc.begin(); itr != listOfStorageLoc.end(); itr++)
	{
		if (current.matrix[itr->row][itr->col] == ' ')
			current.matrix[itr->row][itr->col] = 'S';
	}
}

void Sokoban::CopyStages(Stage& lhs, Stage& rhs)
{
	lhs.SetRow(rhs.GetRow());
	lhs.SetCol(rhs.GetCol());
	lhs.SetIsDead(rhs.GetIsDead());
	for (int i = 0; i < lhs.GetRow(); i++)
	{
		for (int j = 0; j < lhs.GetCol(); j++)
		{
			lhs.matrix[i][j] = rhs.matrix[i][j];
		}
	}
}

bool Sokoban::CompareStages(Stage& lhs, Stage& rhs)
{
	for (int i = 0; i < rhs.GetRow(); i++)
	{
		for (int j = 0; j < rhs.GetCol(); j++)
		{
			if (lhs.matrix[i][j] != rhs.matrix[i][j])
				return false;
		}
	}
	return true;
}

bool Sokoban::CompareStages(Stage& current, list<Stage>& closedList)
{
	for (list<Stage>::iterator itr =closedList.begin(); itr != closedList.end(); itr++)
	{
		if (CompareStages(current, *itr))
			return true;
	}
	return false;
}

bool Sokoban::CheckIfEnd(Stage& current)
{
	for (list<StorageLoc>::iterator itr = listOfStorageLoc.begin(); itr != listOfStorageLoc.end(); itr++)
	{
		if (current.matrix[itr->row][itr->col] != 'B')
		{
			return false;
		}
	}
	return true;
}

bool Sokoban::Control()
{
	Stage new1;
	list<Stage> closedList;
	int user = -1;

	do
	{
		cout << "1. Load puzzle from file" << endl;
		cout << "2. Solve puzzle using Breadth First Search" << endl;
		cout << "3. Sovle puzzle using Depth First Search" << endl;
		cout << "0. Quit" << endl;
		std::cin >> user;
		
		if (user == 1)
		{
			cout << "Coming soon.." << endl;
		}
		else if (user == 2)
		{
			Initialize(new1);
			BFS(new1, closedList);
		}
		else if (user == 3)
		{
			Initialize(new1);
			DFS(new1, closedList);
		}
		else if (user == 0)
		{
			cout << "Solver will now quit.." << endl;
			return true;
		}
	} while (user >= 0 && user < 4);
	
	
	//Initialize(new1);
	//BFS(new1, closedList);
	//DFS(new1, closedList);

	//Display(closedList);
	
	return true;
}