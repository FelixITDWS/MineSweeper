/*********************************************************************
 * File:        Board.h
 * Author:      MIN-FENG CHEN
 * Create Date: July 4, 2023
 * Editor:      MIN-FENG CHEN
 * Update Date: July 7, 2023
 * Description: Board of MineSweeper
 *********************************************************************/
#pragma once
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

class Board
{
private:
	int _length;						// Length of game board
	int _width;							// Width of game board
	int _bombAmount;					// The amount of the bomb
	double _bombRate;					// The rate of bomb
	int _openBlankCount;				// The amount of the opend blank 
	int _remainBlankCount;				// The remaining amount of the blank is not opened
	int _flagCount;						// The amount of the flag is set
	vector<vector<char>> _setBoard;		// Origin set board
	vector<vector<int>> _ansBoard;		// Answer
	vector<vector<char>> _gameBoard;	// The gameboard to show for player

public:
	Board();							// Default constructor
	Board(int w, int l, int amount);	// Create a board with size and bomb amount
	Board(int w, int l, double rate);	// Create a board with size and bomb rate
	Board(int w, int l, vector<vector<char>> inputBoard);	// Create a board with size and board

	void init();							// Initialize the game board
	void genAnsBoard();						// Generate a answer board
	bool openBlank(int row, int col);		// Open the blank of the board with specified position
	bool setMark(int row, int col);			// Set the mark to the specified position
	bool isPositionValid(int row, int col);	// Check whether the position is valid

	int getBombCount() const;				// Get the amount of bomb
	int getOpenBlankCount() const;			// Get the amount of blank is opened
	int getRemainBlankCount() const;		// Get the amount of blank is not opened
	int getFlagCount() const;				// Get the amount of flag is set
	void showBoard() const;					// Show the current game board
	void showAns() const;					// Show the answer board
	bool isBomb(int row, int col);			// Check whether the position is bomb
};