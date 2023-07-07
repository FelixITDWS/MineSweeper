/*********************************************************************
 * File:        Board.cpp
 * Author:      MIN-FENG CHEN
 * Create Date: July 4, 2023
 * Editor:      MIN-FENG CHEN
 * Update Date: July 7, 2023
 * Description: Board of MineSweeper
 *********************************************************************/
#include "Board.h"

 // Constant
const char BLANK = 'O';
const char BOMB = 'X';
const char FLAG = '!';
const char UNKNOWN = '#';
const char QEUSTION = '?';
const int INTBOMB = 9;

// Intent: Default constructor
// Pre: None
// Post: None
Board::Board()
{
	_length = 10;
	_width = 10;
	_bombAmount = 10;
	_bombRate = -1;
}

// Intent: Create a board with the size and mine amount
// Pre: All arg must be greater than zero
// Post: None
Board::Board(int w, int l, int amount)
{
	_length = l;
	_width = w;
	_bombRate = -1;
	_bombAmount = amount;
}

// Intent: Create a board with the size and mine rate
// Pre: All arg must be greater than zero
// Post : None
Board::Board(int w, int l, double rate)
{
	_length = l;
	_width = w;
	_bombAmount = 0;
	_bombRate = rate;
}

// Intent: Create a board with the size and input board
// Pre: All arg must be greater than zero and nonempty
// Post: None
Board::Board(int w, int l, vector<vector<char>> inputBoard)
{
	_width = w;
	_length = l;
	_bombAmount = 0;
	_bombRate = -1;
	init();

	// Create the board with inputBoard
	for (int i = 0; i < inputBoard.size(); i++)
	{
		for (int j = 0; j < inputBoard[i].size(); j++)
		{
			_setBoard[i][j] = inputBoard[i][j];
			if (_setBoard[i][j] == BOMB)
			{
				++_bombAmount;
			}
		}
	}
}

// Intent: Initialize the game board
// Pre: None
// Post: None
void Board::init()
{
	// Initialize the game board
	for (int i = 0; i < _width; i++)
	{
		_setBoard.push_back({});
		_ansBoard.push_back({});
		_gameBoard.push_back({});
		for (int j = 0; j < _length; j++)
		{
			_setBoard[i].push_back(BLANK);
			_ansBoard[i].push_back(0);
			_gameBoard[i].push_back(UNKNOWN);
		}
	}

	// Set bomb by rate
	srand(time(NULL));
	if (_bombRate != -1)
	{
		for (int i = 0; i < _width; i++)
		{
			for (int j = 0; j < _length; j++)
			{
				if (rand() % 100 < _bombRate * 100)
				{
					_setBoard[i][j] = BOMB;
					++_bombAmount;
				}
			}
		}
	}
	// Set bomb by amount
	else
	{
		int remainBomb = _bombAmount;
		while (remainBomb >= 0)
		{
			int row = rand() % _width, col = rand() % _length;
			if (_setBoard[row][col] != BOMB)
			{
				_setBoard[row][col] = BOMB;
				--remainBomb;
			}
		}
	}
}

// Intent: Create the board to show the number of mine in a position
// Pre: None
// Post: None
void Board::genAnsBoard()
{
	for (int row = 0; row < _width; row++)
	{
		for (int col = 0; col < _length; col++)
		{
			if (_setBoard[row][col] == BOMB)
			{
				_ansBoard[row][col] = INTBOMB;
				continue;
			}

			// Travel the Jiugongge to check the amount of mine near the position
			for (int i = row - 1; i <= row + 1; i++)
			{
				for (int j = col - 1; j <= col + 1; j++)
				{
					if (!isPositionValid(i, j))
					{
						continue;
					}

					if (i == row && j == col)
					{
						continue;
					}

					if (isBomb(i, j))
					{
						++_ansBoard[row][col];
					}
				}
			}
		}
	}

	// Initialize the game data
	_openBlankCount = 0;
	_remainBlankCount = _length * _width - _bombAmount;
	_flagCount = 0;
}

// Intent: Open the blank of the position
// Pre: row and col should be positive
// Post: Return whether the action is valid
bool Board::openBlank(int row, int col)
{
	// Check whether the position is in the range
	if (!isPositionValid(row, col))
	{
		return false;
	}

	// Check the blank is able to be opend
	if (_gameBoard[row][col] != UNKNOWN && _gameBoard[row][col] != QEUSTION)
	{
		return false;
	}

	// Trig the bomb
	if (isBomb(row, col))
	{
		_gameBoard[row][col] = BOMB;
		return true;
	}

	// Update board
	_gameBoard[row][col] = _ansBoard[row][col] + '0';
	++_openBlankCount;
	--_remainBlankCount;

	// Diffuse when there is no any bomb near the position
	if (_ansBoard[row][col] == 0)
	{
		for (int delRow = -1; delRow <= 1; delRow++)
		{
			for (int delCol = -1; delCol <= 1; delCol++)
			{
				if (delRow == 0 && delCol == 0)
				{
					continue;
				}
				openBlank(row + delRow, col + delCol);
			}
		}
	}

	return true;
}

// Intent: Set the mark to the position
// Pre: row and col should be positive
// Post: Return whether the action is valid
bool Board::setMark(int row, int col)
{
	// Check whether the position is in the range
	if (!isPositionValid(row, col))
	{
		return false;
	}

	// Set the position to flag if it is not opend
	if (_gameBoard[row][col] == UNKNOWN)
	{
		_gameBoard[row][col] = FLAG;
		++_flagCount;
	}
	// Set the position to question mark if it is flag
	else if (_gameBoard[row][col] == FLAG)
	{
		_gameBoard[row][col] = QEUSTION;
		--_flagCount;
	}
	// Other condition is invalid
	else
	{
		return false;
	}

	return true;
}

// Intent: Check whether the position is in the range
// Pre: row and col should be positive
// Post: Return whether the position is in the range
bool Board::isPositionValid(int row, int col)
{
	if (row < 0 || row >= _width || col < 0 || col >= _length)
	{
		return false;
	}
	return true;
}

// Intent: Get the total bomb amount
// Pre: None
// Post: Return the mine amount
int Board::getBombCount() const
{
	return _bombAmount;
}

// Intent: Get the opend blank amount
// Pre: None
// Post: Return the opend blank count
int Board::getOpenBlankCount() const
{
	return _openBlankCount;
}

// Intent: Get the remaining blank amount
// Pre: None
// Post: Return the remain blank count
int Board::getRemainBlankCount() const
{
	return _remainBlankCount;
}

// Intent: Get the total set flag
// Pre: None
// Post: Return the set flag count
int Board::getFlagCount() const
{
	return _flagCount;
}

// Intent: Show the answer board
// Pre: None
// Post: Print the ansBoard
void Board::showAns() const
{
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _length; j++)
		{
			cout << _ansBoard[i][j];
		}
		cout << '\n';
	}
}

// Intent: Show the game board
// Pre: None
// Post: Print the gameBoard
void Board::showBoard() const
{
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _length; j++)
		{
			cout << _gameBoard[i][j];
		}
		cout << '\n';
	}
}

// Intent: Check whether the position is bomb
// Pre: row and col must be in the range
// Post: Return whether the blank is bomb
bool Board::isBomb(int row, int col)
{
	if (_setBoard[row][col] == BOMB)
	{
		return true;
	}

	return false;
}