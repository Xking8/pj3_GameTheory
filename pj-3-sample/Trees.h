#include <iostream>
#include <string.h>
#include "type.h"
#include "board2x3.h"
using namespace std;

class Tree;

class Node {
friend class Tree;
public:
	Node() {
		value = -1;
		reward = 0;
	}
	Node(board2x3& g, state_type t, int r = 0 ) {
		//cout<<"s="<<s<<endl;
		game = g;
		//strcpy(state,s);
		state[0] = game(0);state[1] = game(1);
		state[2] = game(2);state[3] = game(3);
		state[4] = game(4);state[5] = game(5);

		//cout<<"state="<<state<<endl;
		type = t;
		child_count = 0;
		child_amount = 0;
		reward = r;
		if (type.t != state_type::illegal)
			value = 0;
		else
			value = -1;
		
		//init all child to null
	}
	void print_state()
	{
		for (int i=0;i<6;i++)
		{
			cout<<state[i]<<" ";
		}
		cout<<endl;
	}
//private:
	int state[6];
	state_type type;
	Node* child[12];//beforeNode up to 4 childrem,afterNode up to 12 children
	int child_count;
	int child_amount;
	double value;
	board2x3 game;
	int reward;

};

class Tree {
public:
	Tree() {
		root = new Node();
		for (int i = 0; i<12; i++)
		{
			root->child[i] = NULL;
		}
		root->child_count = 1;
		root->child_amount = 1;
		cout<<"finish contruct"<<endl;
	}
	void expectimax_traversal(double [][13][13][13][13][13][13]);	
	void expectimax_traversal(Node*,double [][13][13][13][13][13][13]);	
//private:
	Node* root;
};
