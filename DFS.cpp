#include "Sokoban.h"

bool Sokoban::DFS(Stage& current, list<Stage>& closedList)
{
	time(&begin);
	std::stack<Stage> stackStages;
	int counter = 0;

	closedList.push_back(current);
	GetRobot(current);

	do
	{
		if (!MoveRight(current).isDead)
		{
			stackStages.push(MoveRight(current));
		}

		if (!MoveUp(current).isDead)
		{
			stackStages.push(MoveUp(current));
		}

		if (!MoveLeft(current).isDead)
		{
			stackStages.push(MoveLeft(current));
		}

		if (!MoveDown(current).isDead)
		{
			stackStages.push(MoveDown(current));
		}

		//Display(current);
		//cout << queueStages.size() << endl;
		if (stackStages.size() != 0)
		{
			CopyStages(current, stackStages.top());
			stackStages.pop();

			while (CompareStages(current, closedList) && stackStages.size() != 0)
			{
				CopyStages(current, stackStages.top());
				stackStages.pop();
				PutSBack(current);
				//Display(current);
			}

			PutSBack(current);
			closedList.push_back(current);
			GetRobot(current);
		}
		else
		{
			cout << "DFS could not find a solution. Exiting now..." << endl;
			return false;
		}

		counter++;

	} while (!CheckIfEnd(current));

	time(&end);
	cout << "DFS has found a solution. Outputting to DFS_Output.txt now..." << endl;
	OutputList(closedList, "DFS");
	while (!stackStages.empty())
	{
		stackStages.pop();
	}
	while (!closedList.empty())
	{
		closedList.pop_front();
	}
	return true;
}