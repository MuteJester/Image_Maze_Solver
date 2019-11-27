#define STB_IMAGE_IMPLEMENTATION\
/*
#include <iostream>
#include <fstream>
#include <sstream>*/
#define _CRT_SECURE_NO_WARNINGS
#include <stb_image.h>
#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <conio.h>
#include <string.h>
#include <vector>
using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

#define CHOICE_MARK




class pixel {
private:
	uint8_t r;
	uint8_t g;
	uint8_t b;
	int index;
public:
	pixel() {
		r = g = b =index= 0;
	}
	pixel(int r, int g, int b,int index) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->index = index;
	}
	char get_color() {
		if (r == 0 && b == 0 && g > 0) {
			return 'g';
		}
		else if (r > 0 && b == 0 && g == 0) {
			return 'r';
		}
		else if (r == 0 && b > 0 && g == 0) {
			return 'b';
		}
		else if (r == 255 && b == 0 && g == 255) {
			return 'y';
		}
		else if (r == 255 && b == 0 && g == 165) {
			return 'o';
		}
		else if (r == 0 && b == 0 && g == 0) {
			return 'B';
		}
		else if (r <= 255 && r >= 240 && b <= 255 && b >= 240 && g <= 255 && g >= 240) {
			return 'W';
		}
		else {
			return 'M';
		}
	}
	void set_color(int r, int g, int b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}
	void set_color(int r, int g, int b,int index) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->index = index;
	}
	int get_index() {
		return index;
	}

};



class Image {
protected:
	char f_name[50];
	unsigned char *image_data;
	int Height;
	int width;
	int channel;
	unsigned int im_size;
	int pos_X, pos_Y;
	unsigned short MODE = 0;
	void color_set(char color_choice, int &index) {


		switch (color_choice)
		{
		case 'r':
			image_data[index++] = 255;
			image_data[index++] = 0;
			image_data[index] = 0;
			index -= 2;
			break;
		case 'g':
			image_data[index++] = 0;
			image_data[index++] = 255;
			image_data[index] = 0;
			index -= 2;
			break;
		case 'b':
			image_data[index++] = 0;
			image_data[index++] = 0;
			image_data[index] = 255;
			index -= 2;
			break;
		case 'W':
			image_data[index++] = 255;
			image_data[index++] = 255;
			image_data[index] = 255;
			index -= 2;
			break;
		case 'B':
			image_data[index++] = 0;
			image_data[index++] = 0;
			image_data[index] = 0;
			index -= 2;
			break;
		default:
			break;
		}



	}
	char decode_color(uint8_t r, uint8_t g, uint8_t b) {
		if (r == 0 && b == 0 && g > 0) {//green
			return 'g';
		}
		else if (r > 0 && b == 0 && g == 0) {//red
			return 'r';
		}
		else if (r == 0 && b > 0 && g == 0) {//blue
			return 'b';
		}
		else if (r == 0 && b == 0 && g == 0) {//black
			return 'B';
		}
		else if (r <= 255 && r >= 240 && b <= 255 && b >= 240 && g <= 255 && g >= 240) {//white
			return 'W';
		}
		else if (r >= 169 && b >= 169 && g >= 169) {//shades of gray
			return 'G';
		}

		else {//undefined color
			return 'M';
		}
	}


public:
	Image() {
		this->image_data = NULL;
		this->Height = 0;
		this->width = 0;
		this->channel = 0;
		this->im_size = 0;
		this->pos_X = 0;
		this->pos_Y = 0;

	}
	Image(unsigned char *image_data, int Height, int width,int channel) {
		this->image_data = image_data;
		this->Height = Height;
		this->width = width;
		this->channel = channel;
		this->im_size = width * Height*channel;
		this->pos_X = 0;
		this->pos_Y = 0;

	
	}
	Image(int Height, int width, int channel) {
		this->Height = Height;
		this->width = width;
		this->channel = channel;
		this->pos_X = 0;
		this->pos_Y = 0;
	}
	~Image() {
		stbi_image_free(image_data);
	
	}
	void Load_Blank_Canvas() {
		cout << "\nPlease Enter Height Of Image: ";
		cin >> Height;
		cout << "\nPlease Enter Width Of Image: ";
		cin >> width;
		cout << "\nPlease Enter Number Of Color Channels: ";
		cin >> channel;
		if (image_data != NULL) {
			stbi_image_free(image_data);
		}
		else {
			image_data = (unsigned char*)calloc(width*Height*channel,sizeof(unsigned char));
		}
	}
	void printImdata() {
		int index = 0;
		system("cls");
		for (int i = 0; i < width*Height * 3; i += 3) {

			if (i % (width * 3) == 0) {
				cout << "\n";
			}

			if (i == (width*3)*(pos_Y) +3*(pos_X+1) && MODE == 1) {
				cout << "[]";
				index += 3;
			}
			if (i == (width * 3)*(pos_Y)+3 * (pos_X + 1) && MODE == 2) {
				cout << "_" << " ";
				index += 3;
			}
			else {

				cout <<decode_color(image_data[index], image_data[index + 1], image_data[index + 2]) << " ";
				index += 3;
			}

		}
	}
	void printImdata(char color) {
		int index = 0;
		system("cls");
		for (int i = 0; i < width*Height * 3; i += 3) {

			if (i % (width * 3) == 0) {
				cout << "\n";
			}

			if (i == (width * 3)*(pos_Y)+3 * (pos_X + 1) && MODE == 1) {
				cout << "[" << color<<"] ";
				index += 3;
			}

			else {

				/*printf("%3d ", image_data[index++]);
				printf("%3d ", image_data[index++]);
				printf("%3d ", image_data[index++]);*/
				cout << decode_color(image_data[index], image_data[index + 1], image_data[index + 2]) << " ";
				index += 3;
			}

		}
	}



