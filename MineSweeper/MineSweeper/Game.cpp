/*********************************************************************
 * File:        Game.cpp
 * Author:      MIN-FENG CHEN
 * Create Date: July 4, 2023
 * Editor:      MIN-FENG CHEN
 * Update Date: July 7, 2023
 * Description: Game Manager
 *********************************************************************/
#include "Game.h"

string strGameStat[3] = { "Standby", "Playing", "GameOver" };	// Game state to be printed

// Intent: Execute the game
// Pre: None
// Post: None
void MineSweeperCore::execute(string input)
{
	stringstream ss(input);
	string cmd, mode;

	// Split the command and the content of mode
	getline(ss, cmd, ' ');
	getline(ss, mode, '\n');

	// Command: Load
	if (cmd == "Load")
	{
		// Wrong state
		if (_gameState != PENDING)
		{
			cout << "<" << input << ">: Failed\n";
			return;
		}

		// Load operation
		load(mode);
	}

	// Command: StartGame
	else if (cmd == "StartGame")
	{
		// Wrong state
		if (_gameState != PENDING)
		{
			cout << "<StartGame>: Failed\n";
			return;
		}

		// StartGame operation
		startGame();
	}

	// Command: Print
	else if (cmd == "Print")
	{
		// Print operation
		print(mode);
	}

	// Command: LeftClick
	else if (cmd == "LeftClick")
	{
		// Split the content of mode to row and col
		string strRow, strCol;
		ss = stringstream(mode);
		getline(ss, strRow, ' ');
		getline(ss, strCol, ' ');
		int row = stoi(strRow), col = stoi(strCol);

		// LeftClick operation
		leftClick(row, col);
	}

	// Command: RightClick
	else if (cmd == "RightClick")
	{
		// Split the content of mode to row and col
		string strRow, strCol;
		ss = stringstream(mode);
		getline(ss, strRow, ' ');
		getline(ss, strCol, ' ');
		int row = stoi(strRow), col = stoi(strCol);

		// RightClick operation
		rightClick(row, col);
	}

	// Command: Replay
	else if (cmd == "Replay")
	{
		// Replay operation
		replay();
	}

	// Command: Quit
	else if (cmd == "Quit")
	{
		// Wrong state
		if (_gameState != END)
		{
			cout << "<Quit>: Failed\n";
			return;
		}

		cout << "<Quit>: Success\n";
		// Ready to exit the game
		exitGame = true;
	}

	// Invalid command
	else
	{
		cout << "<" << input << ">: Failed\n";
	}
}

// Intent: Load the board of MineSweeper
// Pre: mode must be valid
// Post: Print whether the action is successful
void MineSweeperCore::load(string mode)
{
	string input = mode;
	stringstream ss(mode);
	getline(ss, mode, ' ');

	// Load BoardFile: Load a board from a file
	if (mode == "BoardFile")
	{
		string name;
		getline(ss, name, ' ');

		// Load from file
		if (!loadFile(name))
		{
			cout << "<Load BoardFile " << name << ">: Failed\n";
			return;
		}
		cout << "<Load BoardFile " << name << ">: Success\n";
	}

	// Load RandomCount: Load a board with specified bomb amount
	else if (mode == "RandomCount")
	{
		// Split the content to width, length, and bomb amount
		string strWidth, strLength, strCount;
		getline(ss, strWidth, ' ');
		getline(ss, strLength, ' ');
		getline(ss, strCount, ' ');
		int w = stoi(strWidth), l = stoi(strLength), count = stoi(strCount);

		// Create a board with bomb amount
		_gameBoard = Board(w, l, count);
		_gameBoard.init();
		_gameBoard.genAnsBoard();

		cout << "<Load RandomCount " << w << " " << l << " " << count << ">: Success\n";
	}

	// Load RandomRate: Load a board with bomb rate
	else if (mode == "RandomRate")
	{
		// Splite the content to width, length, and bomb rate
		string strWidth, strLength, strRate;
		getline(ss, strWidth, ' ');
		getline(ss, strLength, ' ');
		getline(ss, strRate, ' ');
		int w = stoi(strWidth), l = stoi(strLength);
		double rate = stod(strRate);

		// Create a board with bomb rate
		_gameBoard = Board(w, l, rate);
		_gameBoard.init();
		_gameBoard.genAnsBoard();

		cout << "<Load RandomRate " << w << " " << l << " " << rate << ">: Success\n";
	}

	// Invalid command
	else
	{
		cout << "<Load " << input << ">: Failed\n";
		return;
	}

	// Game board load successfully
	_hasLoaded = true;
}

