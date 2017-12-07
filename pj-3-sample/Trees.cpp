#include <iostream>
#include "Trees.h"
#include "board2x3.h"
#include "action2x3.h"
#include "type.h"
#include <limits.h>

using namespace std;
int count=0;
bool has_trans(board2x3 b, double result[][13][13][13][13][13][13], state_type ty)
{
	int b_a = 0;

	if ( ty.t== state_type::before )
	{
		b_a = 0;
	}
	if ( ty.t== state_type::after )
	{
		b_a = 1;
	}
	
	if( result[b_a][b(0)][b(1)][b(2)][b(3)][b(4)][b(5)]!=-1000 ||result[b_a][b(3)][b(4)][b(5)][b(0)][b(1)][b(2)]!=-1000 || result[b_a][b(2)][b(1)][b(0)][b(5)][b(4)][b(3)]!=-1000 ||result[b_a][b(5)][b(4)][b(3)][b(2)][b(1)][b(0)]!=-1000 )
		//as only as one teamate has value
	{
		//count++;
		return true;
	}


	return false;
}
void Tree::expectimax_traversal(double result[][13][13][13][13][13][13] )
{
	
	for(int a=0;a<2;a++)
	for(int b=0;b<13;b++)
	for(int c=0;c<13;c++)
	for(int d=0;d<13;d++)
	for(int e=0;e<13;e++)
	for(int f=0;f<13;f++)
	for(int g=0;g<13;g++)
		//cout<<result[a][b][c][d][e][f][g]<<" ";
		result[a][b][c][d][e][f][g]=-1000;
	
	expectimax_traversal(root->child[0],result);
}
void Tree::expectimax_traversal(Node* CurNode, double result[][13][13][13][13][13][13]) {
	//expectimax_traversal(CurNode->child[0]);
	cout<<"**********"<<CurNode->type<<"***********************************\n"<<CurNode->game<<endl;
	cout<<"CurNode child count"<<CurNode->child_count<<" CurNode value="<<CurNode->value<<endl;
	//cout<<"start expectimax:"<<CurNode->state<<endl;
	CurNode->print_state();
	//CurNode->game = game;

	//if is before state, L1, or L2
	//state_type bstate = state_type::illegal
	if(CurNode->type.t == state_type::illegal)
	{
		for(int i=0; i<2; i++)
			for (int j=0; j<6; j++)
			{
				board2x3 child_game = CurNode->game;
				action move = action::place(i+1,j);
				if(move.apply(child_game)!=-1)
				{
					
					state_type ty = state_type::before;
					if(child_game.illegal())
						ty = state_type::illegal;


					if (has_trans(child_game,result,ty))
						continue;
					CurNode->child[CurNode->child_count] = new Node(child_game, ty); 
					CurNode->child_count++;
					CurNode->child_amount++;
					cout<<"illegal_state place: "<<i<<j<<endl;//"\n"<<child_game<<CurNode->game<<CurNode->child[CurNode->child_count-1]<<endl;





					expectimax_traversal(CurNode->child[CurNode->child_count-1],result);
				}
				//game = CurNode->game;
			}
			result[0][CurNode->game(0)][CurNode->game(1)][CurNode->game(2)][CurNode->game(3)][CurNode->game(4)][CurNode->game(5)]=-1;
	}

	if(CurNode->type.t == state_type::before)
	{
		for(int i=0; i<4; i++) {
			board2x3 child_game = CurNode->game;
			action move = action::move(i);
			//cout<<"debug: before move child = \n"<<child_game<<"////////"<<endl;
			int reward = move.apply(child_game);
			if(reward != -1)//or if(reward>0)
			{
				
				state_type ty = state_type::after;
				//if(game.illegal())
				//	ty = state_type::illegal;
				if (has_trans(child_game,result,ty))
					continue;
				CurNode->child[CurNode->child_count] = new Node(child_game, ty, reward); 
				CurNode->child_count++;
				CurNode->child_amount++;
				cout<<"before_state move: "<<i<<" reward:"<<reward<<endl;//"\n"<<game<<endl;
				expectimax_traversal(CurNode->child[CurNode->child_count-1],result);
			}
			//game = CurNode->game;
		}
		//do max to calculate CurNode->value
		int max = 0;
		for(int i=0; i<CurNode->child_amount; i++) {
			int child_value = CurNode->child[i]->value + CurNode->child[i]->reward;
			if(max<child_value)
				max = child_value;
			
		}
		CurNode->value = max;
		result[0][CurNode->game(0)][CurNode->game(1)][CurNode->game(2)][CurNode->game(3)][CurNode->game(4)][CurNode->game(5)]=CurNode->value;
		cout<<"This before value="<<CurNode->value<<endl;
	}
	if(CurNode->type.t == state_type::after)
	{
		cout<<"it's afterstate... this reward is "<<CurNode->reward<<endl;
		/*
		for(int i=0; i<2; i++)
			for (int j=0; j<6; j++)
			{
				action move = action::place(i+1,j);
				if(move.apply(game)!=-1)
				{
					
					state_type ty = state_type::before;
					if(game.illegal())
						ty = state_type::illegal;
					CurNode->child[CurNode->child_count] = new Node(game, ty); 
					CurNode->child_count++;
					CurNode->child_amount++;
					cout<<"after_state place: "<<i<<j<<endl;//"\n"<<game<<endl;
					expectimax_traversal(CurNode->child[CurNode->child_count-1],game);
				}
				game = CurNode->game;
			}
		do chance of children to calculate Curnode->value
		*/
	}
	count++;
	cout<<"**************************************count:"<<count<<endl;
}
