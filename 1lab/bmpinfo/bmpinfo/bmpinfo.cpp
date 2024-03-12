#include <fstream>
#include <iostream>
#include <iterator>
#include <stdio.h>
#include <windows.h>

const int RLE1 = 1;
const int RLE2 = 2;
const int JPEG = 4;
const int PNG = 5;

bool ReadHeader(std::istream& fileInput, BITMAPFILEHEADER& bfh, BITMAPINFOHEADER& bih)
{
	memset(&bfh, 0, sizeof(BITMAPFILEHEADER)); //заполним нулями
	memset(&bih, 0, sizeof(BITMAPINFOHEADER));
	if (fileInput.read((char*)&bfh, sizeof(BITMAPFILEHEADER)) && fileInput.read((char*)&bih, sizeof(BITMAPINFOHEADER)))
	{
		return true;
	}
	return false;
}

void DataFilling(BITMAPINFOHEADER& bih, std::ostream& fileOutput)
{
	fileOutput << "Ширина: " << bih.biWidth << std::endl;
	fileOutput << "Высота: " << bih.biHeight << std::endl;
	fileOutput << "Бит на пиксель: " << bih.biBitCount << std::endl;
	if ((bih.biBitCount < 16) && (bih.biClrUsed == 0))
	{
		int biBitCount = 1 << bih.biBitCount;
		fileOutput << "Палитра: " << biBitCount << std::endl;
	}
	if ((bih.biCompression == RLE1) || (bih.biCompression == RLE2))
	{
		fileOutput << "Используется RLE компрессия" << std::endl;
	}
	if (bih.biCompression == JPEG) // числа в конст
	{
		fileOutput << "Используется JPEG компрессия" << std::endl;
	}
	if (bih.biCompression == PNG)
	{
		fileOutput << "Используется PNG компрессия" << std::endl;
	}
	if (bih.biSizeImage != 0)
	{
		fileOutput << "Размер: " << bih.biSizeImage << std::endl;
	}
	else
	{
		fileOutput << "Размер: " << (bih.biWidth * bih.biHeight * bih.biBitCount / 8) << std::endl;
	}
	return;
}

int ValidationArguments(int argc)
{
	if (argc != 3)
	{
		std::cout << "Error, enter the argumets: <input file> <output file>" << std::endl;
		return 1;
	}
	return 0;
}

int main(int argc, char* argv[])
{
	BITMAPFILEHEADER bitmapFileHeader;
	BITMAPINFOHEADER bitmapInfoHeader;
	if (ValidationArguments(argc) == 1)
		return 1;
	std::string fileInputName = argv[1], fileOutputuName = argv[2];
	std::ifstream fileInput(fileInputName, std::ios::binary);
	std::ofstream fileOutput(fileOutputuName);
	if (!fileInput || !fileOutput)
	{
		std::cout << "File(-s) not open(-s)" << std::endl;
		return 1;
	}
	if (!ReadHeader(fileInput, bitmapFileHeader, bitmapInfoHeader))
	{
		std::cout << "Файл не bitmap, а другого расширения." << std::endl;
		return 1;
	}
	int fileWidth = 0, fileHeight = 0, fileBitCount = 0, fileSize = 0, fileCompression = 0;
	DataFilling(bitmapInfoHeader, fileOutput);
	return 0;
}
