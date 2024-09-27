#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

using namespace std;

int numRows, numCols;
int mod(int a, int b)
{ 
    return (a % b + b) % b; 
}
void life(vector<vector<bool> > &gameBoard)
{
	vector<vector<bool> > tempBoard;
	tempBoard = gameBoard;
	
	for (int i = 0; i < tempBoard.size(); i++)
	{
		for (int j = 0; j < tempBoard.at(i).size(); j++)
		{
			int neighborCount = 0;
			neighborCount = gameBoard.at(mod((i-1), numRows)).at(mod((j-1), numCols)) +
							gameBoard.at(mod((i-1), numRows)).at(mod(j, numCols))   +
							gameBoard.at(mod((i-1), numRows)).at(mod((j+1), numCols)) + 
							gameBoard.at(mod(i, numRows)).at(mod((j-1), numCols))   +
							gameBoard.at(mod(i, numRows)).at(mod(j+1, numCols))   +
							gameBoard.at(mod(i+1, numRows)).at(mod(j-1, numCols)) + 
							gameBoard.at(mod(i+1, numRows)).at(mod(j, numCols))   +
							gameBoard.at(mod(i+1, numRows)).at(mod(j+1, numCols));
							
			if (neighborCount < 2 || neighborCount > 3)
				tempBoard.at(i).at(j) = false;
				
			if (neighborCount == 3)
				tempBoard.at(i).at(j) = true;
		}
	}
	gameBoard = tempBoard;
}

void printBoard(vector<vector<bool> > gameBoard, string cell, bool wideMode)
{
	for (unsigned int i = 0; i < gameBoard.size(); i++)
	{
		for (unsigned int j = 0; j < gameBoard.at(i).size(); j++)
		{
			if (wideMode)
			{
				if (gameBoard.at(i).at(j) == 1)
					cout << cell << " ";
				else cout << "  "; 
			}
			else
			{
				if (gameBoard.at(i).at(j) == 1)
					cout << cell;
				else cout << " "; 
			}
		}
		cout << endl;
	}
}

void seedBoard(vector<vector<bool> > &gameBoard)
{
	for (unsigned int i = 1; i < gameBoard.size()-1; i++)
	{
		for (unsigned int j = 1; j < gameBoard.at(i).size()-1; j++)
		{
			gameBoard.at(i).at(j) = rand() % 2;
		}
	}
}

void setBlinker(vector<vector<bool> > &gameBoard)
{
	gameBoard.at(7).at(7) = true;
	gameBoard.at(7).at(8) = true;
	gameBoard.at(7).at(9) = true;
}

int main ()
{
	//int x, y;
	cout << "Enter number of rows and columns: ";
	cin >> numRows >> numCols;
	
	vector<vector<bool> > gameBoard(numRows, vector<bool>(numCols, 0));

	
	int generations = 0;
	double timeStep = 0.0;
	string cells;
	char wideMode = 'n';
	
	cout << "how many generations?: ";
	cin >> generations;
	cout << "enter cell character: ";
	cin >> cells;
	cout << "Enter time step in seconds: ";
	cin >> timeStep;
	cout << "widescreen rendering? (y or n): ";
	cin >> wideMode;
	cout << endl;
	
	srand(time(NULL));
	seedBoard(gameBoard);
	
	for (int i = 0; i < generations; i++)
	{
		system("clear");
		
		cout << "generation: " << i+1 << endl; 
		if (wideMode == 'y')
			printBoard(gameBoard, cells, true);
		else 
			printBoard(gameBoard, cells, false);

		
		life(gameBoard);
		usleep(timeStep * 1000000);
	
	}
}
