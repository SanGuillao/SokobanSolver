#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <queue>
#include <stack>
#include <ctime>
#include <stdlib.h>

using std::cout;
using std::endl;
using std::list;
using std::iterator;
using std::ios;

class Sokoban
{
	private:
		struct Stage
		{
			int row, col, h, g, f;
			bool isDead;
			char** matrix;

				Stage();
				Stage(int r, int c);
				Stage(const Stage& obj);
				~Stage();

			void SetRow(int r) { this->row = r; }
			const int GetRow() { return this->row; }
			void SetCol(int c) { this->col = c; }
			const int GetCol() { return this->col; }
			void SetH(int h2) { this->h = h2; }
			const int GetH() { return this->h; }
			void SetG(int g2) { this->g = g2; }
			const int GetG() { return this->g; }
			void SetF(int f2) { this->f = f2; }
			const int GetF() { return this->f; }
			void SetIsDead(bool d) { this->isDead = d; }
			const bool GetIsDead() { return this->isDead; }
		};
		struct StorageLoc
		{
			int row, col;
				StorageLoc();
				StorageLoc(int r, int c);
		};
		struct BoxLoc
		{
			int row, col;
			BoxLoc();
			BoxLoc(int r, int c);
		};
		struct RobotLoc
		{
			int row, col;
				RobotLoc();
				RobotLoc(int r, int c);
		};
		
		// list for holding the locations of the storages, that way we can immediataly find the location of all the storage points
		list<StorageLoc> listOfStorageLoc;
		// list for holding the locations of the boxes
		list<BoxLoc> listOfBoxesLoc;
		// location of the robot, that way we can always find the Robot
		RobotLoc locationOfRobot;
		// these two will hold the beginning and end time of the selected search method
		time_t begin, end;

	public:
		bool Initialize(Stage&);
		bool LoadFile(Stage&);
		bool GetDimensionMatrix(std::ifstream& inFile, Stage&);
		bool OutputList(list<Stage>&, std::string);

		const void Display(Stage&);
		const void Display(list<Stage>&);
		void CopyStages(Stage&, Stage&);
		bool CompareStages(Stage&, Stage&);
		bool CompareStages(Stage&, list<Stage>&);

		void FindLeastF(list<Stage>&, Stage&);

		Stage MoveUp(Stage&);
		Stage MoveDown(Stage&);
		Stage MoveRight(Stage&);
		Stage MoveLeft(Stage&);
		bool IsStageDead(Stage&);
		void PutSBack(Stage&);

		void GetRobot(Stage&);
		void GetBoxes(Stage&);

		void ManhattanDistance(Stage&);

		bool BFS(Stage&, list<Stage>&);
		bool DFS(Stage&, list<Stage>&);
		bool AStar(Stage&, list<Stage>&);

		bool CheckIfEnd(Stage&);
		bool Control();
};