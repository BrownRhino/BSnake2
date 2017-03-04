#include <cmath>

int* minimax(int max_depth, int current_depth)
{
	int* scoreandmove = new int[2];
	int* temp = new int;
//if((board.gameOver())||(current_depth==max_depth))
/*	if(current_depth==max_depth)
	{
		scoreandmove[0]=1;//scoreandmove[0]=board.evaluate() and scoreandmove[1]= -1; return scoreandmove
		scoreandmove[1]=2;
		return scoreandmove;
	}
	
		int* scoreandmove = new int[2];
	if(G.isGameOver() || current_depth==max_depth)
	{
		//What is the current board rating
		scoreandmove[0]=board_evaluate();
		
		//What is the current scoring scheme
		scoreandmove[1]=-1;
	}
	
	int* best_score = &scoreandmove[0]
	int* best_move = &scoreandmove[1]
	
	
	*best_score = std::numeric_limits<int>::max();
	*best_move = -1;
	std::vector<GameState> possible_moves=board.getMoves();
	
	for(int move = 0; move < size(possible_moves); move++)
	{
		
	}
*/	
	delete[] scoreandmove;
	return temp;
	
}
int main()
{
	int* r = minimax(1,1);
	delete r;
}