#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	int SIZE;
	string filename;
	
	srand(time(0));
	if(argc == 3)
	{
		SIZE = std::stoi(argv[1]);
		filename = argv[2];
	}
	else
	{
		SIZE = (rand() % 50) + 1;
		filename = "/usr/lib/cgi-bin/map.txt";
	}
	ofstream file;
	file.open(filename);
	file << SIZE << endl;
	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			file << 1 + rand() % 9 << ":" << rand() % 10 << "\t";
		}
		file << endl;
	}
}
