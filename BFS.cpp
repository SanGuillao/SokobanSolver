#include "Sokoban.h"

bool Sokoban::BFS(Stage& current, list<Stage>& closedList)
{
	std::queue<Stage> queueStages;
	bool isDone = false;

	closedList.push_back(current);

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

		CopyStages(current, queueStages.front());
		closedList.push_back(current);
		queueStages.pop();
		isDone = true;

	} while (!isDone);
	
	return true;
}