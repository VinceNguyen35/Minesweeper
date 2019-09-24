// Minesweeper Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

/*
These are the public variables that will be used in multiple functions
*/
#define ROWS 9
#define COLS 9

int realRowInput;
int colInput;
int numOfMines = '0';

/*
Displays the array that is inputted
@param char array[ROWS][COLS] is the 2D array
*/
void displayArray(char array[ROWS][COLS])
{
	cout << "  1 2 3 4 5 6 7 8 9" << endl;
	for (int i = 65; i < 74; i++)
	{
		//ASCII is used to reduce hard coding the row letters
		char asciiChar = i;
		cout << asciiChar;
		for (int j = 0; j < 9; j++)
		{
			cout << " " << array[i - 65][j];
		}
		cout << endl;
	}
}

/*
Converts a string to an int by separating all parts of the string into multiple "char"
All white(blank) spaces are removed to convert the "char" into a single int
@param string letter is the string that will be converted to char to int
@return is the ASCII value of all the "char" put together
*/
int convertToASCII(string letter)
{
	int stringValue = 0;
	for (int i = 0; i < letter.length(); i++)
	{
		char x = letter.at(i);
		stringValue = stringValue + int(x);
	}
	return stringValue;
}

/*
Allows the user to enter a row letter and a column number
@param char array[ROWS][COLS] is the 2D array
@return the contents of the 2D array at the inputted location
*/
int InputForRowCol(char array[ROWS][COLS])
{
	string rowInput;
	bool waitingForProperRowInput = true;
	bool waitingForProperColInput = true;

	//this loop will continue until the user inputs a valid capital letter between A-I
	//lowercase letters will not be accepted
	//multiple letters are also not accepted
	while (waitingForProperRowInput)
	{
		cout << "Enter a row letter: " << endl;
		cin >> rowInput;

		//separate function below is used for convenience
		realRowInput = convertToASCII(rowInput) - 64;

		//this statement is used to confirm whether the row letter was converted correctly or not
		if ((realRowInput < 11) && (realRowInput > 0))
		{
			realRowInput--;
			waitingForProperRowInput = false;
		}
		else
		{
			cout << "Invalid Input" << endl;
		}
	}

	//this loop will continue until a valid int between 1-9 is inputted
	while (waitingForProperColInput)
	{
		cout << "Enter a column number" << endl;
		if (cin >> colInput)
		{
			if ((colInput > 0) && (colInput < 10))
			{
				colInput--;
				waitingForProperColInput = false;
			}
			else
			{
				cout << "Invalid Input" << endl;
			}
		}
		else
		{
			cin.clear(); //clear out invalid input
			string invalid;
			cin >> invalid;
			cout << "Invalid Input" << endl;
		}
	}
	return array[realRowInput][colInput];
}

/*
Resets the grid to containing only "x"s
*/
void resetGrid(char array[ROWS][COLS])
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			array[i][j] = 'x';
		}
	}
}

