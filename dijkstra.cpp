#include "bots.h"
#include "stdlib.h"
#include <cmath>
#include <array>
#include <iostream>
#include <vector>
#include <algorithm>
void cDijkstra::Build(cBotBase& bot) {
	for (int i = 0; i < GRIDWIDTH; i++) {
		for (int j = 0; j < GRIDHEIGHT; j++) {
			closed[i][j] = false; //whether or not location is closed
			cost[i][j] = 1000000.0f; //cost value for each location
			linkX[i][j] = -1; //link X coord for each location
			linkY[i][j] = -1;//link Y coord for each location
			inPath[i][j] = false; //whether or not a location is in the final path
		}
	}
	cost[bot.PositionX()][bot.PositionY()] = 0;
	int counter = 0;
	bool done1 = false;
	int LowestPositionX; int LowestPositionY;
	while (!done1) {
		float lowest = 1000000.0f;
		for (int i = 0; i < GRIDWIDTH; i++) {
			for (int j = 0; j < GRIDHEIGHT; j++) {
				if (cost[i][j] < lowest) {
					if (closed[i][j] == false) {
						if (gLevel.isValid(i, j)) {
							lowest = cost[i][j];
							LowestPositionX = i;
							LowestPositionY = j;
						}
					}
				}
			}
		}
		closed[LowestPositionX][LowestPositionY] = true;
		if (gLevel.isValid(LowestPositionX + 1, LowestPositionY)) {
			if (closed[LowestPositionX + 1][LowestPositionY] == false) { // right neighbour
				if (cost[LowestPositionX + 1][LowestPositionY] > lowest + 1) {
					cost[LowestPositionX + 1][LowestPositionY] = lowest + 1;
					linkX[LowestPositionX + 1][ LowestPositionY] = LowestPositionX;
					linkY[LowestPositionX + 1][ LowestPositionY] = LowestPositionY;
				}
			}
		}
		if (gLevel.isValid(LowestPositionX - 1, LowestPositionY)) {
			if (closed[LowestPositionX - 1][LowestPositionY] == false) { // left neighbour
				if (cost[LowestPositionX - 1][LowestPositionY] > lowest + 1) {
					cost[LowestPositionX - 1][LowestPositionY] = lowest + 1;
					linkX[LowestPositionX - 1][ LowestPositionY] = LowestPositionX;
					linkY[LowestPositionX - 1][ LowestPositionY] = LowestPositionY;
				}
			}
		}
		if (gLevel.isValid(LowestPositionX, LowestPositionY + 1)) {
			if (closed[LowestPositionX][LowestPositionY + 1] == false) { // up neighbour
				if (cost[LowestPositionX][LowestPositionY + 1] > lowest + 1) {
					cost[LowestPositionX][LowestPositionY + 1] = lowest + 1;
					linkX[LowestPositionX][ LowestPositionY + 1] = LowestPositionX;
					linkY[LowestPositionX][ LowestPositionY + 1] = LowestPositionY;
				}
			}
		}
		if (gLevel.isValid(LowestPositionX, LowestPositionY - 1)) {
			if (closed[LowestPositionX][LowestPositionY - 1] == false) { // down neighbour
				if (cost[LowestPositionX][LowestPositionY - 1] > lowest + 1) {
					cost[LowestPositionX][LowestPositionY - 1] = lowest + 1;
					linkX[LowestPositionX][ LowestPositionY - 1] = LowestPositionX;
					linkY[LowestPositionX][ LowestPositionY - 1] = LowestPositionY;
				}
			}
		}
		if (gLevel.isValid(LowestPositionX + 1, LowestPositionY + 1)) {
			if (closed[LowestPositionX + 1][LowestPositionY + 1] == false) { // up-right neighbour
				if (cost[LowestPositionX + 1][LowestPositionY + 1] > lowest + 1.4f) {
					cost[LowestPositionX + 1][LowestPositionY + 1] = lowest + 1.4f;
					linkX[LowestPositionX + 1][ LowestPositionY + 1] = LowestPositionX;
					linkY[LowestPositionX + 1][ LowestPositionY + 1] = LowestPositionY;
				}
			}
		}
		if (gLevel.isValid(LowestPositionX + 1, LowestPositionY - 1)) {
			if (closed[LowestPositionX + 1][LowestPositionY - 1] == false) { // down-right neighbour
				if (cost[LowestPositionX + 1][LowestPositionY - 1] > lowest + 1.4f) {
					cost[LowestPositionX + 1][LowestPositionY - 1] = lowest + 1.4f;
					linkX[LowestPositionX + 1][ LowestPositionY - 1] = LowestPositionX;
					linkY[LowestPositionX + 1][ LowestPositionY - 1] = LowestPositionY;
				}
			}
		}
		if (gLevel.isValid(LowestPositionX - 1, LowestPositionY - 1)) {
			if (closed[LowestPositionX - 1][LowestPositionY - 1] == false) { // down-left neighbour
				if (cost[LowestPositionX - 1][LowestPositionY - 1] > lowest + 1.4f) {
					cost[LowestPositionX - 1][LowestPositionY - 1] = lowest + 1.4f;
					linkX[LowestPositionX - 1][ LowestPositionY - 1] = LowestPositionX;
					linkY[LowestPositionX - 1][ LowestPositionY - 1] = LowestPositionY;
				}
			}
		}
		if (gLevel.isValid(LowestPositionX - 1, LowestPositionY + 1)) {
			if (closed[LowestPositionX - 1][LowestPositionY + 1] == false) { // up-left neighbour
				if (cost[LowestPositionX - 1][LowestPositionY + 1] > lowest + 1.4f) {
					cost[LowestPositionX - 1][LowestPositionY + 1] = lowest + 1.4f;
					linkX[LowestPositionX - 1][ LowestPositionY + 1] = LowestPositionX;
					linkY[LowestPositionX - 1][ LowestPositionY + 1] = LowestPositionY;
				}
			}
		}
		if (LowestPositionX == gTarget.PositionX() && LowestPositionY == gTarget.PositionY()) {
			done1 = true;
		}
	}
	bool done = false; //set to true when we are back at the bot position
	int nextClosedX = gTarget.PositionX(); //start of path
	int nextClosedY = gTarget.PositionY(); //start of path
	while (!done)
	{
		inPath[nextClosedX][nextClosedY] = true;
		int tmpX = nextClosedX;
		int tmpY = nextClosedY;
		nextClosedX = linkX[tmpX][tmpY];
		nextClosedY = linkY[tmpX][tmpY];
		if ((nextClosedX == bot.PositionX()) && (nextClosedY == bot.PositionY())) {
			done = true;
		}
		cDijkstra::completed = true;
	}
}
cDijkstra gDijkstra;
void cAStar::BuildManhattan(cBotBase& bot) {
	for (int i = 0; i < GRIDWIDTH; i++) {
		for (int j = 0; j < GRIDHEIGHT; j++) {
			closed[i][j] = false; //whether or not location is closed
			cost[i][j] = 1000000.0f; //cost value for each location
			linkX[i][j] = -1; //link X coord for each location
			linkY[i][j] = -1;//link Y coord for each location
			inPath[i][j] = false; //whether or not a location is in the final path
		}
	}
	cost[bot.PositionX()][bot.PositionY()] = 0; // bot position cost is set to zero
	int counter = 0;
	bool done1 = false;
	int LowestPositionX; int LowestPositionY;
	while (!done1) {
		// two lowest variables are equal to the highest costing grid location
		float lowest = 1000000.0f; 
		float lowest1 = 1000000.0f;
		// for loop which loops through entire grid width 
		for (int i = 0; i < GRIDWIDTH; i++) { 
			// for loop which loops through entire grid height
			for (int j = 0; j < GRIDHEIGHT; j++) {	
				// manhattan path finding equation
				float manhattan_distance = fabs(i - gTarget.PositionX()) + fabs(j - gTarget.PositionY()); 
				// if statement which checks that the current cost location + the heuristic is less than the lowest variable ( 1st iteration this would be 1000000.0f )
				// if statement then checks if the current grid location is closed or not, then checks if the current grid location position is valid 
				if (cost[i][j] + manhattan_distance < lowest1 && closed[i][j] == false && gLevel.isValid(i, j)) { 
				// current grid location is set to two variables 'LowestPositionX' and 'LowestPositionY'
				// lowest cost is then equal to the cost of the newest position
				// lowest1 variable is equal to the cost of the newest location plus the heuristic distance
				// the second lowest variable is used to utilise the heuristic path finding
					LowestPositionX = i;
					LowestPositionY = j;
					lowest = cost[i][j];
					lowest1 = cost[i][j] + manhattan_distance;
				}
			}
		}
		// current location is then set to closed
		closed[LowestPositionX][LowestPositionY] = true;
		// following if statements check each neighbour of the new current location and adds the corresponding cost to the location 
		//(+1 for non diagonal neighbours) 
		//(+1.4 for diagonal neighbours)
		if (gLevel.isValid(LowestPositionX + 1, LowestPositionY)) {
			if (closed[LowestPositionX + 1][LowestPositionY] == false) { // right neighbour
				if (cost[LowestPositionX + 1][LowestPositionY] > lowest + 1) {
					cost[LowestPositionX + 1][LowestPositionY] = lowest + 1;
					linkX[LowestPositionX + 1][LowestPositionY] = LowestPositionX;
					linkY[LowestPositionX + 1][LowestPositionY] = LowestPositionY;
				}
			}
		}
		if (gLevel.isValid(LowestPositionX - 1, LowestPositionY)) {
			if (closed[LowestPositionX - 1][LowestPositionY] == false) { // left neighbour
				if (cost[LowestPositionX - 1][LowestPositionY] > lowest + 1) {
					cost[LowestPositionX - 1][LowestPositionY] = lowest + 1;
					linkX[LowestPositionX - 1][LowestPositionY] = LowestPositionX;
					linkY[LowestPositionX - 1][LowestPositionY] = LowestPositionY;
				}
			}
		}
		if (gLevel.isValid(LowestPositionX, LowestPositionY + 1)) {
			if (closed[LowestPositionX][LowestPositionY + 1] == false) { // up neighbour
				if (cost[LowestPositionX][LowestPositionY + 1] > lowest + 1) {
					cost[LowestPositionX][LowestPositionY + 1] = lowest + 1;
					linkX[LowestPositionX][LowestPositionY + 1] = LowestPositionX;
					linkY[LowestPositionX][LowestPositionY + 1] = LowestPositionY;
				}
			}
		}
		if (gLevel.isValid(LowestPositionX, LowestPositionY - 1)) {
			if (closed[LowestPositionX][LowestPositionY - 1] == false) { // down neighbour
				if (cost[LowestPositionX][LowestPositionY - 1] > lowest + 1) {
					cost[LowestPositionX][LowestPositionY - 1] = lowest + 1;
					linkX[LowestPositionX][LowestPositionY - 1] = LowestPositionX;
					linkY[LowestPositionX][LowestPositionY - 1] = LowestPositionY;
				}
			}
		}
		if (gLevel.isValid(LowestPositionX + 1, LowestPositionY + 1)) {
			if (closed[LowestPositionX + 1][LowestPositionY + 1] == false) { // up-right neighbour
				if (cost[LowestPositionX + 1][LowestPositionY + 1] > lowest + 1.4f) {
					cost[LowestPositionX + 1][LowestPositionY + 1] = lowest + 1.4f;
					linkX[LowestPositionX + 1][LowestPositionY + 1] = LowestPositionX;
					linkY[LowestPositionX + 1][LowestPositionY + 1] = LowestPositionY;
				}
			}
		}
		if (gLevel.isValid(LowestPositionX + 1, LowestPositionY - 1)) {
			if (closed[LowestPositionX + 1][LowestPositionY - 1] == false) { // down-right neighbour
				if (cost[LowestPositionX + 1][LowestPositionY - 1] > lowest + 1.4f) {
					cost[LowestPositionX + 1][LowestPositionY - 1] = lowest + 1.4f;
					linkX[LowestPositionX + 1][LowestPositionY - 1] = LowestPositionX;
					linkY[LowestPositionX + 1][LowestPositionY - 1] = LowestPositionY;
				}
			}
		}
		if (gLevel.isValid(LowestPositionX - 1, LowestPositionY - 1)) {
			if (closed[LowestPositionX - 1][LowestPositionY - 1] == false) { // down-left neighbour
				if (cost[LowestPositionX - 1][LowestPositionY - 1] > lowest + 1.4f) {
					cost[LowestPositionX - 1][LowestPositionY - 1] = lowest + 1.4f;
					linkX[LowestPositionX - 1][LowestPositionY - 1] = LowestPositionX;
					linkY[LowestPositionX - 1][LowestPositionY - 1] = LowestPositionY;
				}
			}
		}
		if (gLevel.isValid(LowestPositionX - 1, LowestPositionY + 1)) {
			if (closed[LowestPositionX - 1][LowestPositionY + 1] == false) { // up-left neighbour
				if (cost[LowestPositionX - 1][LowestPositionY + 1] > lowest + 1.4f) {
					cost[LowestPositionX - 1][LowestPositionY + 1] = lowest + 1.4f;
					linkX[LowestPositionX - 1][LowestPositionY + 1] = LowestPositionX;
					linkY[LowestPositionX - 1][LowestPositionY + 1] = LowestPositionY;
				}
			}
		}
		// if the current location's x and y is equal to the player location done is then equal to true, this then breaks out the for loop
		if (LowestPositionX == gTarget.PositionX() && LowestPositionY == gTarget.PositionY()) {
			done1 = true;
		}
	}
	bool done = false; //set to true when we are back at the bot position
	int nextClosedX = gTarget.PositionX(); //start of path
	int nextClosedY = gTarget.PositionY(); //start of path
	while (!done)
	{
		inPath[nextClosedX][nextClosedY] = true;
		// to convert 2d coords to 1d array format the following formula is used: (y * gridwidth + x)
		// 'push_back' pushes the given location into the vector
		pathway.push_back(nextClosedY* GRIDWIDTH + nextClosedX);
		int tmpX = nextClosedX;
		int tmpY = nextClosedY;
		nextClosedX = linkX[tmpX][tmpY];
		nextClosedY = linkY[tmpX][tmpY];
		// if the next closed grid location is equal to the bot position then done is equal to true, this breaks out the while loop
		if ((nextClosedX == bot.PositionX()) && (nextClosedY == bot.PositionY())) {
			done = true;
		}
		cDijkstra::completed = true; 
	}
	// 1d array index is set to the last element of the vector
	gAStar.FinalPath[0] = pathway.back();
}
void cAStar::BuildDiagonal(cBotBase& bot) {
	for (int i = 0; i < GRIDWIDTH; i++) {
		for (int j = 0; j < GRIDHEIGHT; j++) {
			closed[i][j] = false; //whether or not location is closed
			cost[i][j] = 1000000.0f; //cost value for each location
			linkX[i][j] = -1; //link X coord for each location
			linkY[i][j] = -1;//link Y coord for each location
			inPath[i][j] = false; //whether or not a location is in the final path
		}
	}
	cost[bot.PositionX()][bot.PositionY()] = 0; // bot position cost is set to zero
	int counter = 0;
	bool done1 = false;
	int LowestPositionX; int LowestPositionY;
	while (!done1) {
		// two lowest variables are equal to the highest costing grid location
		float lowest = 1000000.0f;
		float lowest1 = 1000000.0f;
		// for loop which loops through entire grid width 
		for (int i = 0; i < GRIDWIDTH; i++) {
			// for loop which loops through entire grid height
			for (int j = 0; j < GRIDHEIGHT; j++) {
				// diagonal distance path finding equation
				float diagonal_distance = fabs(i - gTarget.PositionX()), fabs(j - gTarget.PositionY());
				// if statement which checks that the current cost location + the heuristic is less than the lowest variable ( 1st iteration this would be 1000000.0f )
				// if statement then checks if the current grid location is closed or not, then checks if the current grid location position is valid 
				if (cost[i][j] + diagonal_distance < lowest1 && closed[i][j] == false && gLevel.isValid(i, j)) {
					// current grid location is set to two variables 'LowestPositionX' and 'LowestPositionY'
					// lowest cost is then equal to the cost of the newest position
					// lowest1 variable is equal to the cost of the newest location plus the heuristic distance
					// the second lowest variable is used to utilise the heuristic path finding
					LowestPositionX = i;
					LowestPositionY = j;
					lowest = cost[i][j];
					lowest1 = cost[i][j] + diagonal_distance;
				}
			}
		}
		// current location is then set to closed
		closed[LowestPositionX][LowestPositionY] = true;
		// following if statements check each neighbour of the new current location and adds the corresponding cost to the location 
		//(+1 for non diagonal neighbours) 
		//(+1.4 for diagonal neighbours)
		if (gLevel.isValid(LowestPositionX + 1, LowestPositionY)) {
			if (closed[LowestPositionX + 1][LowestPositionY] == false) { // right neighbour
				if (cost[LowestPositionX + 1][LowestPositionY] > lowest + 1) {
					cost[LowestPositionX + 1][LowestPositionY] = lowest + 1;
					linkX[LowestPositionX + 1][LowestPositionY] = LowestPositionX;
					linkY[LowestPositionX + 1][LowestPositionY] = LowestPositionY;
				}
			}
		}
		if (gLevel.isValid(LowestPositionX - 1, LowestPositionY)) {
			if (closed[LowestPositionX - 1][LowestPositionY] == false) { // left neighbour
				if (cost[LowestPositionX - 1][LowestPositionY] > lowest + 1) {
					cost[LowestPositionX - 1][LowestPositionY] = lowest + 1;
					linkX[LowestPositionX - 1][LowestPositionY] = LowestPositionX;
					linkY[LowestPositionX - 1][LowestPositionY] = LowestPositionY;
				}
			}
		}
		if (gLevel.isValid(LowestPositionX, LowestPositionY + 1)) {
			if (closed[LowestPositionX][LowestPositionY + 1] == false) { // up neighbour
				if (cost[LowestPositionX][LowestPositionY + 1] > lowest + 1) {
					cost[LowestPositionX][LowestPositionY + 1] = lowest + 1;
					linkX[LowestPositionX][LowestPositionY + 1] = LowestPositionX;
					linkY[LowestPositionX][LowestPositionY + 1] = LowestPositionY;
				}
			}
		}
		if (gLevel.isValid(LowestPositionX, LowestPositionY - 1)) {
			if (closed[LowestPositionX][LowestPositionY - 1] == false) { // down neighbour
				if (cost[LowestPositionX][LowestPositionY - 1] > lowest + 1) {
					cost[LowestPositionX][LowestPositionY - 1] = lowest + 1;
					linkX[LowestPositionX][LowestPositionY - 1] = LowestPositionX;
					linkY[LowestPositionX][LowestPositionY - 1] = LowestPositionY;
				}
			}
		}
		if (gLevel.isValid(LowestPositionX + 1, LowestPositionY + 1)) {
			if (closed[LowestPositionX + 1][LowestPositionY + 1] == false) { // up-right neighbour
				if (cost[LowestPositionX + 1][LowestPositionY + 1] > lowest + 1.4f) {
					cost[LowestPositionX + 1][LowestPositionY + 1] = lowest + 1.4f;
					linkX[LowestPositionX + 1][LowestPositionY + 1] = LowestPositionX;
					linkY[LowestPositionX + 1][LowestPositionY + 1] = LowestPositionY;
				}
			}
		}
		if (gLevel.isValid(LowestPositionX + 1, LowestPositionY - 1)) {
			if (closed[LowestPositionX + 1][LowestPositionY - 1] == false) { // down-right neighbour
				if (cost[LowestPositionX + 1][LowestPositionY - 1] > lowest + 1.4f) {
					cost[LowestPositionX + 1][LowestPositionY - 1] = lowest + 1.4f;
					linkX[LowestPositionX + 1][LowestPositionY - 1] = LowestPositionX;
					linkY[LowestPositionX + 1][LowestPositionY - 1] = LowestPositionY;
				}
			}
		}
		if (gLevel.isValid(LowestPositionX - 1, LowestPositionY - 1)) {
			if (closed[LowestPositionX - 1][LowestPositionY - 1] == false) { // down-left neighbour
				if (cost[LowestPositionX - 1][LowestPositionY - 1] > lowest + 1.4f) {
					cost[LowestPositionX - 1][LowestPositionY - 1] = lowest + 1.4f;
					linkX[LowestPositionX - 1][LowestPositionY - 1] = LowestPositionX;
					linkY[LowestPositionX - 1][LowestPositionY - 1] = LowestPositionY;
				}
			}
		}
		if (gLevel.isValid(LowestPositionX - 1, LowestPositionY + 1)) {
			if (closed[LowestPositionX - 1][LowestPositionY + 1] == false) { // up-left neighbour
				if (cost[LowestPositionX - 1][LowestPositionY + 1] > lowest + 1.4f) {
					cost[LowestPositionX - 1][LowestPositionY + 1] = lowest + 1.4f;
					linkX[LowestPositionX - 1][LowestPositionY + 1] = LowestPositionX;
					linkY[LowestPositionX - 1][LowestPositionY + 1] = LowestPositionY;
				}
			}
		}
		// if the current location's x and y is equal to the player location done is then equal to true, this then breaks out the for loop
		if (LowestPositionX == gTarget.PositionX() && LowestPositionY == gTarget.PositionY()) {
			done1 = true;
		}
	}
	bool done = false; //set to true when we are back at the bot position
	int nextClosedX = gTarget.PositionX(); //start of path
	int nextClosedY = gTarget.PositionY(); //start of path
	while (!done)
	{
		inPath[nextClosedX][nextClosedY] = true;
		// to convert 2d coords to 1d array format the following formula is used: (y * gridwidth + x)
		// 'push_back' pushes the given location into the vector
		pathway.push_back(nextClosedY * GRIDWIDTH + nextClosedX);
		int tmpX = nextClosedX;
		int tmpY = nextClosedY;
		nextClosedX = linkX[tmpX][tmpY];
		nextClosedY = linkY[tmpX][tmpY];
		// if the next closed grid location is equal to the bot position then done is equal to true, this breaks out the while loop
		if ((nextClosedX == bot.PositionX()) && (nextClosedY == bot.PositionY())) {
			done = true;
		}
		cDijkstra::completed = true;
	}
	// 1d array index is set to the last element of the vector
	gAStar.FinalPath[0] = pathway.back();
}
void cAStar::BuildEuclidean(cBotBase& bot) {
	for (int i = 0; i < GRIDWIDTH; i++) {
		for (int j = 0; j < GRIDHEIGHT; j++) {
			closed[i][j] = false; //whether or not location is closed
			cost[i][j] = 1000000.0f; //cost value for each location
			linkX[i][j] = -1; //link X coord for each location
			linkY[i][j] = -1;//link Y coord for each location
			inPath[i][j] = false; //whether or not a location is in the final path
		}
	}
	cost[bot.PositionX()][bot.PositionY()] = 0; // bot position cost is set to zero
	int counter = 0;
	bool done1 = false;
	int LowestPositionX; int LowestPositionY;
	while (!done1) {
		// two lowest variables are equal to the highest costing grid location
		float lowest = 1000000.0f;
		float lowest1 = 1000000.0f;
		// for loop which loops through entire grid width 
		for (int i = 0; i < GRIDWIDTH; i++) {
			// for loop which loops through entire grid height
			for (int j = 0; j < GRIDHEIGHT; j++) {
				// euclidean distance path finding equation
				float euclidean_distance = sqrt(std::pow(i - gTarget.PositionX(), 2) + std::pow(j - gTarget.PositionY(), 2));
				// if statement which checks that the current cost location + the heuristic is less than the lowest variable ( 1st iteration this would be 1000000.0f )
				// if statement then checks if the current grid location is closed or not, then checks if the current grid location position is valid 
				if (cost[i][j] + euclidean_distance < lowest1 && closed[i][j] == false && gLevel.isValid(i, j)) {
					// current grid location is set to two variables 'LowestPositionX' and 'LowestPositionY'
					// lowest cost is then equal to the cost of the newest position
					// lowest1 variable is equal to the cost of the newest location plus the heuristic distance
					// the second lowest variable is used to utilise the heuristic path finding
					LowestPositionX = i;
					LowestPositionY = j;
					lowest = cost[i][j];
					lowest1 = cost[i][j] + euclidean_distance;
				}
			}
		}
		// current location is then set to closed
		closed[LowestPositionX][LowestPositionY] = true;
		// following if statements check each neighbour of the new current location and adds the corresponding cost to the location 
		//(+1 for non diagonal neighbours) 
		//(+1.4 for diagonal neighbours)
		if (gLevel.isValid(LowestPositionX + 1, LowestPositionY)) {
			if (closed[LowestPositionX + 1][LowestPositionY] == false) { // right neighbour
				if (cost[LowestPositionX + 1][LowestPositionY] > lowest + 1) {
					cost[LowestPositionX + 1][LowestPositionY] = lowest + 1;
					linkX[LowestPositionX + 1][LowestPositionY] = LowestPositionX;
					linkY[LowestPositionX + 1][LowestPositionY] = LowestPositionY;
				}
			}
		}
		if (gLevel.isValid(LowestPositionX - 1, LowestPositionY)) {
			if (closed[LowestPositionX - 1][LowestPositionY] == false) { // left neighbour
				if (cost[LowestPositionX - 1][LowestPositionY] > lowest + 1) {
					cost[LowestPositionX - 1][LowestPositionY] = lowest + 1;
					linkX[LowestPositionX - 1][LowestPositionY] = LowestPositionX;
					linkY[LowestPositionX - 1][LowestPositionY] = LowestPositionY;
				}
			}
		}
		if (gLevel.isValid(LowestPositionX, LowestPositionY + 1)) {
			if (closed[LowestPositionX][LowestPositionY + 1] == false) { // up neighbour
				if (cost[LowestPositionX][LowestPositionY + 1] > lowest + 1) {
					cost[LowestPositionX][LowestPositionY + 1] = lowest + 1;
					linkX[LowestPositionX][LowestPositionY + 1] = LowestPositionX;
					linkY[LowestPositionX][LowestPositionY + 1] = LowestPositionY;
				}
			}
		}
		if (gLevel.isValid(LowestPositionX, LowestPositionY - 1)) {
			if (closed[LowestPositionX][LowestPositionY - 1] == false) { // down neighbour
				if (cost[LowestPositionX][LowestPositionY - 1] > lowest + 1) {
					cost[LowestPositionX][LowestPositionY - 1] = lowest + 1;
					linkX[LowestPositionX][LowestPositionY - 1] = LowestPositionX;
					linkY[LowestPositionX][LowestPositionY - 1] = LowestPositionY;
				}
			}
		}
		if (gLevel.isValid(LowestPositionX + 1, LowestPositionY + 1)) {
			if (closed[LowestPositionX + 1][LowestPositionY + 1] == false) { // up-right neighbour
				if (cost[LowestPositionX + 1][LowestPositionY + 1] > lowest + 1.4f) {
					cost[LowestPositionX + 1][LowestPositionY + 1] = lowest + 1.4f;
					linkX[LowestPositionX + 1][LowestPositionY + 1] = LowestPositionX;
					linkY[LowestPositionX + 1][LowestPositionY + 1] = LowestPositionY;
				}
			}
		}
		if (gLevel.isValid(LowestPositionX + 1, LowestPositionY - 1)) {
			if (closed[LowestPositionX + 1][LowestPositionY - 1] == false) { // down-right neighbour
				if (cost[LowestPositionX + 1][LowestPositionY - 1] > lowest + 1.4f) {
					cost[LowestPositionX + 1][LowestPositionY - 1] = lowest + 1.4f;
					linkX[LowestPositionX + 1][LowestPositionY - 1] = LowestPositionX;
					linkY[LowestPositionX + 1][LowestPositionY - 1] = LowestPositionY;
				}
			}
		}
		if (gLevel.isValid(LowestPositionX - 1, LowestPositionY - 1)) {
			if (closed[LowestPositionX - 1][LowestPositionY - 1] == false) { // down-left neighbour
				if (cost[LowestPositionX - 1][LowestPositionY - 1] > lowest + 1.4f) {
					cost[LowestPositionX - 1][LowestPositionY - 1] = lowest + 1.4f;
					linkX[LowestPositionX - 1][LowestPositionY - 1] = LowestPositionX;
					linkY[LowestPositionX - 1][LowestPositionY - 1] = LowestPositionY;
				}
			}
		}
		if (gLevel.isValid(LowestPositionX - 1, LowestPositionY + 1)) {
			if (closed[LowestPositionX - 1][LowestPositionY + 1] == false) { // up-left neighbour
				if (cost[LowestPositionX - 1][LowestPositionY + 1] > lowest + 1.4f) {
					cost[LowestPositionX - 1][LowestPositionY + 1] = lowest + 1.4f;
					linkX[LowestPositionX - 1][LowestPositionY + 1] = LowestPositionX;
					linkY[LowestPositionX - 1][LowestPositionY + 1] = LowestPositionY;
				}
			}
		}
		// if the current location's x and y is equal to the player location done is then equal to true, this then breaks out the for loop
		if (LowestPositionX == gTarget.PositionX() && LowestPositionY == gTarget.PositionY()) {
			done1 = true;
		}
	}
	bool done = false; //set to true when we are back at the bot position
	int nextClosedX = gTarget.PositionX(); //start of path
	int nextClosedY = gTarget.PositionY(); //start of path
	while (!done)
	{
		inPath[nextClosedX][nextClosedY] = true;
		// to convert 2d coords to 1d array format the following formula is used: (y * gridwidth + x)
		// 'push_back' pushes the given location into the vector
		pathway.push_back(nextClosedY * GRIDWIDTH + nextClosedX);
		int tmpX = nextClosedX;
		int tmpY = nextClosedY;
		nextClosedX = linkX[tmpX][tmpY];
		nextClosedY = linkY[tmpX][tmpY];
		// if the next closed grid location is equal to the bot position then done is equal to true, this breaks out the while loop
		if ((nextClosedX == bot.PositionX()) && (nextClosedY == bot.PositionY())) {
			done = true;
		}
		cDijkstra::completed = true;
	}
	// 1d array index is set to the last element of the vector
	gAStar.FinalPath[0] = pathway.back();
}
cAStar gAStar;