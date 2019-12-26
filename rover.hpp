#ifndef ROVER_H
#define	ROVER_H

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

struct Block{
	int sample;
	int fuel;
	int x;
	int y;
};

struct Rover{
	int x = 0;
	int y = 0;
	int sample = 0;
	int fuel = 0;
	Rover(int x, int y, int sample, int fuel);
	void	move(Block *b);
};

class Grid{
	private:
		Block	**map;
		int		size;
	public:
		Grid(string map);
		Block	*find_route(int x, int y, int fuel, int sample);
		void	drawGrid(Rover* r);
		int		u_cost(int x, int y);
		int		d_cost(int x, int y);
		int		r_cost(int x, int y);
		int		l_cost(int x, int y);
		void	updateMap(string filename);
		Block	*get_block_pointer(int x, int y);
		int		get_size();
};

#endif
