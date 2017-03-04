// heuristics.cpp : Defines the entry point for the console application.
//
#include "GameState.h"
#include "heuristics.h"
#include "daniel_timer.h"
#include <iostream>
#include <sstream>


void test() {
	Timer t;
	t.start();
	GameState *gs;
	gs = GameState::buildFromCin();
	unsigned long time = t.millisecondsPassed();
	std::cout << time << std::endl;
	gs->printDijkstra(0);
	gs->printTTL();
	gs->printMoves(0);
	for (int i = 0; i < 4; i++) {
		std::cout << gs->calcAccessibleArea(i, 0) << std::endl;
	}
	gs->printVoronoi();
	t.start();
	//Gets the game states for us.
	volatile auto results = gs->getMoves(true);
	time = t.millisecondsPassed();
	//Gets the game states for enemy moves.
	volatile auto results2 = gs->getMoves(false);
	unsigned long time2 = t.millisecondsPassed();
	std::cout << time << " " << time2 << std::endl;
	results->at(0).printDijkstra(0);
	std::cout << "---------------" << std::endl;
	for (int i = 0; i < results2->size(); i++) {
		results2->at(i).printDijkstra(0);
		std::cout << std::endl;
	}

	delete results;
	delete results2;
}


int main()
{
	test();
    return 0;
}

