#pragma once

#include "GameState.h"
#include <vector>
class Snake
{
public:
	Snake();
	~Snake();

	void moveSnake(Direction dir) {};

	int m_id;
	int m_health;
	int m_length;
	bool m_isAlive;
	std::vector<GridPoint> m_snake;

};