	void Manual_Draw() {
		int index = 3;
		int key_movment ;
		unsigned char choice='z',color_choice;
		short state = 1;
		MODE = 1;
		
		printImdata();
		while (state) {
			
			switch ((key_movment = _getch()))
			{
				
			case KEY_UP:
				if (pos_Y > 0) {
					pos_Y--;
					index -= 3*width;
					printImdata();
					choice = _getch();

					if (choice == 'e') {
						MODE = 2;
						printImdata();
						MODE = 1;
						color_choice = _getch();

						color_set(color_choice, index);
						printImdata(color_choice);
						choice = 'z';
					}

				}
#ifdef DEBUG



				cout << "up Y: " << pos_Y << "  Index Is " << index << "\n";
#endif //debug
				break;
			case KEY_DOWN:
				if (pos_Y < Height) {
					pos_Y ++;
					index += 3*width;
					printImdata();
					choice = _getch();

					if (choice == 'e') {
						MODE = 2;
						printImdata();
						MODE = 1;
						color_choice = _getch();

						color_set(color_choice, index);
						printImdata(color_choice);
						choice = 'z';
					}
				}
#ifdef DEBUG



				cout << "down Y: " << pos_Y << "  Index Is " << index << "\n";
#endif //debug
				break;
			case KEY_LEFT:
				if (pos_X > 0) {
					pos_X--;
					index -= 3;
					printImdata();
					choice = _getch();

					if (choice == 'e') {
						MODE = 2;
						printImdata();
						MODE = 1;
						color_choice = _getch();

						color_set(color_choice, index);
						printImdata(color_choice);
						choice = 'z';
					}
				}
#ifdef DEBUG
				cout << "left x: " << pos_X << "  Index Is " << index << "\n";
#endif DEBUG//debug
				break;
			case KEY_RIGHT:
				if (pos_X < width) {
					pos_X++;
					index += 3;
					printImdata();
					choice = _getch();

					if (choice == 'e') {
						MODE = 2;
						printImdata();
						MODE = 1;
						color_choice = _getch();

						color_set(color_choice, index);
						printImdata(color_choice);
						choice = 'z';
					}
				}
#ifdef DEBUG
				cout << "right x: " << pos_X << "  Index Is " << index << "\n";
#endif DEBUG//debug
				break;
			case '-':
				state = 0;
				break;

			default:
				break;
			}

			
		}

		MODE = 0;
	}



	void Load_Image() {
		cout << "Please Enter Image Name Including .'Type': ";
		cin >> f_name;
		strcpy(this->f_name, f_name);
		this->image_data = stbi_load(f_name, &width, &Height, &channel, 3);

		if (this->image_data == NULL) {
			cout << "\n There Was An Error While Openning Image\nPlease Check File Name / Diractory\n";
		}
		else {
			cout << "\nFile Loaded Succsesfully\n";
		}
	}
	void Load_Image(const char *f_name) {
		strcpy(this->f_name, f_name);
		this->image_data = stbi_load((char*)f_name, &width, &Height, &channel, 3);
		if (this->image_data == NULL) {
			cout << "\n There Was An Error While Openning Image\nPlease Check File Name / Diractory\n";
		}
		else {
			cout << "\nFile Loaded Succsesfully\n";
		}
	}

