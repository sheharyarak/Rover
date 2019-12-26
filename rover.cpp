#include "rover.hpp"

Rover::Rover(int x, int y, int sample, int fuel)
{
	this->x = x;
	this->y = y;
	this->sample = sample;
	this->fuel = fuel;
}

Grid::Grid(string filename)
{
	ifstream infile;
	infile.open(filename);
	infile >> size;
	map = new Block*[size];
	for(int i = 0; i < size; i++)
		map[i] = new Block[size];
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			infile >> filename;
			map[i][j].fuel = atoi(&filename[0]);
			map[i][j].sample = atoi(&filename[2]);
			map[i][j].x = j;
			map[i][j].y = i;
		}
	}
}

Block *Grid::find_route(int x, int y, int fuel, int sample)
{
	if(x==0 and y==0)//top left corner - start - ⠋
	{
		if(r_cost(x,y) > d_cost(x,y))
			return	&map[y][x+1];	//move right
		else
			return	&map[y+1][x];	//move down
	}
	else if(x==size-1 and y==0)//top right corner - ⠙
	{
		if(l_cost(x,y) > d_cost(x,y))
			return	&map[y][x-1];	//move left
		else
			return	&map[y+1][x];	//move down
	}
	else if(x==0 and y==size-1)//bottom left corner - ⠦
	{
		if(u_cost(x,y) > r_cost(x,y))
			return	&map[y-1][x];	//move up
		else
			return	&map[y][x+1];	//move right
	}
	else if(x==size-1 and y==size-1)//bottom right corner - end - ⠴
	{
		if(sample < 12)
		{
			if(u_cost(x,y) > l_cost(x,y))
				return	&map[y-1][x];	//move up
			else
				return	&map[y][x-1];	//move left
		}
		else
			return &map[y][x];
	}
	else if(y==0)//top edge - ⠉
	{
		if(l_cost(x,y) > r_cost(x,y))
		{
			if(l_cost(x,y) > d_cost(x,y))
				return	&map[y][x-1];	//move left
			else
				return	&map[y+1][x];	//move down
		}
		else
		{
			if(r_cost(x,y) > d_cost(x,y))
				return	&map[y][x+1];	//move right
			else
				return	&map[y+1][x];	//move down
		}
	}	
	else if(x==0)//left edge - ⠇
	{
		if(u_cost(x,y) > r_cost(x,y))
		{
			if(u_cost(x,y) > d_cost(x,y))
				return	&map[y-1][x];	//move up
			else
				return	&map[y+1][x];	//move down
		}
		else
		{
			if(r_cost(x,y) > d_cost(x,y))
				return	&map[y][x+1];	//move right
			else
				return	&map[y+1][x];	//move down
		}
	}
	else if(x==size-1)//right edge - ⠸
	{
		if(u_cost(x,y) > l_cost(x,y))
		{
			if(u_cost(x,y) > d_cost(x,y))
				return	&map[y-1][x];	//move up
			else
				return	&map[y+1][x];	//move down
		}
		else
		{
			if(l_cost(x,y) > d_cost(x,y))
				return	&map[y][x-1];	//move left
			else
				return	&map[y+1][x];	//move down
		}
	}
	else if(y==size-1)//bottom edge - ⠤
	{
		if(u_cost(x,y) > r_cost(x,y))
		{
			if(u_cost(x,y) > l_cost(x,y))
				return	&map[y-1][x];	//move up
			else
				return	&map[y][x+1];	//move left
		}
		else
		{
			if(r_cost(x,y) > l_cost(x,y))
				return	&map[y][x+1];	//move right
			else
				return	&map[y][x-1];	//move left
		}
	}
	else//center - ⠿
	{
		//make parellel arrays that link th eposition to the cost
		int		pos[4][2] = {
			{y,x+1},	//right
			{y,x-1},	//left
			{y+1,x},	//down
			{y-1,x}		//up
		};
		int cost[4] = {
			r_cost(x,y),
			l_cost(x,y),
			d_cost(x,y),
			u_cost(x,y)
		};
		//find most profitable position to move to
		int	max_index = 0;
		for(int i = 1; i < 4; i++)
			if(cost[i]>cost[max_index])
				max_index = i;
		//~ cout << "max index cost = " << cost[max_index];
		return &map[pos[max_index][0]][pos[max_index][1]]; //move to position
	}
}

void	Grid::drawGrid(Rover *r)
{
	int BOX_SIZE = size > 10 ? 5000 / (size * size) : 50 ;
	cout << "<div class=\"grid-div\">";
	cout << "<table style=\"width: "<<size*BOX_SIZE<<"px; height: "<<size*25<<"px; text-align: center;\">";
    cout << "<tbody>";
    for(int i = 0; i < size; i++)
	{
		cout << "\n<tr style=\"height:"<<BOX_SIZE<<"; width: "<<size*BOX_SIZE<<"\">";
		for(int j = 0; j < size; j++)
		{
			cout << "\n\t<td  style=\"background-color:rgb(139,69,19, 0."<< 50 + map[i][j].fuel*5<<"); height:"<<BOX_SIZE<<"px; width:"<<BOX_SIZE<<"px\">";
			if(r->x == j && r->y == i)
			{
				cout << "\n\t\t\t<img src=\"http://localhost:8080/home/Tutoring/Rover/rover.png\" height=\""<<BOX_SIZE<<" width=\""<<BOX_SIZE<<"\">";
			}
			else
			{
			    cout << "\n\t\t\t<p>"<<map[i][j].sample<<"</p>";
			}
			cout <<"\n\t</td>";
		}
		cout << "\n</tr>";
	}
	cout << "</div></tbody></table>";
}

void	Rover::move(Block *b)
{
	if(b->fuel > this->fuel)
	{
		this->fuel++;
		return;
	}
	else
	{		
		this->x = b->x;
		this->y = b->y;
		this->fuel -= b->fuel;
		this->sample += b->sample;
		b->sample = 0;
		b->fuel = 9;
	}
}

int		Grid::u_cost(int x, int y)
{
	return map[y-1][x].sample - 2 * map[y-1][x].fuel;
}
int		Grid::d_cost(int x, int y)
{
	return map[y+1][x].sample - map[y+1][x].fuel;
}
int		Grid::r_cost(int x, int y)
{
	return map[y][x+1].sample - map[y][x+1].fuel;
}
int		Grid::l_cost(int x, int y)
{
	return map[y][x-1].sample - 2*map[y][x-1].fuel;
}	
void	Grid::updateMap(string filename)
{
	ofstream file;
	file.open(filename, ios::out);
	file << size << endl;
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			file << map[i][j].fuel << ":" << map[i][j].sample << "\t";
		}
		file << endl;
	}
}
Block	*Grid::get_block_pointer(int x, int y)
{
	return &map[y][x];
}

int		Grid::get_size(){
	return size;
}
