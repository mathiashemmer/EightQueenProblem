#pragma once

#include <stdlib.h>
#include <cmath>

struct BoardManifest
{
	short* queens;
	short collision_number;

	static bool CompareCollisionManifest(BoardManifest const* a, BoardManifest const* b){
		return a->collision_number < b->collision_number;
	}
};

BoardManifest* CreateBlankBoard(int board_size){
	BoardManifest* new_board = (BoardManifest*)malloc(sizeof(BoardManifest*));
	new_board->queens = (short*)malloc(sizeof(short)*board_size);
	new_board->collision_number = 0;

	for(int i = 0; i < board_size; i++)
		new_board->queens[i] = 0;

	return new_board;
}

BoardManifest* CreateRandomBoard(int board_size){
	BoardManifest* board_manifest = CreateBlankBoard(board_size);

	for(int i = 0; i < board_size; i++){
		int queen_index = rand() % board_size;
		board_manifest->queens[i] = queen_index;
	}
	return board_manifest;
}

void CalculateQueenPath(BoardManifest* board_manifest, int board_size){
	for(short queen_index = 0; queen_index < board_size; queen_index++){
		short queen_y = board_manifest->queens[queen_index];
		short queen_x = queen_index;

		for(int x = 0; x < board_size; x++){
			if(x == queen_index) 
				continue; //Skip the current queen;

			// Get the y index of each queen, and compare with the current queen y index
			if(board_manifest->queens[x] == queen_y) 
				board_manifest->collision_number++;
			
			if(std::abs(queen_x - x) == std::abs(queen_y -board_manifest->queens[x]))
				board_manifest->collision_number++;
		}
	}
}