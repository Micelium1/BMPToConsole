#include "BMParser.h"
#include <windows.h>
#include <iostream>

BMParser::BMParser()
{

}

BMParser::BMParser(const std::string& filename)
{
	this->openBMP(filename);
}

void BMParser::openBMP(const std::string& filename)
{
	if (file and file->is_open()) file.reset();
	file = std::make_shared<std::fstream>(std::fstream(filename));
	if (!file.get()->is_open()) { throw std::runtime_error("Ошибка чтения файла с путем: " + filename); };
	return;
}
void BMParser::displayBMP()
{
	BITMAPFILEHEADER fileHeader;
	file->read(reinterpret_cast<char*>(&fileHeader), sizeof(BITMAPFILEHEADER));

	BITMAPINFOHEADER infoHeader;
	file->read(reinterpret_cast<char*>(&infoHeader), sizeof(BITMAPINFOHEADER));

	std::cout << "Width: " << infoHeader.biWidth << std::endl;
	std::cout << "Height: " << infoHeader.biHeight << std::endl;
	std::cout << "Bit Count: " << infoHeader.biBitCount << " bits per pixel" << std::endl;
	std::cout << "Compression: " << infoHeader.biCompression << std::endl;
	std::cout << "Image Size: " << infoHeader.biSizeImage << " bytes" << std::endl;
	if (!(infoHeader.biBitCount == 24 or infoHeader.biBitCount == 32)) throw std::runtime_error("Не поддерживаемый БМП формат");

	int dataSize = infoHeader.biSizeImage;
	if (dataSize == 0) {
		dataSize = infoHeader.biWidth * infoHeader.biHeight * (infoHeader.biBitCount / 8);
	}

	int bytesPerPixel = infoHeader.biBitCount / 8;

	int rowSize = (infoHeader.biWidth * bytesPerPixel + 3) & (~3);  

	

	
	char* pixelData = new char[infoHeader.biHeight * rowSize];

	file->seekg(fileHeader.bfOffBits, std::ios::beg); 
	file->read(pixelData, rowSize * infoHeader.biHeight);

	for (int y = infoHeader.biHeight - 1; y >= 0; y--) {
		


		for (int x = 0; x < infoHeader.biWidth; x++) {

			int rowIndex = y * rowSize;
			int pixelIndex = x * bytesPerPixel;
			unsigned char blue = pixelData[rowIndex + pixelIndex + 0];
			if (blue) std::cout << "_";
			else std::cout << "*";
		}
		std::cout << std::endl;
	}


	delete[] pixelData;
	return;
}
void BMParser::closeBMP()
{
	file.reset();
}

BMParser::~BMParser()
{
	this->closeBMP();
}
