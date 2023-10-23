#include "sysout.hpp"

/*
	Code Flow:
	1.) Find Neighbors
	2.) Find Practical Movement Points
	3.) Jump to possible points
	4.) Loop until we find a connection to the bottom row
*/

void FindPath(int s, vector<int> nGrid)
{
	/*
		1.) Start from index [0, nGrid.size() - 1] $interval notation$

		2.) loop through the current selected index's neighbors and move
			to the node closest to the bottom most row $ 0's are open areas, 1's are obstacles

		3.) Continue looping down towards the bottom until a path is found

		4.) Color show the path with couts
	*/

	// cout << "Range: [" << (s - 1) - (sqrt(s) - 1) << "," << (s - 1) << "]" << endl;

	// iterate first row
	for (int i = 0; i < sqrt(s); i++)
	{
		int neighbors[8];

		// cout << "[+] Shifting forward in the Top-Most-Row: " << i << endl;
		// 
		// clear previously drawn path
		for (int f = 0; f < s; f++)
		{
			if (nGrid[f] == 2) nGrid[f] = 0;
		}

		FindNeighbors(neighbors, i, s, nGrid);
	}

	cout << "[-] Sorry, No Path could be found\n Go Cry About It!" << endl;
	cout << "Wanna run the program again? [y/n]: ";
	char ans;
	cin >> ans;

	while (ans != 'y' && ans != 'n')
	{
		cout << "Dude read the prompt, I only accept y or n BOZO >:(\n Wanna run the program again? [y/n]: ";
		cin >> ans;
	}

	if (ans == 'y')
	{
		main();
	}
}

void FindNeighbors(int neighbors[], int cIndex, int s, vector<int> nGrid)
{
	// find valid neighbors that leads us down to the bottom row :: [(s - 1) - (sqrt(s) - 1), s - 1]

	/*
		===== DISTANCE CHART =====
			0   1   2   3   4
			5   6   7   8   9
			10  11  12  13  14
			15  16  17  18  19
			20  21  22  23  24

			diagonal_right::(+/-) size + 1 ## Linear line with negative slope
			vertical::(+/-) sqrt(array_size)
			diagonal_left::(+/-) size - 1 ## Linear line with positive slope
			horizontal::(+/-) 1

			# WATCH FOR EDGE CASES
			## (NEIGHBOR CALCS ARE DIFFERENT IN CASES WHERE THE cIndex EQUALS A NUMBER ON THE FIRST AND LAST INDEX OF THE ROW)
	*/

	bool solveEdgeCaseLeft = false, solveEdgeCaseRight = false;
	for (int i = 0; i < (int)sqrt(s); i++)
	{
		if ((cIndex == ((s - 1) - (sqrt(s) - 1)) - (sqrt(s) * i)))
		{
			solveEdgeCaseLeft = true;
		}
		else if ((cIndex == (s - 1) - (sqrt(s) * i)))
		{
			solveEdgeCaseRight = true;
		}
	}

	if (solveEdgeCaseLeft || solveEdgeCaseRight)
	{
		if (solveEdgeCaseLeft)
		{
			// Find neighbors above and below
			// Find neighbors to the RIGHT, diagonally in the RIGHT direction too
			// iterate through the discovered neighbors
			for (int i = 0; i < 8; i++)
			{
				switch (i)
				{
				case 0:
					//				10	 +  ( 10 + 1 ) == 21
					neighbors[i] = cIndex + (sqrt(s) + 1);
					break;
				case 1:
					//				10	 -  ( 10 - 1 ) == 1
					neighbors[i] = cIndex - (sqrt(s) - 1);
					break;
				case 2:
					neighbors[i] = cIndex + sqrt(s);
					break;
				case 3:
					neighbors[i] = cIndex - sqrt(s);
					break;
				case 4:
					neighbors[i] = cIndex + 1;
					break;
				default:
					neighbors[i] = -1;
					break;
				}
			}
		}
		else if (solveEdgeCaseRight)
		{
			// Find neighbors above and below
			// Find neighbors to the LEFT, diagonally in the LEFT direction too
			for (int i = 0; i < 8; i++)
			{
				switch (i)
				{
				case 0:
					neighbors[i] = cIndex - (sqrt(s) + 1);
					break;
				case 1:
					neighbors[i] = cIndex + (sqrt(s) - 1);
					break;
				case 2:
					neighbors[i] = cIndex + sqrt(s);
					break;
				case 3:
					neighbors[i] = cIndex - sqrt(s);
					break;
				case 4:
					neighbors[i] = cIndex - 1;
					break;
				default:
					neighbors[i] = -1;
					break;
				}
			}
		}
	}
	else
	{
		// iterate through the discovered neighbors
		for (int i = 0; i < 8; i++)
		{
			switch (i)
			{
			case 0:
				neighbors[i] = cIndex + (sqrt(s) + 1);
				break;
			case 1:
				neighbors[i] = cIndex - (sqrt(s) + 1);
				break;
			case 2:
				neighbors[i] = cIndex + (sqrt(s) - 1);
				break;
			case 3:
				neighbors[i] = cIndex - (sqrt(s) - 1);
				break;
			case 4:
				neighbors[i] = cIndex + sqrt(s);
				break;
			case 5:
				neighbors[i] = cIndex - sqrt(s);
				break;
			case 6:
				neighbors[i] = cIndex + 1;
				break;
			case 7:
				neighbors[i] = cIndex - 1;
				break;
			default:
				break;
			}
		}
	}

	/*
		0  1  2  3  4  5  6  7  8  9
		10 11 12 13 14 15 16 17 18 19
		20 21 22 23 24 25 26 27 28 29
		30 31 32 33 34 35 36 37 38 39
		40 41 42 43 44 45 46 47 48 49
		50 51 52 53 54 55 56 57 58 59
		60 61 62 63 64 65 66 67 68 69
		70 71 72 73 74 75 76 77 78 79
		80 81 82 83 84 85 86 87 88 89
		90 91 92 93 94 95 96 97 98 99
	*/

	
	/*cout << "\n========= cIndex:: " << cIndex << "=========" << endl;
	for (int i = 0; i < 8; i++)
	{
		if (neighbors[i] >= 0) cout << neighbors[i] << endl;
	}*/
	CalculateMove(neighbors, cIndex, s, nGrid);
}

