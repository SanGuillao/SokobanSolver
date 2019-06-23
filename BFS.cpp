#include "Sokoban.h"

bool Sokoban::BFS(Stage& current, list<Stage>& closedList)
{
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

			while (CompareStages(current, closedList))
			{
				CopyStages(current, queueStages.front());
				queueStages.pop();
			}
			
			closedList.push_back(current);
			GetRobot(current);
		}
		
	} while (!CheckIfEnd(current));
	
	if (CheckIfEnd(current))
	{
		OutputList(closedList);
		return true;
	}
	//Display(closedList);
	cout << "Could not find a solution" << endl;
	return false;
}