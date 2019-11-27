#pragma once
#include "Maze.h"
char Maze::Move_UP(int index) {
	int location;
	if (this->pos_Y > 0) {
		location = index - (3 * this->width);
		return decode_color(image_data[location], image_data[location + 1], image_data[location + 2]);
	}
}
char Maze::Move_DOWN(int index) {
	int location;

	if (this->pos_Y < Height) {
		location = index + (3 * this->width);
		return decode_color(this->image_data[location], this->image_data[location + 1], this->image_data[location + 2]);
	}
}
char Maze::Move_LEFT(int index) {
	int location;

	if (this->pos_X > 0) {
		location = index - 3;
		return decode_color(image_data[location], image_data[location + 1], image_data[location + 2]);
	}
}
char Maze::Move_RIGHT(int index) {
	int location;
	if (this->pos_X < width) {
		location = index + 3;
		return decode_color(image_data[location], image_data[location + 1], image_data[location + 2]);
	}
}
int Maze::Amount_of_choices(int index) {
	int count = 0;

	/*for (int i = 0; i < 4; i++) {
		Vision[i] = 0;
	}*/

	//hallway
	if (Move_UP(index) == 'B' && Move_DOWN(index) == 'B') {
		//Pocket

		if (Move_LEFT(index) == 'B' && Move_UP(index) == 'B' && Move_DOWN(index) == 'B') {
			return 5;

		}
		if (Move_DOWN(index) == 'B' && Move_RIGHT(index) == 'B' && Move_UP(index) == 'B') {
			return 5;

		}
		//!Pocket

		return count;

	}
	if (Move_LEFT(index) == 'B' && Move_RIGHT(index) == 'B') {

		//Pocket

		if (Move_UP(index) == 'B' && Move_RIGHT(index) == 'B' && Move_LEFT(index) == 'B') {
			return 5;

		}
		if (Move_DOWN(index) == 'B' && Move_RIGHT(index) == 'B' && Move_LEFT(index) == 'B') {
			return 5;

		}

		//!Pocket

		return count;

	}




	//vision
	if (Move_UP(index) == 'W' || Move_UP(index) == 'r') {
		count++;
		Vision[0] = 1;
	}
	if (Move_DOWN(index) == 'W' || Move_DOWN(index) == 'r') {
		count++;
		Vision[1] = 1;
	}
	if (Move_LEFT(index) == 'W' || Move_LEFT(index) == 'r') {
		count++;
		Vision[2] = 1;
	}
	if (Move_RIGHT(index) == 'W' || Move_RIGHT(index) == 'r') {
		count++;
		Vision[3] = 1;
	}

	return count;
}
void Maze::Mark_Choices() {
	short status = 0;
	for (int i = 0; i < width*Height * 3; i += 3) {
		if (decode_color(image_data[Position_Index], image_data[Position_Index + 1], image_data[Position_Index + 2]) == 'b') {
			//end of maze
			break;
		}
		else if (decode_color(image_data[Position_Index], image_data[Position_Index + 1], image_data[Position_Index + 2]) == 'W') {
			// a walkable path
			if (i % (width * 3) == 0) {
				pos_Y++;
				pos_X = 0;
			}
			if (Amount_of_choices(Position_Index) >= 2 && Amount_of_choices(Position_Index) < 5) {
				Color_Spec(Position_Index, 'g');

			}
			if (Amount_of_choices(Position_Index) == 5) {
				Color_Spec(Position_Index, 'b');

			}



			Position_Index += 3;
			pos_X++;

		}
		else {
			// !walkable path
			if (i % (width * 3) == 0) {
				pos_Y++;
				pos_X = 0;
			}

			Position_Index += 3;
			pos_X++;
		}

	}
}
unsigned long long Maze::cord_to_index(unsigned int x, unsigned int y) {
	return ((width * 3)*(y)) + (3 * (x));
}
void Maze::set_start_end() {
	unsigned long int index = 0;
	for (int i = 0; i < width * 3; i += 3) {
		if (decode_color(image_data[index], image_data[index + 1], image_data[index + 2]) == 'r') {

			S_x = index / 3;
			S_y = 0;
			break;

		}
		else {
			index += 3;
		}
	}
	index = Height * (3 * width);
	for ( int i = Height * (3 * width); i < (width *Height * 3) + (3 * width); i += 3) {
		if (decode_color(image_data[index], image_data[index + 1], image_data[index + 2]) == 'r') {

			E_x = (i / 3) / 3;
			E_y = Height - 1;
			return;

		}
		else {
			index += 3;
		}
	}

}
Maze::Maze() {
	Position_Index = 0;
	Vision = (int*)calloc(4, 4);
	pos_X = 0;
	pos_Y = 0;

}
void Maze::Load_Maze(const char *f_name) {
	Load_Image(f_name);
}
void Maze::print_maze() {
	printImdata();
}
bool Maze::Recursive_walk(int x, int y) {


	if (x == E_x && y == E_y) {
		return true;
	}
	if (decode_color(image_data[cord_to_index(x, y)], image_data[cord_to_index(x, y) + 1], image_data[cord_to_index(x, y) + 2]) == 'B' || memory[x][y]) {
		return false;
	}
	else {
		memory[x][y] = true;
	}


	if (x != 0) {
		if (Recursive_walk((x - 1), y)) {
			path[x][y] = true;
			return true;
		}

	}
	if (x != width - 1) {
		if (Recursive_walk((x + 1), y)) {
			path[x][y] = true;
			return true;
		}
	}
	if (y != 0) {
		if (Recursive_walk(x, (y - 1))) {
			path[x][y] = true;
			return true;
		}
	}
	if (y != Height - 1) {
		if (Recursive_walk(x, (y + 1))) {
			path[x][y] = true;
			return true;
		}
	}



	return false;
}
void Maze::Write_Junctions() {
	Mark_Choices();

	Write_Image("Colored");

}
void Maze::Solve_Maze() {
	//set_start_end();

	S_x = 12;
	S_y = 0;
	E_x = 84;
	E_y = 114;

	path = new bool*[width];
	memory = new bool*[width];
	for (int i = 0; i < width; i++) {
		path[i] = new bool[Height];
		memory[i] = new bool[Height];
	}
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < Height; j++) {
			path[i][j] = false;
			memory[i][j] = false;
		}
	}
	Recursive_walk(S_x, S_y);

	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < width; j++) {
			if (path[j][i] == true) {
				Color_Spec(cord_to_index(j, i), 'r');
			}
		}

	}


#ifdef DEBUG



	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < width; j++) {
			cout << path[j][i] << " ";
		}
		cout << "\n";
	}

#endif // DEBUG



	MODE = 4;
	Write_Image("666_solution");
}

