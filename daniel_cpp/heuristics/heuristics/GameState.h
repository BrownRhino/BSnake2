#pragma once


#include <vector>
#include "Snake.h"

#define MAX_X 40
#define MAX_Y 40
#define MAX_SNAKES 10

enum Direction { UP, DOWN, RIGHT, LEFT };

struct GridPoint {
public:
	GridPoint() : x(0), y(0) {}
	GridPoint(uint8_t newX, uint8_t newY) : x(newX), y(newY) {}
	uint8_t x = 0;
	uint8_t y = 0;
};

class GameState
{
public:
	GameState();
	~GameState();

	void buildFromCin();

	void getMovesForSnake(int snake);
	void moveSnake(int snake, Direction direction);
	void getPossibleMoves(int *snakes, Direction* directions);

	void runDijkstra(int snake);
	
	int calcAccessibleArea(int snake, int turnFudgeFactor);
	int distanceToClosestFood(int snake);

	void printDijkstra(int snake);

	void addSnakeTest(int snake);


private:
	uint8_t m_xSize = MAX_X;
	uint8_t m_ySize = MAX_Y;

	uint8_t m_numSnakes = MAX_SNAKES;

	bool checkIfKilled(const Snake & snake);
	void updateSnakes();

	Snake m_snakes[MAX_SNAKES];

	int m_costs[MAX_X][MAX_Y];
	GridPoint m_dijkstraPrev[MAX_SNAKES][MAX_X][MAX_Y];
	int m_dijkstraNumMoves[MAX_SNAKES][MAX_X][MAX_Y];
	int m_dijkstraCosts[MAX_SNAKES][MAX_X][MAX_Y];
	
};
