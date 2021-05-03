#pragma once
#ifndef _source_
#define _source_
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#define BMP_IN "training.bmp"
#define BMP_OUT "training-modified.bmp"

#pragma pack(push, 1)
struct Pix
{
	unsigned char B;
	unsigned char G;
	unsigned char R;

};
#pragma pack(pop)

#pragma pack(push, 1)
struct BitMap
{
	short		m_signature;
	long		m_reserved1 = 0;
	long		m_reserved2 = 0;

	long		m_dataOffSet= 54;

	long		m_size = 40;
	long		m_width;
	long		m_height;
	short		m_planes = 1;
	short		m_bpp;

	long		m_compression = 0;
	long		m_sizeImage;

	long		m_xPixelsPreMeter = 0;
	long		m_yPixelsPreMeter = 0;

	long		m_colorsUsed = 0;
	long		m_colorsImportant = 0;
};
#pragma pack(pop)

void readBMP(const char* filePath, BitMap& header, char*& data);
void writeBMP(const char* filePath, BitMap& header, char*& data);

char* convertPixelArrayToData(Pix*& pixels, BitMap& header);
Pix* convertDataToPixelArray(char*& data, BitMap& header);

void grayscale(Pix*& pixel, int size);
void createImage(BitMap& _header, char*& _data, int w, int h);
void drawFlagOfEngland(BitMap& _header, Pix*& _pixels);
void createFoe(std::string path, int w, int h);
void copyImage(std::string fileIN, std::string fileOUT);
void printImageInformation(std::string path);

#endif // !_source_

