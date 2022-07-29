#pragma once
//======================================================================================
//Header file for bots: initially cBotRandom is defined here, but other bot classes
//can go here too
//
//(c) Patrick Dickinson, University of Lincoln, School of Computer Science, 2020
//======================================================================================

#include "botbase.h"
#include <vector>
#include <string>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <array>

class cBotRandom : public cBotBase
{
	virtual void ChooseNextGridPosition();
};

class cDijkstra
{
public:
	bool closed[GRIDWIDTH][GRIDHEIGHT]; //whether or not location is closed
	float cost[GRIDWIDTH][GRIDHEIGHT]; //cost value for each location
	int linkX[GRIDWIDTH][GRIDHEIGHT]; //link X coord for each location
	int linkY[GRIDWIDTH][GRIDHEIGHT]; //link Y coord for each location
	bool inPath[GRIDWIDTH][GRIDHEIGHT]; //whether or not a location is in the final path
	bool completed;
	cDijkstra() { completed = false; }
	virtual void Build(cBotBase& bot);
};
extern cDijkstra gDijkstra;

class cAStar : public cDijkstra {
public:
	// member variable of a 1d index array which is currently set to 0
	int FinalPath[1] = { 0 };
	// member variable of vector which holds the converted 2d coordinates into 1d form to then be put into the final path index array
	std::vector<int>pathway;
	// each heuristic is mapped to a different key bind
	// when p is pressed manhattan distance is used
	// when o is pressed diagonal distance is used
	// when i is pressed euclidean distance is used
	virtual void BuildManhattan(cBotBase& bot);
	virtual void BuildDiagonal(cBotBase& bot);
	virtual void BuildEuclidean(cBotBase& bot);
};
extern cAStar gAStar;

class cBotAStar : public cBotBase {
	virtual void ChooseNextGridPosition();
};
