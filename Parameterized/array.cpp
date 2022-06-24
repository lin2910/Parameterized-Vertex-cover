#include "array.h"


void add(int*& arr, size_t size, size_t& size_cover, int toAdd, int& countOperation) {
	for (size_t i = 0; i < size_cover; i++)
		if (arr[i] == toAdd) {
			countOperation++;
			return;
		}
		else
			if (arr[i] > toAdd) {
				countOperation++;
				int t, tt = toAdd;
				size_cover++;
				for (size_t j = i; j < size_cover; j++) {
					t = arr[j];
					arr[j] = tt;
					tt = t;
					countOperation += 2;
				}
				return;
			}
	if (size_cover < size) {
		arr[size_cover++] = toAdd;
		countOperation += 2;
	}
}



int* copy(const int* original, const size_t size) {
	int* copy = new int[size];
	for (size_t i = 0; i < size; i++)
		copy[i] = original[i];
	return copy;
}

int* reversArr(const int* original, const size_t size, size_t& size_cover, int& countOperation) {
	int* revers = new int[size];

	countOperation++;
	size_cover = 0;
	size_t j = 0;
	size_t i = 0;

	for (; i < size; i++)
	{
		countOperation++;
		if (original[i] == 0)
			break;
		while (original[i] - 1 > j) {
			add(revers, size, size_cover, ++j, countOperation);
		}
		countOperation++;
		j++;
	}
	for (size_t i = j + 1; i <= size; i++)
		add(revers, size, size_cover, i, countOperation);
	for (size_t i = size_cover; i < size; i++)
	{
		countOperation++;
		revers[i] = 0;
	}
	return revers;
}

