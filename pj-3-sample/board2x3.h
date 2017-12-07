#pragma once
#include <array>
#include <iostream>
#include <string>
#include <cstdio>
#include <cmath>

/**
 * array-based board for 2x3 2048
 *
 * index (2-d form):
 * [0][0] [0][1] [0][2]
 * [1][0] [1][1] [1][2]
 *
 * index (1-d form):
 *  (0)  (1)  (2)
 *  (3)  (4)  (5)
 *
 */
class board2x3 {

public:
	board2x3() : tile() {}
	board2x3(const board2x3& b) = default;
	board2x3& operator =(const board2x3& b) = default;

	std::array<int, 3>& operator [](const int& i) { return tile[i]; }
	const std::array<int, 3>& operator [](const int& i) const { return tile[i]; }
	int& operator ()(const int& i) { return tile[i / 3][i % 3]; }
	const int& operator ()(const int& i) const { return tile[i / 3][i % 3]; }
	bool illegal() {
		int count = 0;
		for(int i=0; i<2; i++)
			for(int j=0; j<3; j++)
			{
				if(tile[i][j]==0)
					count++;
			}
		if(count>4)
			return 1;
		else
			return 0;
	}

public:
	bool operator ==(const board2x3& b) const { return tile == b.tile; }
	bool operator < (const board2x3& b) const { return tile <  b.tile; }
	bool operator !=(const board2x3& b) const { return !(*this == b); }
	bool operator > (const board2x3& b) const { return b < *this; }
	bool operator <=(const board2x3& b) const { return !(b < *this); }
	bool operator >=(const board2x3& b) const { return !(*this < b); }

public:
	/**
	 * apply an action to the board
	 * return the reward gained by the action, or -1 if the action is illegal
	 */
	int move(const int& opcode) {
		switch (opcode) {
		case 0: return move_up();
		case 1: return move_right();
		case 2: return move_down();
		case 3: return move_left();
		default: return -1;
		}
	}
	int fibdriver(int n) const{
		if (n>=2)
			n++;
		return fib(n);
	}
	
	int fib(int n) const{
		//n++;
		if(n==0)
			return 0;
		if(n==1)
			return 1;
		return (fib(n-1)+fib(n-2));
	}

private:
	int move_left(int& left, int& right) {
		if (left) {
			if (right &&(left == right-1 || left == right+1 || (right==1&&left==1)) ) {
				left =std::max(left,right) + 1;
				right = 0;
				//return 1 << left;
				return fibdriver(left);
			}
		} else {
			left = right;
			right = 0;
		}
		return 0;
	}

public:
	int move_left() {
		//std::cout<<"========================================================in move left"<<std::endl;
		board2x3 prev = *this;
			
		int score = 0;
		for (int r = 0; r < 2; r++) {
			int s = move_left(tile[r][0], tile[r][1]) + move_left(tile[r][1], tile[r][2]);
			if (s == 0) s += move_left(tile[r][0], tile[r][1]);
			score += s;
		}
		//if(*this==prev)
		//	std::cout<<"====================same"<<std::endl;
		//std::cout<<prev;
		//std::cout<<*this;
		//std::cout<<"ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo"<<std::endl;
		return (*this != prev) ? score : -1;
	}
	int move_right() {
		reflect_horizontal();
		int score = move_left();
		reflect_horizontal();
		return score;
	}
	int move_up() {
		//std::cout<<"=====================in move up"<<std::endl;
		board2x3 prev = *this;
		int score = 0;
		for (int c = 0; c < 3; c++) {
			score += move_left(tile[0][c], tile[1][c]);
		}
		//if(*this==prev)
		//	std::cout<<"====================same"<<std::endl;

		//std::cout<<prev;
		//std::cout<<*this;
		//std::cout<<"ooooooooooooooooooooooooooooooooooooooo"<<std::endl;
		return (*this != prev) ? score : -1;
	}
	int move_down() {
		reflect_vertical();
		int score = move_up();
		reflect_vertical();
		return score;
	}

	void reflect_horizontal() {
		std::swap(tile[0][0], tile[0][2]);
		std::swap(tile[1][0], tile[1][2]);
	}

	void reflect_vertical() {
		std::swap(tile[0], tile[1]);
	}

	void reverse() { reflect_horizontal(); reflect_vertical(); }

public:
    friend std::ostream& operator <<(std::ostream& out, const board2x3& b) {
		char buff[32];
		out << "+------------------+" << std::endl;
		/*for (int r = 0; r < 2; r++) {
			std::snprintf(buff, sizeof(buff), "|%6u%6u%6u|",
				(1 << b[r][0]) & -2u, // use -2u (0xff...fe) to remove the unnecessary 1 for (1 << 0)
				(1 << b[r][1]) & -2u,
				(1 << b[r][2]) & -2u);
			out << buff << std::endl;
		}*/
		for (int r = 0; r < 2; r++) {
			std::snprintf(buff, sizeof(buff), "|%6u%6u%6u|",
				(b.fibdriver(b[r][0])), // use -2u (0xff...fe) to remove the unnecessary 1 for (1 << 0)
				(b.fibdriver(b[r][1])),
				(b.fibdriver(b[r][2])));
			out << buff << std::endl;
		}
		out << "+------------------+" << std::endl;
		return out;
	}
    friend std::istream& operator >>(std::istream& in, board2x3& b) {
    	std::string s;
		if (in >> s) {
			bool norm = false;
			if (s.find('+') != std::string::npos) {
		    	norm = true;
				if (in >> s && s == "|") {
			    	in >> b(0) >> b(1) >> b(2) >> s >> s;
			    	in >> b(3) >> b(4) >> b(5) >> s >> s;
				} else {
					b(0) = std::stol(s);
			    	in >> b(1) >> b(2) >> b(3) >> b(4) >> b(5);
				}
			} else {
				b(0) = std::stol(s);
		    	in >> b(1) >> b(2) >> b(3) >> b(4) >> b(5);
			}
			if (norm) {
		    	for (int i = 0; i < 6; i++)
		    		if (b(i) != 0) b(i) = std::log2(b(i));
			}
		}
    	return in;
    }

private:
    std::array<std::array<int, 3>, 2> tile;
};
