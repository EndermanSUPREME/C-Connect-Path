#include <iostream>
#include <vector> // allows for dynamic arrays
#include <ctime>
#include <cstdlib>
#include <stdlib.h>
#include <string>

using std::cin; using std::cout; using std::endl;
using std::vector;
using std::string;

#ifndef sysout.hpp
#define user
// user method defs
int main();
int getSize();
#define grid
// grid method defs
void ConstructGrid(int s);
#define calc
// calc method defs
void FindPath(int s, vector<int> nGrid);
void FindNeighbors(int neighbors[], int cIndex, int s, vector<int> nGrid);
void CalculateMove(int neighbors[], int cIndex, int s, vector<int> nGrid);
bool isGoalInRange(int t, int s);
void Move2Node(int neighbors[], int cIndex, int s, vector<int> nGrid);
void PrintPath(vector<int> nGrid);
#endif