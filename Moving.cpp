#include "Sokoban.h"

bool Sokoban::IsStageDead(Stage& temp)
{
	for (int i = 0; i < temp.GetRow(); i++)
	{
		for (int j = 0; j < temp.GetCol(); j++)
		{
			if (temp.matrix[i][j] == 'B')
			{
				for (list<StorageLoc>::iterator itr = listOfStorageLoc.begin(); itr != listOfStorageLoc.end(); itr++)
				{
					if (i == itr->row && j == itr->col)
						return false;
				}
			}
			// find box, check above and to the right, to see if in a corner
			if (temp.matrix[i][j] == 'B' && temp.matrix[i - 1][j] == 'O' && temp.matrix[i][j + 1] == 'O')
				return true;
			// find box, check above and to the left, to see if in a corner
			if (temp.matrix[i][j] == 'B' && temp.matrix[i - 1][j] == 'O' && temp.matrix[i][j - 1] == 'O')
				return true;
			// find box, check below and to the right, to see if in a corner
			if (temp.matrix[i][j] == 'B' && temp.matrix[i + 1][j] == 'O' && temp.matrix[i][j + 1] == 'O')
				return true;
			// find box, check below and to the left, to see if in a corner
			if (temp.matrix[i][j] == 'B' && temp.matrix[i + 1][j] == 'O' && temp.matrix[i][j - 1] == 'O')
				return true;
		}
	}

	return false;
}

Sokoban::Stage Sokoban::MoveUp(Stage& current)
{
	Stage temp(current.GetRow(), current.GetCol());
	CopyStages(temp, current);

	if (IsStageDead(temp))
	{
		temp.SetIsDead(true);
		return temp;
	}

	if ((temp.matrix[locationOfRobot.row - 1][locationOfRobot.col] == 'O') ||
		(temp.matrix[locationOfRobot.row - 1][locationOfRobot.col] == 'B' && temp.matrix[locationOfRobot.row - 2][locationOfRobot.col] == 'B') ||
		(temp.matrix[locationOfRobot.row - 1][locationOfRobot.col] == 'B' && temp.matrix[locationOfRobot.row - 2][locationOfRobot.col] == 'O'))
	{
		temp.SetIsDead(true);
		return temp;
	}

	for (int i = 0; i < temp.GetRow(); i++)
	{
		for (int j = 0; j < temp.GetCol(); j++)
		{
			if (temp.matrix[i][j] == 'R' && temp.matrix[i - 1][j] == 'B' && temp.matrix[i - 2][j] == ' ')
			{
				temp.matrix[i - 1][j] = 'R';
				temp.matrix[i - 2][j] = 'B';
				temp.matrix[i][j] = ' ';
				return temp;
			}
			else if (temp.matrix[i][j] == 'R' && temp.matrix[i - 1][j] == 'B' && temp.matrix[i - 2][j] == 'S')
			{
				temp.matrix[i - 1][j] = 'R';
				temp.matrix[i - 2][j] = 'B';
				temp.matrix[i][j] = ' ';
				return temp;
			}
			else if (temp.matrix[i][j] == 'R' && temp.matrix[i - 1][j] == 'S')
			{
				temp.matrix[i - 1][j] = 'R';
				temp.matrix[i][j] = ' ';
				return temp;
			}
			else if (temp.matrix[i][j] == 'R' && temp.matrix[i - 1][j] == ' ')
			{
				temp.matrix[i - 1][j] = 'R';
				temp.matrix[i][j] = ' ';
				return temp;
			}
		}
	}

	return temp;
}

Sokoban::Stage Sokoban::MoveDown(Stage& current)
{
	Stage temp(current.GetRow(), current.GetCol());
	CopyStages(temp, current);

	if (IsStageDead(temp))
	{
		temp.SetIsDead(true);
		return temp;
	}

	if ((temp.matrix[locationOfRobot.row + 1][locationOfRobot.col] == 'O') ||
		(temp.matrix[locationOfRobot.row + 1][locationOfRobot.col] == 'B' && temp.matrix[locationOfRobot.row + 2][locationOfRobot.col] == 'B') ||
		(temp.matrix[locationOfRobot.row + 1][locationOfRobot.col] == 'B' && temp.matrix[locationOfRobot.row + 2][locationOfRobot.col] == 'O'))
	{
		temp.SetIsDead(true);
		return temp;
	}

	for (int i = 0; i < temp.GetRow(); i++)
	{
		for (int j = 0; j < temp.GetCol(); j++)
		{
			if (temp.matrix[i][j] == 'R' && temp.matrix[i + 1][j] == 'B' && temp.matrix[i + 2][j] == ' ')
			{
				temp.matrix[i + 1][j] = 'R';
				temp.matrix[i + 2][j] = 'B';
				temp.matrix[i][j] = ' ';
				return temp;
			}
			else if (temp.matrix[i][j] == 'R' && temp.matrix[i + 1][j] == 'B' && temp.matrix[i + 2][j] == 'S')
			{
				temp.matrix[i + 1][j] = 'R';
				temp.matrix[i + 2][j] = 'B';
				temp.matrix[i][j] = ' ';
				return temp;
			}
			else if (temp.matrix[i][j] == 'R' && temp.matrix[i + 1][j] == 'S')
			{
				temp.matrix[i + 1][j] = 'R';
				temp.matrix[i][j] = ' ';
				return temp;
			}
			else if (temp.matrix[i][j] == 'R' && temp.matrix[i + 1][j] == ' ')
			{
				temp.matrix[i + 1][j] = 'R';
				temp.matrix[i][j] = ' ';
				return temp;
			}
		}
	}

	return temp;
}

