#include "board.h"
#include <iostream>
#include <tuple>

using namespace std;

BoardManifest* CreateNextGeneration(BoardManifest* father, BoardManifest* mother, int board_size){
	/*
	* Here how it goes: We take the first 4 of the father and last 4 of the mother for the first child
	*					Then we swap the father and mother places, and do it again
	*			FATHER				MOTHER
	*			[1,6,5,3,7,2,4,0] 	[2,5,4,7,1,3,6,0]
	* Child One [1,6,5,3,                    1,3,6,0]	
	* Child Two	[        7,2,4,0     2,5,4,7        ]
	*			[1,6,5,3,7,2,4,0]   [2,5,4,7,1,3,6,0]
	*
	* Then we apply mutations to swap two queens
	*/

	BoardManifest* new_child = CreateBlankBoard(board_size);
	new_child->queens[0] = father->queens[0];
	new_child->queens[1] = father->queens[1];
	new_child->queens[2] = father->queens[2];
	new_child->queens[3] = father->queens[3];
	new_child->queens[4] = mother->queens[4];
	new_child->queens[5] = mother->queens[5];
	new_child->queens[6] = mother->queens[6];
	new_child->queens[7] = mother->queens[7];

	int mutate = rand() % 101 > 70;
	if(mutate){
		int mutate_a = rand() % board_size;
		int mutate_b = rand() % board_size;
		while(mutate_a == mutate_b)
			mutate_b = rand() % board_size;

		auto tmp = new_child->queens[mutate_a];
		new_child->queens[mutate_a] = new_child->queens[mutate_b];
		new_child->queens[mutate_b] = tmp;
	}

	CalculateQueenPath(new_child, board_size);
	return new_child;
}