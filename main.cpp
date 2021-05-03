#include "Source.h"

int main()
{
	std::string fileIN = "training.bmp";
	std::string fileOUT = "result.bmp";
	
	BitMap _header;
	char* data;
	createFoe(fileOUT, 1920 , 1080);
	
	/*printImageInformation(fileOUT);*/
	return 0;
}