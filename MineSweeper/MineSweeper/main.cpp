/*********************************************************************
 * File:        main.cpp
 * Author:      MIN-FENG CHEN
 * Create Date: July 4, 2023
 * Editor:      MIN-FENG CHEN
 * Update Date: July 7, 2023
 * Description: Main program to select mode
 *********************************************************************/
#include "Game.h"
#include <fstream>
using namespace std;

void runGUI();											// Run GUI of MineSweeper
void runConsole();										// Run the console of MineSweeper
void runFileMode(string inputName, string outputName);	// Run the file mode of MineSweeper

int main(int argc, char* argv[])
{
	if (argc == 0)
	{
		cout << "arg error!\n";
	}
	else if (argc == 2)
	{
		if (string(argv[1]) == "GUI")
		{
			runGUI();
		}
		else if (string(argv[1]) == "CommandInput")
		{
			runConsole();
		}
		else
		{
			cout << "arg error!\n";
		}
	}
	else if (argc == 4 && string(argv[1]) == "CommandFile")
	{
		runFileMode(string(argv[2]), string(argv[3]));
	}
	else
	{
		cout << "arg error!\n";
	}

	return 0;
}

// Intent: Run the GUI of MineSweeper
// Pre: None
// Post: None
void runGUI()
{
	cout << "Sorry, I am working on it.\n";
	cout << "I will finish it ASAP.\n";
}

// Intent: Run the console mode of MineSweeper
// Pre: None
// Post: None
void runConsole()
{
	MineSweeperCore mineSweeper;
	string cmdLine;

	while (getline(cin, cmdLine))
	{
		mineSweeper.execute(cmdLine);

		if (mineSweeper.exitGame)
		{
			break;
		}
	}
}


// Intent: Run the file mode of MineSweeper
// Pre: None
// Post: Write the result to the output file
void runFileMode(string inputName, string outputName)
{
	ifstream inputFile(inputName);
	if (!inputFile.is_open())
	{
		cout << "Invalid input file.\n";
		return;
	}

	ofstream outputFile(outputName);
	MineSweeperCore mineSweeper;
	string cmdLine;

	auto backupBuffer = cout.rdbuf();
	cout.rdbuf(outputFile.rdbuf());
	while (getline(inputFile, cmdLine))
	{
		mineSweeper.execute(cmdLine);

		if (mineSweeper.exitGame)
		{
			break;
		}
	}
	cout.rdbuf(backupBuffer);
	inputFile.close();
	outputFile.close();
}