Sokoban::Stage Sokoban::MoveRight(Stage& current)
{
	Stage temp(current.GetRow(), current.GetCol());
	CopyStages(temp, current);

	if (IsStageDead(temp))
	{
		temp.SetIsDead(true);
		return temp;
	}

	if ((temp.matrix[locationOfRobot.row][locationOfRobot.col + 1] == 'O') ||
		(temp.matrix[locationOfRobot.row][locationOfRobot.col + 1] == 'B' && temp.matrix[locationOfRobot.row][locationOfRobot.col + 2] == 'B') ||
		(temp.matrix[locationOfRobot.row][locationOfRobot.col + 1] == 'B' && temp.matrix[locationOfRobot.row][locationOfRobot.col + 2] == 'O'))
	{
		temp.SetIsDead(true);
		return temp;
	}

	for (int i = 0; i < temp.GetRow(); i++)
	{
		for (int j = 0; j < temp.GetCol(); j++)
		{
			if (temp.matrix[i][j] == 'R' && temp.matrix[i][j + 1] == 'B' && temp.matrix[i][j + 2] == ' ')
			{
				temp.matrix[i][j + 1] = 'R';
				temp.matrix[i][j + 2] = 'B';
				temp.matrix[i][j] = ' ';
				return temp;
			}
			else if (temp.matrix[i][j] == 'R' && temp.matrix[i][j + 1] == 'B' && temp.matrix[i][j + 2] == 'S')
			{
				temp.matrix[i][j + 1] = 'R';
				temp.matrix[i][j + 2] = 'B';
				temp.matrix[i][j] = ' ';
				return temp;
			}
			else if (temp.matrix[i][j] == 'R' && temp.matrix[i][j + 1] == 'S')
			{
				temp.matrix[i][j + 1] = 'R';
				temp.matrix[i][j] = ' ';
				return temp;
			}
			else if (temp.matrix[i][j] == 'R' && temp.matrix[i][j + 1] == ' ')
			{
				temp.matrix[i][j + 1] = 'R';
				temp.matrix[i][j] = ' ';
				return temp;
			}
		}
	}

	return temp;
}

Sokoban::Stage Sokoban::MoveLeft(Stage& current)
{
	Stage temp(current.GetRow(), current.GetCol());
	CopyStages(temp, current);

	if (IsStageDead(temp))
	{
		temp.SetIsDead(true);
		return temp;
	}

	if ((temp.matrix[locationOfRobot.row][locationOfRobot.col - 1] == 'O') ||
		(temp.matrix[locationOfRobot.row][locationOfRobot.col - 1] == 'B' && temp.matrix[locationOfRobot.row][locationOfRobot.col - 2] == 'B') ||
		(temp.matrix[locationOfRobot.row][locationOfRobot.col - 1] == 'B' && temp.matrix[locationOfRobot.row][locationOfRobot.col - 2] == 'O'))
	{
		temp.SetIsDead(true);
		return temp;
	}

	for (int i = 0; i < temp.GetRow(); i++)
	{
		for (int j = 0; j < temp.GetCol(); j++)
		{
			if (temp.matrix[i][j] == 'R' && temp.matrix[i][j - 1] == 'B' && temp.matrix[i][j - 2] == ' ')
			{
				temp.matrix[i][j - 1] = 'R';
				temp.matrix[i][j - 2] = 'B';
				temp.matrix[i][j] = ' ';			
				return temp;
			}
			else if (temp.matrix[i][j] == 'R' && temp.matrix[i][j - 1] == 'B' && temp.matrix[i][j - 2] == 'S')
			{
				temp.matrix[i][j - 1] = 'R';
				temp.matrix[i][j - 2] = 'B';
				temp.matrix[i][j] = ' ';
				return temp;
			}
			else if (temp.matrix[i][j] == 'R' && temp.matrix[i][j - 1] == 'S')
			{
				temp.matrix[i][j - 1] = 'R';
				temp.matrix[i][j] = ' ';
				return temp;
			}
			else if (temp.matrix[i][j] == 'R' && temp.matrix[i][j - 1] == ' ')
			{
				temp.matrix[i][j - 1] = 'R';
				temp.matrix[i][j] = ' ';
				return temp;
			}
		}
	}

	return temp;
}