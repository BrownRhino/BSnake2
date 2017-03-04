#pragma once

#include "GameState.h"

class GameState;

namespace SnakeHeuristics
{
	int calcHeuristic(GameState &gs);

	int hungry(GameState& gs);

	int opertunisticEat(GameState &gs);

	int relativeAreas(GameState& gs);

	int ourArea(GameState& gs);

	int enemyDeaths(GameState& gs);

	int gameLoss(GameState& gs);

	int gameWin(GameState& gs);
}

