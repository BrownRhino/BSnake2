#pragma once


#include <vector>
#include "Snake.h"
#include "misc.h"
#include <iostream>

class GameState
{
public:
	GameState();
	static GameState *buildFromCin();
	GameState( GameState &gs);
	~GameState();

	std::vector<GameState> getMoves(bool ourSnake);
	
	int calcAccessibleArea(int snake, int turnFudgeFactor);
	int distanceToClosestFood(int snake);

	void printDijkstra(int snake);

	void addSnakeTest(int snake);


private:
	int m_xSize = MAX_X;
	int m_ySize = MAX_Y;
	GameState *m_previousState;

	int m_numSnakes = MAX_SNAKES;
	std::vector<Snake> m_snakes = std::vector<Snake>(MAX_SNAKES);
	int m_ttl[MAX_X][MAX_Y];

	std::vector<GridPoint> m_food;

	int m_costs[MAX_X][MAX_Y];
	GridPoint m_dijkstraPrev[MAX_SNAKES][MAX_X][MAX_Y];
	int m_dijkstraNumMoves[MAX_SNAKES][MAX_X][MAX_Y];
	int m_dijkstraCosts[MAX_SNAKES][MAX_X][MAX_Y];

	void runDijkstra(int snake);

	bool checkIfKilled( Snake snake);
	void updateFood(Snake &snake);
	void updateSnakes();
	void moveSnakes(std::vector<Direction> moves);

	std::vector<Direction> checkDirections(int snakeNum);
	std::vector< std::vector<Direction>> pickMoves(int snake);	
};