	void Write_Image() {
		if (MODE == 4) {
			char solved[100];
			strcpy(solved, "Solved_");
			strcat(solved, this->f_name);
			if (channel > 3) {
				channel = 3;
			}
			stbi_write_jpg(solved, width, Height, channel, image_data, 100);
		}
		else {
			char s_name[50];
			char type[10];
			strcpy(type, ".jpg");
			cout << "Save As?: ";
			cin >> s_name;
			strcat(s_name, type);
			stbi_write_jpg(s_name, width, Height, channel, image_data, 100);

			cout << "\nFile Saved Succsfully As: " << s_name << endl;
		}
	}
	void Write_Image(const char *f_name) {
	
			char s_name[50];
			char type[10];
			strcpy(type, ".jpg");
			strcpy(s_name, f_name);
			strcat(s_name, type);
			if (channel > 3) {
				channel = 3;
			}
			stbi_write_jpg(s_name, width, Height, channel, image_data, 100);

			cout << "\nFile Saved Succsfully As: " << s_name << endl;
		
	}

	void Color_Spec(int w, int h, char color) {
		int pos = ((width * 3)*(h)+3 * (w));
		color_set(color,pos);
	}
	void Color_Spec(int index, char color) {
		
		int pos = index;
		color_set(color, pos);
	}

};



class Maze :private Image {
private:
	int Position_Index;
	//Linked_List Path_Graph;
	//up,down,left,right
	int *Vision;
	int Entry_Index, Exist_Index;
	int S_x, S_y, E_x, E_y;
	bool **memory;
	bool **path;
	char Move_UP(int index) {
		int location;
		if (this->pos_Y > 0) {
			location = index - (3 * this->width);
			return decode_color(image_data[location], image_data[location + 1], image_data[location + 2]);
		}
	}
	char Move_DOWN(int index) {
		int location;

		if (this->pos_Y < Height) {
			location = index + (3 * this->width);
			return decode_color(this->image_data[location], this->image_data[location + 1], this->image_data[location + 2]);
		}
	}
	char Move_LEFT(int index) {
		int location;

		if (this->pos_X > 0) {
			location = index - 3;
			return decode_color(image_data[location], image_data[location + 1], image_data[location + 2]);
		}
	}
	char Move_RIGHT(int index) {
		int location;
		if (this->pos_X < width) {
			location = index + 3;
			return decode_color(image_data[location], image_data[location + 1], image_data[location + 2]);
		}
	}
	int Amount_of_choices(int index) {
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
	void Mark_Choices() {
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
	unsigned long long cord_to_index(unsigned int x, unsigned int y) {
		return ((width * 3)*(y))+(3 * (x));
	}
	void set_start_end() {
		unsigned long int index = 0;
		int e = 0;
		for (int i = 0; i < width * 3; i += 3) {
			if (decode_color(image_data[index], image_data[index + 1] , image_data[index + 2] )=='W') {

					S_x = (index)/ 3;
					S_y = 0;
					break;

			}
			else {
				index += 3;
			}
		}
		index = (Height-1) * (3 * width);
		for (unsigned int i = (Height-1) * (3 * width); i < (width *Height* 3); i += 3) {
			if (decode_color(image_data[index], image_data[index + 1] , image_data[index + 2] ) == 'W') {

				E_x = e;
				E_y = Height-1;
				return;

			}
			else {
				e++;
				index += 3;
			}
		}

	}
public:
	Maze() {
		Position_Index = 0;
		Vision = (int*)calloc(4, 4);
		pos_X = 0;
		pos_Y = 0;
		
	}
	void Load_Maze(const char *f_name) {
		Load_Image(f_name);
	}
	void print_maze() {
		printImdata();
	}
	bool Recursive_walk(int x,int y) {


		if (x == E_x && y == E_y) {
			return true;
		}
		if (decode_color(image_data[cord_to_index(x,y)], image_data[cord_to_index(x, y)+1], image_data[cord_to_index(x, y) + 2] ) == 'B' || memory[x][y]) {
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
			if (Recursive_walk(x, (y-1))) {
				path[x][y] = true;
				return true;
			}
		}
		if (y != Height - 1) {
			if (Recursive_walk(x, (y+1))) {
				path[x][y] = true;
				return true;
			}
		}



		return false;
	}
	void Write_Junctions() {
		Mark_Choices();

		Write_Image("Colored_Des");

	}
	void Solve_Maze() {
		//set_start_end();

		S_x = 4;
		S_y = 0;
		E_x = 1801;
		E_y = 1797;

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
		Color_Spec(cord_to_index(E_x, E_y), 'b');

#ifdef DEBUG



		for (int i = 0; i <Height ; i++) {
			for (int j = 0; j < width; j++) {
				cout << path[j][i] << " ";
			}
			cout << "\n";
		}

#endif // DEBUG

		

		MODE = 4;
		Write_Image("Solution");
	}

};
