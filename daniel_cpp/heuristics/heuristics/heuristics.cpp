// heuristics.cpp : Defines the entry point for the console application.
//
#include "GameState.h"
#include "heuristics.h"
#include "daniel_timer.h"
#include <iostream>
int main()
{
	GameState gs;
	Timer t;
	gs.addSnakeTest(0);
	t.start();
	gs.runDijkstra(0);
	unsigned long time = t.millisecondsPassed();
	std::cout << time  << std::endl;
	gs.printDijkstra(0);
	//while (true);
    return 0;
}

