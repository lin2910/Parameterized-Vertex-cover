#pragma once


int* copy(const int* original, size_t size);

void add(int*& arr, size_t size, size_t& size_cover, int toAdd, int& countOperation);

int* reversArr(const int* original, const size_t size, size_t& size_cover, int& countOperation);