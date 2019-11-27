#pragma once


#include "Image_Handle.h"

class Maze :private Image {
private:
	int Position_Index;
	//up,down,left,right
	int *Vision;
	int Entry_Index, Exist_Index;
	int S_x, S_y, E_x, E_y;
	bool **memory;
	bool **path;
	char Move_UP(int index);
	char Move_DOWN(int index);
	char Move_LEFT(int index);
	char Move_RIGHT(int index);

	int Amount_of_choices(int index);

	void Mark_Choices();
	unsigned long long cord_to_index(unsigned int x, unsigned int y);
	void set_start_end();


public:
	Maze();
	void Load_Maze(const char *f_name);
	void print_maze();
	bool Recursive_walk(int x, int y);
	void Write_Junctions();
	void Solve_Maze();

};
