#include "Sokoban.h"

Sokoban::Stage Sokoban::MoveUp(Stage& current)
{
	Stage temp(current.GetRow(), current.GetCol());
	CopyStages(temp, current);

	for (int i = 0; i < temp.GetRow(); i++)
	{
		for (int j = 0; j < temp.GetCol(); j++)
		{
			if ((temp.matrix[i][j] == 'R' && temp.matrix[i - 1][j] == 'B' && temp.matrix[i - 2][j] == 'B') ||
				(temp.matrix[i][j] == 'R' && temp.matrix[i - 1][j] == 'B' && temp.matrix[i - 2][j] == 'O') ||
				(temp.matrix[i][j] == 'R' && temp.matrix[i - 1][j] == 'O'))
			{
				temp.isDead = true;
				return temp;
			}
			else if (temp.matrix[i][j] == 'R' && temp.matrix[i - 1][j] == 'B' && temp.matrix[i - 2][j] == ' ')
			{
				temp.matrix[i - 1][j] = 'R';
				temp.matrix[i - 2][j] = 'B';
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

	for (int i = 0; i < temp.GetRow(); i++)
	{
		for (int j = 0; j < temp.GetCol(); j++)
		{
			if ((temp.matrix[i][j] == 'R' && temp.matrix[i + 1][j] == 'B' && temp.matrix[i + 2][j] == 'B') ||
				(temp.matrix[i][j] == 'R' && temp.matrix[i + 1][j] == 'B' && temp.matrix[i + 2][j] == 'O') ||
				(temp.matrix[i][j] == 'R' && temp.matrix[i + 1][j] == 'O'))
			{
				temp.isDead = true;
				return temp;
			}
			else if (temp.matrix[i][j] == 'R' && temp.matrix[i + 1][j] == 'B' && temp.matrix[i + 2][j] == ' ')
			{
				temp.matrix[i + 1][j] = 'R';
				temp.matrix[i + 2][j] = 'B';
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

	for (int i = 0; i < temp.GetRow(); i++)
	{
		for (int j = 0; j < temp.GetCol(); j++)
		{
			if ((temp.matrix[i][j] == 'R' && temp.matrix[i][j + 1] == 'B' && temp.matrix[i][j + 2] == 'B') ||
				(temp.matrix[i][j] == 'R' && temp.matrix[i][j + 2] == 'B' && temp.matrix[i][j + 2] == 'O') ||
				(temp.matrix[i][j] == 'R' && temp.matrix[i][j + 1] == 'O'))
			{
				temp.isDead = true;
				return temp;
			}
			else if (temp.matrix[i][j] == 'R' && temp.matrix[i][j + 1] == 'B' && temp.matrix[i][j + 2] == ' ')
			{
				temp.matrix[i][j + 1] = 'R';
				temp.matrix[i][j + 2] = 'B';
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

	for (int i = 0; i < temp.GetRow(); i++)
	{
		for (int j = 0; j < temp.GetCol(); j++)
		{
			if ((temp.matrix[i][j] == 'R' && temp.matrix[i][j - 1] == 'B' && temp.matrix[i][j - 2] == 'B') ||
				(temp.matrix[i][j] == 'R' && temp.matrix[i][j - 2] == 'B' && temp.matrix[i][j - 2] == 'O') ||
				(temp.matrix[i][j] == 'R' && temp.matrix[i][j - 1] == 'O'))
			{
				temp.isDead = true;
				return temp;
			}
			else if (temp.matrix[i][j] == 'R' && temp.matrix[i][j - 1] == 'B' && temp.matrix[i][j - 2] == ' ')
			{
				temp.matrix[i][j - 1] = 'R';
				temp.matrix[i][j - 2] = 'B';
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