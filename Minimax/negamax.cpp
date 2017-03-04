#include <iostream>
#include <limits>
#include "Meow_Mix.h"
#include <algorithm>

const int MIN_VAL = -1000000;
const int MAX_VAL =  1000000;

using namespace std;
//negamax(const int& i);
//int* negamax(const GameState& G, int max_depth, int current_depth, bool player)
void negamax(const int& i)
{
	std::cout<<"i is "<<i;
/*	
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
	
	
	*best_score = std::numeric_limits<int>::min();
	*best_move = -1;
	std::vector<GameState> possible_moves=board.getMoves();
	
	int recused_score;
	int current_move;
	
	int* recursed_score_move;
	int current_score;
	
	for(int move = 0; move < possible_moves.size(); move++)
	{
		recursed_score_move = negamax(possible_moves[move], max_depth, current_depth-1, !player);
		currentscore = -recursed_score_move[0];
		
		if(current_score > (*best_score))
		{
			*best_score = current_score;
			*best_move=possible_moves[move].get_move();
		}
		delete[2] recursed_score_move;
	}
	return scoreandmove;
*/
	
}

int* negamax(const GameState& G, int max_depth, int current_depth, bool player)
{
	int* scoreandmove = new int[2];
	
//	cout<<"In depth "<<current_depth<<".  Is the game over? "<<G.isGameOver()<<endl;
//	cout<<"Current Node ID is "<<G.get_id()<<endl;
	
	if(G.isGameOver() || current_depth==max_depth)
	{
//		cout<<"WE'RE AT A LEAF BOARD?"<<endl;
		//What is the current board rating
		scoreandmove[0]=G.evaluate();
		
		//What is the current scoring scheme
		scoreandmove[1]=-1;
		return scoreandmove;
	}
	
	int* best_score = &scoreandmove[0];
	int* best_move = &scoreandmove[1];
	
	
	*best_score = MIN_VAL;
	*best_move = -1;
	std::vector<GameState> possible_moves=G.getMoves();
	
//	int recused_score;
//	int current_move;
	
	int* recursed_score_move;
	int current_score;
	
	
//	cout<<"Number of Possible Moves is "<<G.getMoves().size();
//	for(int move = 0; move < G.getMoves().size(); move++)
//	{	
//		cout<<endl<<"IDs of the possible moves "<<G.getMoves()[move].get_id();
//	}
//	cout<<endl<<endl;
	
	for(int move = 0; move < possible_moves.size(); move++)
	{
		recursed_score_move = negamax(possible_moves[move], max_depth, current_depth+1, !player);
		current_score = -recursed_score_move[0];
		
		if(current_score > (*best_score))
		{
			*best_score = current_score;
			*best_move=possible_moves[move].get_move();
		}
		delete[] recursed_score_move;
	}
	return scoreandmove;

	
}



int* abNegamax(const GameState& G, int max_depth, int current_depth, int alpha, int beta)
{
	int* scoreandmove = new int[2];
	
	if(G.isGameOver() || current_depth==max_depth)
	{
		scoreandmove[0]=G.evaluate();
		scoreandmove[1]=-1;
		return scoreandmove;
	}
	
	int* best_score = &scoreandmove[0];
	int* best_move = &scoreandmove[1];
	
	
	*best_score = std::numeric_limits<int>::min();
	*best_move = -1;
	std::vector<GameState> possible_moves=G.getMoves();
	
	int* recursed_score_move;
	int current_score;
	
	for(int move = 0; move < possible_moves.size(); move++)
	{
		recursed_score_move = abNegamax(possible_moves[move], max_depth, current_depth+1, -beta, -(std::max(alpha,(*best_score))) );
		current_score = -recursed_score_move[0];
		
		if(current_score > (*best_score))
		{
			*best_score = current_score;
			*best_move=possible_moves[move].get_move();
		}
		delete[] recursed_score_move;
		if(*best_score >= beta)
		{
			cout<<"best score is "<<*best_score<<" which is higher than beta="<<beta<<" so no need to search node "<<possible_moves[1].get_id()<<endl;
			return scoreandmove;	
		}
	}
	return scoreandmove;	
}


int main()
{
	negamax(2);
	int a = std::numeric_limits<int>::max();
	int b = std::numeric_limits<int>::min();
	std::cout<<"Max integer value is "<<a<<endl;
	std::cout<<"Min integer value is "<<b<<endl;
	
	Node test (1);
	cout<<"Parent?  "<<test.is_parent()<<endl<<".  Leaf? "<<test.is_leaf()<<endl;
	test.set_id(100);
	cout<<"id? "<<test.get_id()<<endl;

	Node tree[7] = {{0,1,2},{0,2,3},{0,3,2},{1,100,3},{1,50,2},{1,23,3},{1,3,2}};
	for(int i = 0; i<7; i++)
		cout<<"Node["<<i<<"] = "<<tree[i].is_parent()<<", "<<tree[i].get_value()<<", "<<tree[i].get_move()<<endl;	
	tree[0].set_id(0);
	tree[1].set_id(1);
	tree[2].set_id(2);
	tree[3].set_id(3);
	tree[4].set_id(4);
	tree[5].set_id(5);
	tree[6].set_id(6);
	GameState combo[7]={{tree[0],0},{tree[1],1},{tree[2],1},{tree[3],0},{tree[4],0},{tree[5],0},{tree[6],0}};
	vector<Node> kids0=tree[0].get_children();
	
	combo[2].set_children(combo[5]);
	combo[2].set_children(combo[6]);
	combo[1].set_children(combo[3]);
	combo[1].set_children(combo[4]);
	combo[0].set_children(combo[1]);
	combo[0].set_children(combo[2]);
		
	
	(combo[0].getMoves())[0].set_children(combo[3]);
	(combo[0].getMoves())[0].set_children(combo[4]);
	
	combo[0].getMoves()[1].set_children(combo[5]);
	combo[0].getMoves()[1].set_children(combo[6]);
	
	int meow;
	vector<GameState> tmp;
	
	for(int j=0; j<3;j++)
	{
		cout<<"Node "<<combo[j].get_id()<<"'s children are as follows:\n";
		tmp= combo[j].getMoves();
		for(int i=0; i<(tmp.size()); i++)
		{
			meow=tmp[i].evaluate();
			cout<<"Kid "<<i<<" is "<<meow<<"\t";
		}
		cout<<endl<<endl;
	}

	
	tmp = (combo[0].getMoves())[0].getMoves();
	cout<<(combo[0].getMoves())[0].get_id()<<" has "<<tmp.size()<<" children!\n";
	
	cout<<(combo[1].get_id())<<" has "<<combo[1].getMoves().size()<<" children\n";
	
/*	int* hope;
	hope=negamax(combo[0], 100, 0, 0);
	cout<<"Best Score is "<<hope[0]<<".\tBest Move is "<<hope[1]<<".\n";
	delete[] hope;
*/	
	int* hope;
	hope=abNegamax(combo[0], 100, 0, MIN_VAL, MAX_VAL);
	cout<<"Best Score is "<<hope[0]<<".\tBest Move is "<<hope[1]<<".\n";
	delete[] hope;
}