/*
Determines of the location is a mine
@param char array[ROWS][COLS] is the 2D array
@return whether there is a mine or not at the location called upon
*/
bool thisIsAMine(char array[ROWS][COLS])
{
	if (array[realRowInput][colInput] == 'o')
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
Counts how many mines are surrounding the selected location
@param char array[ROWS][COLS] is the 2D array
@return the number of mines around the inputted location
*/
int nearbyMines(char array[ROWS][COLS])
{
	//although this variable will be used for multiple reasons, it is put here again to reset itself
	numOfMines = '0';

	//top left neighbor
	if (array[realRowInput - 1][colInput - 1] == 'o')
	{
		numOfMines++;
	}

	//top middle neighbor
	if (array[realRowInput][colInput - 1] == 'o')
	{
		numOfMines++;
	}

	//top right neighbor
	if (array[realRowInput + 1][colInput - 1] == 'o')
	{
		numOfMines++;
	}

	//middle left neighbor
	if (array[realRowInput - 1][colInput] == 'o')
	{
		numOfMines++;
	}

	//middle right neighbor
	if (array[realRowInput + 1][colInput] == 'o')
	{
		numOfMines++;
	}

	//bottom left neighbor
	if (array[realRowInput - 1][colInput + 1] == 'o')
	{
		numOfMines++;
	}

	//bottom middle neighbor
	if (array[realRowInput][colInput + 1] == 'o')
	{
		numOfMines++;
	}

	//bottom right neighbor
	if (array[realRowInput + 1][colInput + 1] == 'o')
	{
		numOfMines++;
	}
	return numOfMines;
}

/*
Allows an int to be stored in a char array
@param1 char array[ROWS][COLS] is the 2D array
@param2 int a is the number being inserted into the array
*/
void putNumIntoGrid(char array[ROWS][COLS], int a)
{
	array[realRowInput][colInput] = (char)a;
}

/*
Places a flag on the grid
@param char array[ROWS][COLS] is the 2D array
*/
void placeFlag(char array[ROWS][COLS])
{
	array[realRowInput][colInput] = 'F'; //literally this puts an "F" into the array
}

/*
Determines if the user has successfully won the game
@param1 char array[ROWS][COLS] is the fake 2D array that is normally displayed
@param2 char array1[ROWS][COLS] is the 2D array that contains all the mines and isn't displayed
@return whether the game is won or not
*/
bool victory(char array[ROWS][COLS], char array1[ROWS][COLS])
{
	//arrEqual is always true until found false at a location
	bool arrEqual = true;
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (array[i][j] != array1[i][j])
			{
				//if in this area, then there is either a mine, an "F", or both
				if (array[i][j] == 'F')
					//if in this area, then the "F" is placed on a mine
				{}
				else
				{
					arrEqual = false;
				}
			}
		}
	}
	bool victory = arrEqual;
	return victory;
}

int main()
{
	int option;
	char fakegrid[ROWS][COLS];
	char grid[ROWS][COLS];

	//this will open the txt file that the level generator program wrote into
	fstream file;
	file.open("C:/Users/Vince Nguyen/Desktop/Mines.txt", ios::in);
	if (file)
	{
		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COLS; j++)
			{
				file >> grid[i][j];
				cout << grid[i][j]; //this allows us to see the location of the mines for testing purposes
			}
			cout << endl;
		}
	}

	resetGrid(fakegrid);
	displayArray(fakegrid);

	//this will keep running until the game is won, the user reveals a mine, or the user decides to quit
	bool menu = true;
	while (menu)
	{
		cout << endl;
		cout << "Minesweeper:" << endl;
		cout << "1. Reveal" << endl;
		cout << "2. Drop Flag" << endl;
		cout << "3. Quit" << endl;
		if (cin >> option)
		{
			if (option > 0) //checks that the input is a number
			{
				if (option < 4) //checks that the input is valid
				{
					if (option == 1)
					{
						InputForRowCol(grid);
						if (fakegrid[realRowInput][colInput] != 'x') //checks if the location is already revealed
						{
							cout << "Already Revealed." << endl;
						}
						else
						{
							fakegrid[realRowInput][colInput] = grid[realRowInput][colInput];
							if (thisIsAMine(grid)) //checks if the location is a mine
							{
								displayArray(fakegrid);
								cout << "Game Over!" << endl;
								menu = false;
							}
							else //this displays the fake grid, but will insert the location of the real grid into the fake grid
							{
								fakegrid[realRowInput][colInput] = nearbyMines(grid);
								displayArray(fakegrid);
							}
						}
					}
					if (option == 2)
					{
						if (InputForRowCol(fakegrid) == 'F') //checks if the location is already flagged
						{
							cout << "Already Flagged." << endl;
						}
						else
						{
							if (fakegrid[realRowInput][colInput] != 'x') //checks if the location is already revealed
							{
								cout << "Already Revealed." << endl;
							}
							else
							{
								placeFlag(fakegrid);
								displayArray(fakegrid);
							}
						}
					}
					if (option == 3)
					{
						menu = false; //basically quitting
					}
					if (victory(fakegrid, grid))
					{
						cout << endl;
						cout << "Congratulations! You Won!" << endl;
						menu = false;
					}
				}
				else
				{
					cout << "Invalid Input" << endl;
				}
			}
			if (option == 0)
			{
				cout << "Invalid Input" << endl;
			}
		}
		else
		{
			cin.clear();
			string invalid;
			cin >> invalid;
			cout << "Invalid Input" << endl;
		}
	}
	return 0;
}