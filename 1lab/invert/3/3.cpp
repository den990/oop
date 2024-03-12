#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <array>

const int MATRIX3X3_SIZE = 3;
const int MATRIX2X2_SIZE = 2;

using Mat3x3 = std::array<std::array<double, 4>, 4>;
using Mat2x2 = std::array<std::array<double, 3>, 3>;

int ValidationArguments(int argc)
{
	if (argc != 2)
	{
		std::cout << "Error, enter the argumets : <input file> <output file>" << std::endl;
		return 1;
	}
	return 0;
}

int ReadMatrix(std::istream &inputMatrix, Mat3x3& matrix3x3)
{
	int count = 0;
	for (size_t i = 1; i <= MATRIX3X3_SIZE; i++)
	{
		for (size_t m = 1; m <= MATRIX3X3_SIZE; m++)
		{
			if (!(inputMatrix >> matrix3x3[i][m]))
			{
				std::cout << "The matrix is not filled completely" << std::endl;
				return 1;
			}
		}
	}
	return 0;
}

void Exclude(Mat3x3& matrix3x3, std::array<std::array<double, 3>, 3>& matrix2x2, int x, int y)
{
	int px = 1, py = 1;
	for (size_t i = 1; i <= MATRIX3X3_SIZE; i++)
	{
		if (x == i)
		{
			continue;
		}
		py = 1;
		for (size_t m = 1; m <= MATRIX3X3_SIZE; m++)
		{
			if (y == m)
			{
				continue;
			}
			matrix2x2[px][py] = matrix3x3[i][m];
			py++;
		}
		px++;
	}
}

double Det3(Mat3x3& matrix3x3)
{
	double plusTriangle = (matrix3x3[1][1] * matrix3x3[2][2] * matrix3x3[3][3]) + (matrix3x3[1][2] * matrix3x3[2][3] * matrix3x3[3][1]) + (matrix3x3[1][3] * matrix3x3[2][1] * matrix3x3[3][2]);
	double negativeTriangle = (matrix3x3[1][3] * matrix3x3[2][2] * matrix3x3[3][1]) + (matrix3x3[1][2] * matrix3x3[2][1] * matrix3x3[3][3]) + (matrix3x3[1][1] * matrix3x3[2][3] * matrix3x3[3][2]);
	if ((plusTriangle - negativeTriangle) == 0)
	{
		std::cout << "Нельзя получить определитель" << std::endl;
		return 0;
	}
	return (plusTriangle - negativeTriangle);
}

double Det2(Mat2x2& matrix2x2)
{
	return matrix2x2[1][1] * matrix2x2[2][2] - matrix2x2[1][2] * matrix2x2[2][1];
}

void TransportMatrix(Mat3x3& reverseMatrix, Mat3x3& transportMatrix)
{
	for (size_t i = 1; i <= MATRIX3X3_SIZE; i++)
	{
		for (size_t m = 1; m <= MATRIX3X3_SIZE; m++)
		{
			transportMatrix[i][m] = reverseMatrix[m][i];
		}
	}
}

void MatrixMultiplication(Mat3x3& transportMatrix, double det)
{
	for (int i = 1; i <= MATRIX3X3_SIZE; i++)
	{
		for (int m = 1; m <= MATRIX3X3_SIZE; m++)
		{
			transportMatrix[i][m] = transportMatrix[i][m] * (1 / det);
		}
	}
}

void GetReverseMatrix(Mat3x3& matrix3x3, Mat2x2& matrix2x2, Mat3x3& reverseMatrix)
{
	int coefficient = 1;
	for (int i = 1; i <= MATRIX3X3_SIZE; i++)
	{
		for (int m = 1; m <= MATRIX3X3_SIZE; m++)
		{
			Exclude(matrix3x3, matrix2x2, i, m);
			reverseMatrix[i][m] = coefficient * Det2(matrix2x2);
			coefficient = -coefficient;
		}
	}
}

void PrintMatrix(Mat3x3& transportMatrix)
{
	for (int i = 1; i <= MATRIX3X3_SIZE; i++)
	{
		for (int m = 1; m <= MATRIX3X3_SIZE; m++)
		{
			std::cout << (round(transportMatrix[i][m] * 1000) / 1000) << " ";
		}
		std::cout << "\n";
	}
}

int GetInvertMatrix(Mat3x3& matrix3x3, Mat2x2& matrix2x2, Mat3x3& reverseMatrix, Mat3x3& transportMatrix)
{
	double detMatrix = Det3(matrix3x3);
	if (detMatrix == 0) return 1;
	GetReverseMatrix(matrix3x3, matrix2x2, reverseMatrix);
	TransportMatrix(reverseMatrix, transportMatrix);
	MatrixMultiplication(transportMatrix, detMatrix);
	PrintMatrix(transportMatrix);
	return 0;
}

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int result = ValidationArguments(argc);
	if (result == 1) return 1;
	Mat3x3 matrix3x3, reverseMatrix, transportMatrix;
	Mat2x2 matrix2x2;
	std::ifstream fileInput(argv[1]);
	if (!fileInput)
	{
		std::cout << "File(-s) not open" << std::endl;
		return 1;
	}
	result = ReadMatrix(fileInput, matrix3x3);
	if (result == 1) return 1;
	if (GetInvertMatrix(matrix3x3, matrix2x2, reverseMatrix, transportMatrix) == 1) return 1;
	return 0;
}