void CalculateMove(int neighbors[], int cIndex, int s, vector<int> nGrid)
{
	// With restricting movement to the downwards direction
	// we only have to deal with 3 values

	int pNodes[3]{};
	int i2 = 0;

	for (int i = 0; i < 8; i++)
	{
		if (i2 < 3)
		{
			// Look only at positive numbers
			if (neighbors[i] > 0)
			{
				if (neighbors[i] == (cIndex + sqrt(s)) || neighbors[i] == (cIndex + (sqrt(s) - 1)) || neighbors[i] == (cIndex + (sqrt(s) + 1)))
				{
					pNodes[i2] = neighbors[i];
					// cout << pNodes[i2] << " -> " << nGrid[pNodes[i2]] << endl;
					i2++;
				}
			}
			else
			{
				break;
			}
		}
	}

	// Determine whether the pNodes are valid moving points or not
	for (int i3 = 0; i3 < 3; i3++)
	{
		// cout << "[*] Is " << pNodes[i3] << " -> " << nGrid[pNodes[i3]] << " == 0?" << endl;

		if (nGrid[pNodes[i3]] == 0)
		{
			// If a valid moving node is a value in the bottom most row of the vector array
			if (isGoalInRange(pNodes[i3], s))
			{
				nGrid[cIndex] = 2;
				nGrid[pNodes[i3]] = 2;
				PrintPath(nGrid);
			}
			else // move to the valid node, find neighbors, loop until endpoint is found or dead end is discovered
			{
				nGrid[cIndex] = 2;
				nGrid[pNodes[i3]] = 2;
				cIndex = pNodes[i3];
				
				// Pausing Stack Frame
				/*cout << "[*] cIndex is changing to:: " << cIndex << endl << "[Press Enter to Step Forward]" << endl;
				char sChar;
				cin >> sChar;*/

				Move2Node(neighbors, cIndex, s, nGrid);
			}
		}
	}
}

bool isGoalInRange(int t, int s)
{
	// cout << t << " > " << (s - 1) - (sqrt(s) - 1) << endl;
	// cout << t << " < " << (s - 1) << endl;

	return ((t >= ((s - 1) - (sqrt(s) - 1))) && (t <= (s - 1)));
}

void Move2Node(int neighbors[], int cIndex, int s, vector<int> nGrid)
{
	FindNeighbors(neighbors, cIndex, s, nGrid);
}