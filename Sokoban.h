#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <queue>
#include <stack>

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
			int row, col;
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
			void SetIsDead(bool d) { this->isDead = d; }
			const bool GetIsDead() { return this->isDead; }
		};
		struct StorageLoc
		{
			int row, col;
				StorageLoc();
				StorageLoc(int r, int c);
		};
		struct RobotLoc
		{
			int row, col;
				RobotLoc();
				RobotLoc(int r, int c);
		};

		list<StorageLoc> listOfStorageLoc;
		RobotLoc locationOfRobot;

	public:
		bool Initialize(Stage&);
		bool GetDimensionMatrix(std::ifstream& inFile, Stage&);
		bool OutputList(list<Stage>&);

		const void Display(Stage&);
		const void Display(list<Stage>&);
		void CopyStages(Stage&, Stage&);
		bool CompareStages(Stage&, Stage&);
		bool CompareStages(Stage&, list<Stage>&);

		Stage MoveUp(Stage&);
		Stage MoveDown(Stage&);
		Stage MoveRight(Stage&);
		Stage MoveLeft(Stage&);
		bool IsStageDead(Stage&);
		void PutSBack(Stage&);

		void GetRobot(Stage&);

		bool BFS(Stage&, list<Stage>&);
		bool DFS(Stage&);

		bool CheckIfEnd(Stage&);
		bool Control();
};