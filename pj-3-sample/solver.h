#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include "board2x3.h"
#include "type.h"
#include "Trees.h"

class solver {
public:
	typedef float value_t;

public:
	class answer {
	public:
		answer(value_t value) : value(value) {}
	    friend std::ostream& operator <<(std::ostream& out, const answer& ans) {
	    	return out << (std::isnan(ans.value) ? -1 : ans.value);
		}
	public:
		const value_t value;
	};

public:
	void copystate(int* s, board2x3& b) {
		s[0]=b(0);s[1]=b(1);
		s[2]=b(2);s[3]=b(3);
		s[4]=b(4);s[5]=b(5);
	}
	solver(const std::string& args) {
		// TODO: explore the tree and save the result
		std::cout << "feel free to display some messages..." << std::endl;
		std::cout << "solver is initialized." << std::endl << std::endl;
		board2x3 game;
		std::cout<<game;
		Tree expTree;
		int s[6]; //= {0, 0, 0, 0, 0, 0};//here TODO copy game board to local char
		copystate(s,game);
		expTree.root->child[0] = new Node(s,state_type::illegal);
		expTree.expectimax_traversal(game);
		
	}

	answer solve2x3(const board2x3& state, state_type type = state_type::before) {
		// TODO: find the answer in the lookup table and return it
		return -1;
	}

private:
	// TODO: place your transposition table here
};
