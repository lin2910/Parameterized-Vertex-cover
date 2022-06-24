#pragma once
#include "array.h"

void generate(int** matrix, const size_t size, const int uCount, int* inCover, int*& result, size_t& record, const size_t n, int& countOperation, const size_t to);

bool generate(int** matrix, const size_t size, const int uCount, int* inCover, int*& result, size_t& record, const size_t n, const size_t k, int& countOperation);

bool makeCover(int** matrix, const size_t size, const int uCount, const int* inCover, size_t& record, int& countOperation);

size_t countUinCover(int** matrix, const size_t size, const int* cover, const size_t size_cover, int& countOperation);

void generateRevers(int** matrix, const size_t size, const int uCount, int* inCover, int*& result, size_t& record, const size_t n, int& countOperation, const size_t from);

bool generateRevers(int** matrix, const size_t size, const int uCount, int* inCover, int*& result, size_t& record, const size_t n, const size_t k, int& countOperation);

bool makeReverseCover(int** matrix, const size_t size, const int uCount, const int* inCover, size_t& record, int& countOperation);

