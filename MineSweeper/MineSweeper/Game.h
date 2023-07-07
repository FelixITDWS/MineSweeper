/*********************************************************************
 * File:        Game.h
 * Author:      MIN-FENG CHEN
 * Create Date: July 4, 2023
 * Editor:      MIN-FENG CHEN
 * Update Date: July 7, 2023
 * Description: Game core of MineSweeper
 *********************************************************************/
#pragma once
#include "Board.h"
#include <fstream>
#include <sstream>

 // Game state
enum GAMESTATE
{
	PENDING,
	ONGOING,
	END
};

class MineSweeperCore
{
private:
	Board _gameBoard;					// Game board of MineSweeper
	GAMESTATE _gameState = PENDING;		// Game state of MineSweeper
	bool _hasLoaded = false;			// The state of the game board

public:
	bool exitGame = false;				// The state of the game

public:
	void execute(string input);			// Execute the game by the input command
	void load(string mode);				// Load the board by mode
	void startGame();					// Start the game
	void print(string mode);			// Print the information of mode
	void leftClick(int row, int col);	// Left click to the position
	void rightClick(int row, int col);	// Right click to the position
	void replay();						// Reset the game
	bool loadFile(string fileName);		// Load game board with file
};