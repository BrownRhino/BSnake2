#ifndef MEOW_MIX_H
#define MEOW_MIX_H

#include <vector>

class Node
{
	unsigned id;
	bool parent;
	bool leaf;
	unsigned value;
	std::vector<Node> children;
	unsigned number_of_kids;
	int move;
	
	public:
		Node();
		Node(const int&);
		Node(const int&,const int&,const int& move);
		void set_move(const int&);
		int get_move();
		void set_child(Node);
		std::vector<Node> get_children()const;
		void set_id(unsigned int);
		unsigned get_id()const;
		bool set_value(unsigned);
		unsigned get_value(void) const;
		bool is_leaf() const;
		bool is_parent() const;
};



class GameState
{
	Node root;
	int player;
	std::vector<GameState> children;
	public:
		GameState();
		GameState(const Node&, const int&);
		unsigned get_id() const;
		int get_move();
		void set_root(const Node& n);
		void const set_children(const GameState&);
		std::vector<GameState> getMoves() const;
		void makeMove(int) const;
		int evaluate() const;
		int currentPlayer() const;
		int isGameOver() const;
};


#endif