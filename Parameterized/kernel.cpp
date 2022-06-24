#include "kernel.h"
#include <iostream>
#include <vector>




void generate(int** matrix, const size_t size, const int  uCount, int* inCover, int*& result, size_t& record, const size_t n, int& countOperation, const size_t to)
{
	for (size_t i = 0; i < to; i++) {
		if (generate(matrix, size, uCount, inCover, result, record, n, i, countOperation))
		{
			break;
		}
	}
}

bool generate(int** matrix, const size_t size, const int uCount, int* inCover, int*& result, size_t& record, const size_t n, const size_t k, int& countOperation) {
	if (k == -1 || n == -1) {
		if (makeCover(matrix, size, uCount, inCover, record, countOperation)) {
			delete[] result;
			result = copy(inCover, size);
			countOperation += size;
			for (record = 0; record < size; record++)
				if (result[record] == 0)
					break;
			return true;
		}
		return false;
	}
	else {
		for (size_t i = k; i < n; i++)
		{
			inCover[k] = i + 1;
			countOperation++;
			if (generate(matrix, size, uCount, inCover, result, record, i, k - 1, countOperation))
				return true;
		}
	}
	return false;
}

bool makeCover(int** matrix, const size_t size, const int  uCount, const int* inCover, size_t& record, int& countOperation) {
	size_t size_cover = 0;
	for (size_t i = 0; i < size; i++) {
		countOperation++;
		if (inCover[i] == 0)
			break;
		size_cover++;
		countOperation++;

	}


	countOperation++;
	if (uCount == countUinCover(matrix, size, inCover, size_cover, countOperation)) {
		return true;
	}
	return false;
}

size_t countUinCover(int** matrix, const size_t size, const int* cover, const size_t size_cover, int& countOperation) {
	size_t count = 0;

	//дуги между элементами в покрытии и элементами выше
	for (size_t i = 0; i < size_cover; i++)
	{
		for (size_t j = cover[i]; j < size; j++)
		{
			countOperation++;
			if (matrix[cover[i] - 1][j] != 0) {
				countOperation++;
				count++;
			}
		}
	}

	//пропущенные дуги
	size_t size_not_cover;
	int* notInCover = reversArr(cover, size, size_not_cover, countOperation);
	for (size_t i = 0; i < size_not_cover; i++)
	{
		for (size_t j = 0; j < size_cover; j++)
		{
			countOperation++;
			if (notInCover[i] >= cover[j])
				continue;
			if (matrix[notInCover[i] - 1][cover[j] - 1] != 0) {
				countOperation++;
				count++;
			}
		}
	}

	delete[]notInCover;
	return count;
}



void generateRevers(int** matrix, const size_t size, const int  uCount, int* inCover, int*& result, size_t& record, const size_t n, int& countOperation, const size_t from)
{
	for (size_t i = from - 1; i != -1; i--) {
		if (generateRevers(matrix, size, uCount, inCover, result, record, n, i, countOperation))
		{
			break;
		}
		inCover[i] = 0;
		countOperation++;
	}
}

bool generateRevers(int** matrix, const size_t size, const int  uCount, int* inCover, int*& result, size_t& record, const size_t n, const size_t k, int& countOperation) {
	if (k == -1 || n == -1) {
		if (makeReverseCover(matrix, size, uCount, inCover, record, countOperation)) {
			delete[] result;
			//result = copy(inCover, size);
			result = reversArr(inCover, size, record, countOperation);
			return true;
		}
		return false;
	}

	else {
		for (size_t i = k; i < n; i++)
		{
			inCover[k] = i + 1;
			countOperation++;
			if (generateRevers(matrix, size, uCount, inCover, result, record, i, k - 1, countOperation))
				return true;
		}
	}
	return false;
}


bool makeReverseCover(int** matrix, const size_t size, const int  uCount, const int* inCover, size_t& record, int& countOperation) {
	size_t size_cover;
	int* cover = reversArr(inCover, size, size_cover, countOperation);

	countOperation++;
	if (uCount == countUinCover(matrix, size, cover, size_cover, countOperation)) {
		delete[]cover;
		return true;
	}
	delete[]cover;
	return false;
}

