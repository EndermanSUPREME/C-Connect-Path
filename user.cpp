#include "sysout.hpp"

int userSetSize = 0;

int main()
{
	// Take the Users Input to build a randomized grid
	// Accept sizes that are 10+
	while (userSetSize < 9)
	{
		cout << "Input size of grid [10 or Greater]: ";
		cin >> userSetSize;
	}

	userSetSize *= userSetSize;

	/*for (int i = 0; i < (int)sqrt(userSetSize); i++)
	{
		for (int i2 = 0; i2 < (int)sqrt(userSetSize); i2++)
		{
			if (i2 < (int)sqrt(userSetSize) - 1)
			{
				cout << (((int)sqrt(userSetSize) * i) + i2) << " ";
			}
			else
			{
				cout << (((int)sqrt(userSetSize) * i) + i2) << endl;
			}
		}
	}*/

	// Spawn grid
	ConstructGrid(userSetSize);
}

int getSize()
{
	return userSetSize;
}