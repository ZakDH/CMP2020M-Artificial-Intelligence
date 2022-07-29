#include "bots.h"
#include "stdlib.h"
void cBotAStar::ChooseNextGridPosition() // program loops through this class every bot move
{
	bool done = false;
	while (!done) {
		// checks to see if the final path array is not empty
		if (gAStar.FinalPath[0] != 0) {
			// to get the x coordinate the final path index eg: 830 is '%' by 40 ( 40 being the gridwidth or gridheight
			// to get the y coordinate the path index is divided by 40
			// after this the x and y coordinates are given which can then be used to set the next bot location
			int x = gAStar.FinalPath[0] % 40;
			int y = gAStar.FinalPath[0] / 40;
			// done is equal to the next bot location, x is the worked out x location and the same with the y location
			done = SetNext((x), (y), gLevel);	
			// the last element from the vector is removed from the vector, this prevents the bot class from reading the same grid location every time
			gAStar.pathway.pop_back();
			// final path index is then set to the new last element in the vector 
			gAStar.FinalPath[0] = gAStar.pathway.back();
		}
		// if array is empty then done is equal to true
		// this prevents the program from trashing when the array is empty
		else {
			done = true;
		}
	}
}