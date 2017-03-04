// heuristics.cpp : Defines the entry point for the console application.
//
#include "GameState.h"
#include "heuristics.h"
#include "daniel_timer.h"
#include <iostream>
#include <sstream>


void test() {
	GameState *gs;
	gs = GameState::buildFromCin();
	Timer t;
	t.start();
	unsigned long time = t.millisecondsPassed();
	std::cout << time << std::endl;
	gs->printDijkstra(0);
}


int main()
{
	test();
    return 0;
}

