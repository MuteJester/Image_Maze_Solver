#pragma once
#ifndef Im
#define Im

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#endif

//#define _CRT_SECURE_NO_WARNINGS
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
	void color_set(char color_choice, int &index);
	char decode_color(uint8_t r, uint8_t g, uint8_t b);
public:
	Image();
	Image(unsigned char *image_data, int Height, int width, int channel);
	Image(int Height, int width, int channel);
	~Image();
	void Load_Blank_Canvas();
	void printImdata();
	void printImdata(char color);
	void Manual_Draw();
	void Load_Image();
	void Load_Image(const char *f_name);
	void Write_Image();
	void Write_Image(const char *f_name);
	void Color_Spec(int w, int h, char color);
	void Color_Spec(int index, char color);

};
