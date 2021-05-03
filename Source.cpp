
#include "Source.h"

void readBMP(const char* filePath, BitMap& header, char*& data)
{
	FILE* f = fopen(filePath, "rb");
	if (!f)
	{
		printf("Cannot open file for reading!!!");
		exit(-1);
	}

	fread(&header, sizeof(header), 1, f);

	int _padding = header.m_width % 4;
	int _size = header.m_width * header.m_height * (header.m_bpp / 8) + _padding * header.m_height;

	data = new char[_size];
	fread(data, sizeof(char), _size, f);

	fclose(f);
}

void writeBMP(const char* filePath, BitMap& header, char*& data)
{
	FILE* f = fopen(filePath, "wb");
	if (!f)
	{
		printf("Cannot open file for writing!!!");
		exit(-1);
	}

	fwrite(&header, sizeof(header), 1, f);

	int _padding = header.m_width % 4;
	int _size = header.m_width * header.m_height * (header.m_bpp / 8) + _padding * header.m_height;

	fwrite(data, sizeof(char), _size, f);

	fclose(f);
}

Pix* convertDataToPixelArray(char*& data, BitMap& header)
{
	int _size = header.m_width * header.m_height;
	Pix* _pixels = new Pix[_size];

	int _padding = header.m_width % 4;

	char* _temp = data;

	for (int i = 0; i < header.m_height; i++)
	{
		for (int j = 0; j < header.m_width; j++)
		{
			_pixels[i * header.m_height + j].B = *(_temp++);
			_pixels[i * header.m_height + j].G = *(_temp++);
			_pixels[i * header.m_height + j].R = *(_temp++);
		}

		_temp += _padding;
	}

	return _pixels;
}

char* convertPixelArrayToData(Pix*& pixels, BitMap& header)
{
	int _padding = header.m_width % 4;
	int _size = header.m_width * header.m_height * (header.m_bpp / 8) + _padding * header.m_height;

	char* _data = new char[_size];
	char* _temp = _data;

	for (int i = 0; i < header.m_height; i++)
	{
		for (int j = 0; j < header.m_width; j++)
		{
			*(_temp++) = pixels[i * header.m_height + j].B;
			*(_temp++) = pixels[i * header.m_height + j].G;
			*(_temp++) = pixels[i * header.m_height + j].R;
		}

		for (int k = 0; k < _padding; k++)
		{
			*(_temp++) = 0;
		}
	}

	return _data;
}

void grayscale(Pix*& pixels, int size)
{
	for (int i = 0; i < size; i++)
	{
		int _val = (pixels[i].R + pixels[i].G + pixels[i].B) / 3;
		pixels[i].R = pixels[i].G = pixels[i].B = _val;
	}
}

void createImage(BitMap& _header, char*& _data, int w, int h)
{

	//setup header struct
	_header.m_signature = 19778;
	_header.m_height = h;
	_header.m_width = w;
	_header.m_bpp = 24;
	_header.m_dataOffSet = 54;

	_header.m_sizeImage = _header.m_width * _header.m_height * (_header.m_bpp / 8);
	_header.m_reserved1 = _header.m_sizeImage + _header.m_dataOffSet;
	//set up data
	int _padding = _header.m_width % 4;
	int _size = _header.m_width * _header.m_height * (_header.m_bpp / 8) + _padding * _header.m_height;
	_data = new char[_size];
	std::cout << "hello";
	//for (int i = 0; i < _size; i++) *(_data++) = 0;
	std::cout << "helo";
	//end setup
}

void drawFlagOfEngland(BitMap& _header, Pix*& _pixels)
{
	//draw white background
	for (int i = 0; i < _header.m_height; i++)
	{
		for (int j = 0; j < _header.m_width; j++)
		{
			_pixels[i * _header.m_height + j].B = 253;
			_pixels[i * _header.m_height + j].G = 253;
			_pixels[i * _header.m_height + j].R = 250;
		}


	}

	// draw red cross
	int thickness = _header.m_height / 10;
	
	for (int i = 0; i < _header.m_height; i++)
	{
		for (int j = (_header.m_width - thickness) / 2; j < (_header.m_width + thickness) / 2; j++)
		{
			_pixels[i * _header.m_height + j].B = 0;
			_pixels[i * _header.m_height + j].G = 0;
			_pixels[i * _header.m_height + j].R = 255;
		}
	}
	
	for (int i = (_header.m_height - thickness) / 2; i < (_header.m_height + thickness) / 2; i++)
	{
		for (int j = 0; j < _header.m_width; j++)
		{
			_pixels[i * _header.m_height + j].B = 0;
			_pixels[i * _header.m_height + j].G = 0;
			_pixels[i * _header.m_height + j].R = 255;
		}
	}
}

void copyImage(std::string fileIN, std::string fileOUT)
{
	BitMap _header;
	char* _data = NULL;
	
	readBMP(fileIN.c_str(), _header, _data);


	Pix* _pixels = convertDataToPixelArray(_data, _header);
	delete[] _data;
	_data = NULL;
	int _padding = _header.m_width % 4;

	char* _temp = _data;


	delete[]_temp;
	_data = convertPixelArrayToData(_pixels, _header);

	writeBMP(fileOUT.c_str(), _header, _data);
	delete[] _pixels;
	_pixels = NULL;
}

void printImageInformation(std::string path)
{
	FILE* f = fopen(path.c_str(), "rb");
	if (!f)
	{
		printf("Cannot open file for reading!!!");
		exit(-1);
	}
	BitMap header;

	fread(&header, sizeof(header), 1, f);
	fclose(f);


	printf("\n  signature         %d", header.m_signature);       
	printf("\n  reserved1         %d", header.m_reserved1);      
	printf("\n  reserved2         %d", header.m_reserved2);     
	printf("\n  dataOffSet        %d", header.m_dataOffSet);         
	printf("\n  size              %d", header.m_size );                  				  
	printf("\n  width             %d", header.m_width);       		   	
	printf("\n  height            %d", header.m_height);           	     
	printf("\n  planes            %d", header.m_planes);        	      
	printf("\n  bpp               %d", header.m_bpp);            		    
	printf("\n  compression       %d", header.m_compression);   	  
	printf("\n  sizeImage         %d", header.m_sizeImage);	    		
	printf("\n  xPixelsPreMeter   %d", header.m_xPixelsPreMeter); 	
	printf("\n  yPixelsPreMeter   %d", header.m_yPixelsPreMeter);	
	printf("\n  colorsUsed        %d", header.m_colorsUsed );    		
	printf("\n  colorsImportant   %d", header.m_colorsImportant);	


	
}

void createFoe(std::string path, int w, int h)
{
	BitMap _header;
	char* _data;

	createImage(_header, _data, w, h);

	int _padding = _header.m_width % 4;


	Pix* _pixels = convertDataToPixelArray(_data, _header);
	delete[] _data;
	_data = NULL;


	drawFlagOfEngland(_header, _pixels);


	_data = convertPixelArrayToData(_pixels, _header);

	writeBMP(path.c_str(), _header, _data);
	delete[] _pixels;
}
