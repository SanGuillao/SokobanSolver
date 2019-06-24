#include "Sokoban.h"

bool Sokoban::BFS(Stage& current, list<Stage>& closedList)
{
	time(&begin);
	std::queue<Stage> queueStages;
	int counter = 0;

	closedList.push_back(current);
	GetRobot(current);

	do
	{
		if (!MoveRight(current).isDead)
		{
			queueStages.push(MoveRight(current));
		}

		if (!MoveUp(current).isDead)
		{
			queueStages.push(MoveUp(current));
		}

		if (!MoveLeft(current).isDead)
		{
			queueStages.push(MoveLeft(current));
		}

		if (!MoveDown(current).isDead)
		{
			queueStages.push(MoveDown(current));
		}

		//Display(current);
		//cout << queueStages.size() << endl;
		if (queueStages.size() != 0)
		{
			CopyStages(current, queueStages.front());
			queueStages.pop();

			while (CompareStages(current, closedList) && queueStages.size() != 0)
			{
				CopyStages(current, queueStages.front());
				queueStages.pop();
				PutSBack(current);
			}
			
			PutSBack(current);
			closedList.push_back(current);
			GetRobot(current);
		}
		else
		{
			cout << "BFS could not find a solution. Exiting now..." << endl;
			return false;
		}


	} while (!CheckIfEnd(current));

	time(&end);
	cout << "BFS has found a solution. Outputting to BFS_Output.txt now..." << endl;
	OutputList(closedList, "BFS");
	while (!queueStages.empty())
	{
		queueStages.pop();
	}
	while (!closedList.empty())
	{
		closedList.pop_front();
	}
	return true;
}