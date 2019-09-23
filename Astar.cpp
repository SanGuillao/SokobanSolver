#include "Sokoban.h"

/***
  * Make sure to update box locations before hand, as it will take the current box locations
  * - will assign an h-value to the Stage passed in
  */
void Sokoban::ManhattanDistance(Stage& current)
{
	//current.SetH(0);
	int temp = 0;
	GetBoxes(current);
	GetRobot(current);
	list<BoxLoc>::iterator bitr;
	list<StorageLoc>::iterator sitr;

	sitr = listOfStorageLoc.begin();

	for (bitr = listOfBoxesLoc.begin(); bitr != listOfBoxesLoc.end(); bitr++)
	{
		if (sitr != listOfStorageLoc.end())
		{
			temp += abs(bitr->row - sitr->row - locationOfRobot.row) + abs(bitr->col - sitr->col - locationOfRobot.col);
			sitr++;
		}
		else
		{
			sitr = listOfStorageLoc.begin();
		}
	}

	current.h = temp;
	//std::cerr << "Final h_value: " << current.h << endl;
}

/***
 * Will change the rhs to be the Stage with the least f value
 * - will also delete that stage from the list that was provided
 */
void Sokoban::FindLeastF(list<Stage>& openList, Stage& temp)
{
	list<Stage>::iterator itr = openList.begin();
	//Stage temp;
	CopyStages(temp, *itr);
	//temp.f = 100;

	for (itr = openList.begin(); itr != openList.end(); itr++)
	{
		//std::cerr << "Value: " << itr->f << endl;
		if (temp.f > itr->f)
		{
			CopyStages(temp, *itr);
			//Display(temp);
			//std::cerr << temp.f << endl;
		}
	}

	//std::cerr << "Final Value: " << temp.f << endl;

	for (itr = openList.begin(); itr != openList.end(); itr++)
	{
		if (CompareStages(temp, *itr))
		{
			//std::cerr << "Hit" << endl;
			itr = openList.erase(itr);
			return;
		}
	}
}

bool Sokoban::AStar(Stage& current, list<Stage>& closedList)
{
	time(&begin);
	std::list<Stage> openList;
	std::list<Stage> succList;
	Stage temp(current);
	int counter = 0;

	closedList.push_back(current);
	GetRobot(current);

	do
	{
		if (!MoveRight(current).isDead)
		{
			succList.push_back(MoveRight(current));
		}

		if (!MoveUp(current).isDead)
		{
			succList.push_back(MoveUp(current));
		}

		if (!MoveLeft(current).isDead)
		{
			succList.push_back(MoveLeft(current));
		}

		if (!MoveDown(current).isDead)
		{
			succList.push_back(MoveDown(current));
		}

		for (list<Stage>::iterator itr = succList.begin(); itr != succList.end(); itr++)
		{
			// assign current stage a h-value
			GetBoxes(*itr);
			ManhattanDistance(*itr);

			//itr->g = current.g + 1;
			itr->g = 0;
			itr->f = itr->g + itr->h;

			//std::cerr << itr->f << endl;
		}

		while (!succList.empty())
		{
			openList.push_back(succList.front());
			succList.pop_front();
		}

		//Display(current);
		//cout << queueStages.size() << endl;
		if (openList.size() != 0)
		{
			FindLeastF(openList, current);
			//CopyStages(current, openList.front());
			//openList.pop_front();

			while (CompareStages(current, closedList) && openList.size() != 0)
			{
				FindLeastF(openList, current);
				//CopyStages(current, openList.front());
				//openList.pop_front();
				PutSBack(current);
				//Display(current);
			}

			PutSBack(current);
			closedList.push_back(current);
			GetRobot(current);
		}
		else
		{
			cout << "A* search could not find a solution. Exiting now..." << endl;
			return false;
		}

		counter++;

	} while (!CheckIfEnd(current));

	time(&end);
	cout << "A* has found a solution. Outputting to AStar_Output.txt now..." << endl;
	OutputList(closedList, "AStar");
	while (!openList.empty())
	{
		openList.pop_front();
	}
	while (!closedList.empty())
	{
		closedList.pop_front();
	}
	return true;
}