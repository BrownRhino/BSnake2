#include "Meow_Mix.h"

Node::Node(void)
{
	
}

Node::Node(const int& x)
{
	if(x==0)
		parent=1, leaf=0;
	else
		leaf=1, parent=0;
	
}

Node::Node(const int& x,const int& val, const int& m)
{
	if(x==0)
		parent=1, leaf=0;
	else
		leaf=1, parent=0;
	if(leaf)
		value=val;
	move=m;
}

void Node::set_move(const int& m)
{
	move=m;
}

int Node::get_move()
{
	return move;
}

void Node::set_child(Node n)
{
	children.push_back(n);
}

std::vector<Node> Node::get_children() const
{
	return children;
}

		
void Node::set_id(unsigned i)
{
	id=i;
}

unsigned int Node::get_id() const
{
	return id;
}
bool Node::set_value(unsigned a)
{
	if(leaf)
		value = a;
	
}

unsigned Node::get_value(void) const
{
	return value;
}

bool Node::is_parent() const
{
	return parent;
}

bool Node::is_leaf() const
{
	return leaf;
}


GameState::GameState()
{
	
}

GameState::GameState(const Node& n, const int& p)
{
	root=n;
	player=p;
}

void GameState::set_root(const Node& n)
{
	root=n;
}

const void GameState::set_children(const GameState& G) 
{
	children.push_back(G);
}

unsigned GameState::get_id() const
{
	return root.get_id();
}

std::vector<GameState> GameState::getMoves()const
{
	return children;
}
int GameState::get_move()
{
	return root.get_move();
}
int GameState::evaluate() const
{
	return root.get_value();
}
int GameState::currentPlayer() const
{
	return player;
}
int GameState::isGameOver() const
{
	return root.is_leaf();
}

