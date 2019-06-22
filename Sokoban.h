#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <list>

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
		char** matrix;

		Stage();
		Stage(int r, int c);
		Stage(const Stage& obj);
		~Stage();

		void SetRow(int r) { this->row = r; }
		const int GetRow() { return this->row; }
		void SetCol(int c) { this->col = c; }
		const int GetCol() { return this->col; }
	};
public:
	bool Initialize(Stage&);
	bool GetDimensionMatrix(std::ifstream& inFile, Stage&);

	const void Display(Stage&);
	void CopyStages(Stage&, Stage&);

	Stage MoveUp(Stage&);
	Stage MoveDown(Stage&);
	Stage MoveRight(Stage&);
	Stage MoveLeft(Stage&);

	bool Control();
};