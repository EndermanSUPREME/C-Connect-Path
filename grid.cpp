#include "sysout.hpp"

// build an array based off of size
// paint a nice grid on screen for the user

// ANSI escape codes for color formatting
const string RED_COLOR = "\033[1;31m";    // Red text
const string GREEN_COLOR = "\033[1;32m";  // Green text

const string DARK_BROWN = "\033[0;33m";       // Dark Brown
const string BLUE = "\033[34m";          // Blue

const string RESET_COLOR = "\033[0m";     // Reset to default color

void ConstructGrid(int s)
{
	vector<int> nGrid;

    // Resize the vector to the desired size
    nGrid.resize(s);

	// Ensure true randomness
	srand(time(nullptr));

	for (int i = 0; i < (int)sqrt(s); i++)
	{
		for (int i2 = 0; i2 < (int)sqrt(s); i2++)
		{
			nGrid[((int)sqrt(s) * i) + i2] = ((rand() % 100)) % 2;

			if (i2 < (int)sqrt(s) - 1)
			{
				if (nGrid.at(((int)sqrt(s) * i) + i2) == 0)
				{
					cout << RESET_COLOR << nGrid.at(((int)sqrt(s) * i) + i2) << RESET_COLOR << " - ";
				}
				else // change values that arent 0
				{
					if (((rand() % 100)) % 2 == 0)
					{
						cout << DARK_BROWN << nGrid.at(((int)sqrt(s) * i) + i2) << RESET_COLOR << " - ";
					}
					else
					{
						nGrid[((int)sqrt(s) * i) + i2] = 3;
						cout << BLUE << nGrid.at(((int)sqrt(s) * i) + i2) << RESET_COLOR << " - ";
					}
				}
			}
			else
			{
				if (nGrid.at(((int)sqrt(s) * i) + i2) == 0)
				{
					cout << RESET_COLOR << nGrid.at(((int)sqrt(s) * i) + i2) << RESET_COLOR  << endl;
				}
				else // change values that arent 0
				{
					if (((rand() % 100)) % 2 == 0)
					{
						cout << DARK_BROWN << nGrid.at(((int)sqrt(s) * i) + i2) << RESET_COLOR << endl;
					}
					else
					{
						nGrid[((int)sqrt(s) * i) + i2] = 3;
						cout << BLUE << nGrid.at(((int)sqrt(s) * i) + i2) << RESET_COLOR << endl;
					}
				}
			}
		}
	}

	FindPath(s, nGrid);
}

//=============================================================================
//=============================================================================
//=============================================================================

void PrintPath(vector<int> nGrid)
{
	cout << endl << "===================================================" << endl << endl;

	int s = nGrid.size();

	for (int i = 0; i < (int)sqrt(s); i++)
	{
		for (int i2 = 0; i2 < (int)sqrt(s); i2++)
		{
			int gridIndex = (nGrid.at(((int)sqrt(s) * i) + i2));

			if (i2 < (int)sqrt(s) - 1)
			{
				if (gridIndex == 2)
				{
					cout << GREEN_COLOR << nGrid.at(((int)sqrt(s) * i) + i2) << RESET_COLOR << " - ";
				}
				else // change values that arent 2
				{
					if (gridIndex == 1)
					{
						cout << DARK_BROWN << nGrid.at(((int)sqrt(s) * i) + i2) << RESET_COLOR << " - ";
					}
					else if (gridIndex == 0)
					{
						cout << RESET_COLOR << nGrid.at(((int)sqrt(s) * i) + i2) << RESET_COLOR << " - ";
					}
					else
					{
						cout << BLUE << nGrid.at(((int)sqrt(s) * i) + i2) << RESET_COLOR << " - ";
					}
				}
			}
			else
			{
				if (gridIndex == 2)
				{
					cout << GREEN_COLOR << nGrid.at(((int)sqrt(s) * i) + i2) << RESET_COLOR << endl;
				}
				else // change values that arent 2
				{
					if (gridIndex == 1)
					{
						cout << DARK_BROWN << nGrid.at(((int)sqrt(s) * i) + i2) << RESET_COLOR << endl;
					}
					else if (gridIndex == 0)
					{
						cout << RESET_COLOR << nGrid.at(((int)sqrt(s) * i) + i2) << RESET_COLOR << endl;
					}
					else
					{
						cout << BLUE << nGrid.at(((int)sqrt(s) * i) + i2) << RESET_COLOR << endl;
					}
				}
			}
		}
	}

	// End the program when a path is found
	cout << "[*] EXITING" << endl;
	exit(0);
}