// Intent: Start the game
// Pre: None
// Post: Print whether the action is successful
void MineSweeperCore::startGame()
{
	// The action will fail if the board is not loaded
	if (!_hasLoaded)
	{
		cout << "<StartGame>: Failed\n";
		return;
	}
	cout << "<StartGame>: Success\n";
	// Ready to play the game
	_gameState = ONGOING;
}

// Intent: Show the certain information
// Pre: mode should be nonempty
// Post: Print the certain information
void MineSweeperCore::print(string mode)
{
	// Format the content of mode
	string input = mode;
	stringstream ss(mode);
	getline(ss, mode, ' ');

	// Print GameBoard: Show the game board
	if (mode == "GameBoard")
	{
		cout << "<Print GameBoard>: \n";
		_gameBoard.showBoard();
	}

	// Print GameState: Show the current state of the game
	else if (mode == "GameState")
	{
		cout << "<Print GameState>: " << strGameStat[_gameState] << '\n';
	}

	// Print GameAnswer: Show the answer board
	else if (mode == "GameAnswer")
	{
		cout << "<Print GameAnswer>: \n";
		_gameBoard.showAns();
	}

	// Print BombCount: Show the amount of the bomb of the game
	else if (mode == "BombCount")
	{
		cout << "<Print BombCount>: " << _gameBoard.getBombCount() << '\n';
	}

	// Print FlagCount: Show the current amount of the flag
	else if (mode == "FlagCount")
	{
		cout << "<Print FlagCount>: " << _gameBoard.getFlagCount() << '\n';
	}

	// Print OpenBlankCount: Show the current amount of opened blank
	else if (mode == "OpenBlankCount")
	{
		cout << "<Print OpenBlankCount>: " << _gameBoard.getOpenBlankCount() << '\n';
	}

	// Print RemainBlankCount: Show the remaining amount of blank
	else if (mode == "RemainBlankCount")
	{
		cout << "<Print RemainBlankCount>: " << _gameBoard.getRemainBlankCount() << '\n';
	}

	// Invalid command: extra command or lack command
	else
	{
		cout << "<Print " << mode << ">: Failed\n";
		return;
	}
}

// Intent: Left click to the position
// Pre: row and col should be in the range
// Post: Print whether the action is successful
void MineSweeperCore::leftClick(int row, int col)
{
	// Wrong state
	if (_gameState != ONGOING)
	{
		cout << "<LeftClick " << row << " " << col << ">: Failed\n";
		return;
	}

	// Fail to open blank
	if (!_gameBoard.openBlank(row, col))
	{
		cout << "<LeftClick " << row << " " << col << ">: Failed\n";
		return;
	}
	cout << "<LeftClick " << row << " " << col << ">: Success\n";

	// Player will lose when the bomb is opend
	if (_gameBoard.isBomb(row, col))
	{
		_gameState = END;
		cout << "You lose the game.\n";
		return;
	}

	// Player will win when all the blank is opend
	if (_gameBoard.getRemainBlankCount() == 0)
	{
		_gameState = END;
		cout << "You win the game.\n";
		return;
	}
}

// Intent: Right click to the position
// Pre: row and col should be in the range
// Post: Print whether the action is successful
void MineSweeperCore::rightClick(int row, int col)
{
	// Wrong state
	if (_gameState != ONGOING)
	{
		cout << "<RightClick " << row << " " << col << ">: Failed\n";
		return;
	}

	// Fail to set mark
	if (!_gameBoard.setMark(row, col))
	{
		cout << "<RightClick " << row << " " << col << ">: Failed\n";
		return;
	}

	cout << "<RightClick " << row << " " << col << ">: Success\n";
}

// Intent: Reset the game and replay
// Pre: None
// Post: Print whether the action is successful
void MineSweeperCore::replay()
{
	// Wrong state
	if (_gameState != END)
	{
		cout << "<Replay>: Failed\n";
		return;
	}

	// Reset the game
	_gameBoard = Board();
	_gameState = PENDING;
	_hasLoaded = false;

	cout << "<Replay>: Success\n";
}

// Intent: Load board from file
// Pre: file should exist
// Post: None
bool MineSweeperCore::loadFile(string fileName)
{
	ifstream boardFile(fileName);

	// Invalid file
	if (!boardFile.is_open())
	{
		return false;
	}

	int w = 0, l = 0;
	vector<vector<char>> board;
	boardFile >> w >> l;

	// Load board from file
	for (int i = 0; i < w; i++)
	{
		board.push_back({});
		for (int j = 0; j < l; j++)
		{
			char input;
			boardFile >> input;
			board[i].push_back(input);
		}
	}

	// Create the board with the board from file
	_gameBoard = Board(w, l, board);
	_gameBoard.genAnsBoard();
	return true;
}