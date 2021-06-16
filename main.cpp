#include<windows.h>
#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include "board.h"
#include "genetic.h"
#include <vector>

using namespace std;

#define BOARD_SIZE 8
#define BOARD_NUMBER 128
#define QUEEN_NUMBER 8
#define ITERATIONS 10000

void PrintBoard(BoardManifest* board){
	for(short i = 0; i < BOARD_SIZE; i++){
		for(short j = 0; j < BOARD_SIZE; j++){
			if(board->queens[i] == j)
				cout <<  "1" << " ";
			else
				cout << "0" << " ";
		}
		cout << "\n";
	}
}

int main(){
	srand(time(NULL));

	BoardManifest** boards = (BoardManifest**)malloc(sizeof(BoardManifest*)*BOARD_NUMBER);
	vector<BoardManifest**> board_iterations;
	
	cout << "Eight Queen alg in progression!" << "\n\n";

	int current_iteration = 0;

	for(int board_index = 0; board_index < BOARD_NUMBER; board_index++){
		boards[board_index] = CreateRandomBoard(BOARD_SIZE);
		CalculateQueenPath(boards[board_index], BOARD_SIZE);
	}

	board_iterations.push_back(boards);

	while(current_iteration < ITERATIONS){
		if(boards[0]->collision_number == 0) break;

		BoardManifest** new_boards = (BoardManifest**)malloc(sizeof(BoardManifest*)*BOARD_NUMBER);
		for(int board_index = 0; board_index < BOARD_NUMBER; board_index++){
			new_boards[board_index] = CreateBlankBoard(BOARD_SIZE);
		}

		for(int i = 0; i < BOARD_NUMBER;){
			if(i < BOARD_NUMBER / 2){
				for(int x= 0; x < BOARD_SIZE; x++){
					new_boards[i]->queens[x] = boards[i]->queens[x];
					//new_boards[i] = CreateRandomBoard(BOARD_SIZE);
				}
				new_boards[i]->collision_number = boards[i]->collision_number;
				i++;
			}else{
				new_boards[i] = CreateNextGeneration(boards[i], boards[i+1], BOARD_SIZE);
				new_boards[i+1] = CreateNextGeneration(boards[i+1], boards[i], BOARD_SIZE);
				i+=2;
			}
		}

		sort(new_boards, new_boards + BOARD_NUMBER, BoardManifest::CompareCollisionManifest);
		board_iterations.push_back(new_boards);
		boards = new_boards;

		current_iteration++;
	}


	auto best_boards = board_iterations.back();
	
	PrintBoard(best_boards[0]);
	cout << "Fitness: " << best_boards[0]->collision_number << "\n";
	cout << "Generatios: " << current_iteration;

	/*
	for(int board_index = BOARD_NUMBER-1; board_index >= 0; board_index--){
		PrintBoard(best_boards[board_index]);
		cout << "Fitness: " << best_boards[board_index]->collision_number << "\n";
		cout << "---------------\n";
	}
	cout << "Generatios: " << current_iteration;
	
	for(auto cur_board : board_iterations){
		for(int board_index = 0; board_index < BOARD_NUMBER; board_index++){
			PrintBoard(cur_board[board_index]);
			cout << "Fitness: " << cur_board[board_index]->collision_number << "\n";
			cout << "---------------\n";
		}
	}
	*/
	
}


