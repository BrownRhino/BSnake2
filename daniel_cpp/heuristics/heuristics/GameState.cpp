#include "GameState.h"

#include <queue>
#include <algorithm>
#include <locale.h>
#include <wchar.h>
#include <stdio.h>
#include <stddef.h>
#include <iostream>
#include <unordered_set>

GameState::GameState()
{
}


GameState::~GameState()
{
}


void GameState::buildFromCin()
{
}

class DijkstraCompare {
public:
	bool operator()(const std::pair< int, GridPoint> a, const std::pair< int, GridPoint> b) {
		return a.first > b.first;
	}
};

inline int hashGridPoint(GridPoint p) {
	return p.x << 8 | p.y;
}


const int8_t directionsX[] = { -1,0,1,0 };
const int8_t directionsY[] = { 0,1,0,-1 };

void GameState::runDijkstra(int snake)
{
	bool visited[MAX_X << 8 | MAX_Y] = { 0 };
	std::priority_queue< std::pair< int, GridPoint>,
		std::vector< std::pair< int, GridPoint>>,
		DijkstraCompare> queue;
	//std::unordered_set< int > set;

	for (int i = 0; i < MAX_X; i++) {
		for (int j = 0; j < MAX_Y; j++) {
			m_dijkstraCosts[snake][i][j] = INT_MAX;
			m_dijkstraPrev[snake][i][j] = GridPoint(255, 255);
			m_dijkstraNumMoves[snake][i][j] = INT_MAX;
		}
	}

	GridPoint startPoint;
	startPoint = m_snakes[snake][0];
	queue.push(std::pair< int, GridPoint>(0, startPoint));
	m_dijkstraCosts[snake][startPoint.x][startPoint.y] = 0;
	//set.insert(hashGridPoint(startPoint.start));

	while (!queue.empty()) {
		auto queueNode = queue.top();
		queue.pop();

		//Pop edge from u to v.
		int currentCost = queueNode.first;
		GridPoint currentPoint = queueNode.second;
		uint8_t x = currentPoint.x;
		uint8_t y = currentPoint.y;

		//int additionalCost = m_costs[x][y];
		//int currentCost = oldCost + additionalCost;

		//set.erase(hashGridPoint(v));

		//Check if this is first visit to v.
		if (!visited[hashGridPoint(currentPoint)]) {
			visited[hashGridPoint(currentPoint)] = true;
			//First visit, always run.
			//m_dijkstraCosts[snake][x][y] = currentCost;
			//m_dijkstraPrev[snake][x][y] = u;

			//Check all neighbours
			for (int d = 0; d < 4; d++) {
				uint8_t newX = x + directionsX[d];
				uint8_t newY = y + directionsY[d];
				GridPoint nextPoint(newX, newY);
				//set.count(hashGridPoint(newV)) == 0 &&
				if (newX < m_xSize&&newY < m_ySize) {
					//Valid point.
					int newCost = currentCost + m_costs[newX][newY];
					if (!visited[hashGridPoint(nextPoint)] && newCost < m_dijkstraCosts[snake][newX][newY]) {
						m_dijkstraPrev[snake][newX][newY] = currentPoint;
						m_dijkstraCosts[snake][newX][newY] = newCost;
						queue.push(std::pair< int, GridPoint>(newCost, nextPoint));
					}
				}
			}
		}
	}
}

int GameState::calcAccessibleArea(int snake, int turnFudgeFactor)
{

}

void GameState::printDijkstra(int snake)
{
	for (int y = 0; y < m_ySize; y++) {
		for (int x = 0; x < m_ySize; x++) {
			int deltaX = m_dijkstraPrev[snake][x][y].x - x;
			int deltaY = m_dijkstraPrev[snake][x][y].y - y;
			int cost = m_costs[x][y];
			wchar_t bg;
			wchar_t arrow;
			if (cost < 2) {
				bg = ' ';
			}
			else if (cost < 10) {
				bg = '1';
			}
			else if (cost < 100) {
				bg = '2';
			}
			else if (cost < 1000) {
				bg = '3';
			}
			else {
				bg = '4';
			}

			if (deltaY == -1) {
				arrow = '^';
			}
			else if (deltaY == 1) {
				arrow = 'v';
			}
			else if (deltaX == -1) {
				arrow = '<';
			}
			else if (deltaX == 1) {
				arrow = '>';
			}
			else {
				arrow = '*';
			}
			std::wcout << bg << arrow << bg;
		}
		std::wcout << std::endl;
	}
}

void GameState::addSnakeTest(int snake)
{
	//memset(m_costs, 1, sizeof m_costs);
	for (int i = 0; i < MAX_X; i++) {
		for (int j = 0; j < MAX_Y; j++) {
			m_costs[i][j] = 1;
		}
	}
	m_snakes[snake].push_back(GridPoint(0, 0));
}

bool GameState::checkIfKilled(const Snake &snake) {
	for (int i = 0; i < MAX_SNAKES; i++) {
		Snake &otherSnake = m_snakes[i];
		if (otherSnake.m_isAlive) {
			GridPoint head = snake.m_snake[0];
			for (int j = 0; j < otherSnake.m_snake.size(); j++) {
				GridPoint bodySegment = otherSnake.m_snake[j];
				if (bodySegment.x == head.x && bodySegment.y == head.y) {
					if (otherSnake.m_length >= snake.m_length) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

void GameState::updateSnakes()
{
	bool nowDead[MAX_SNAKES] = { 0 };
	for (int i = 0; i < MAX_SNAKES; i++) {
		Snake &snake = m_snakes[i];
		if (snake.m_isAlive) {

		}
	}
}
