#pragma once
#include "array.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

struct listArc
{
	int start = 0;
	int end = 0;
	listArc* next = nullptr;
};

listArc* makeList(int** arr, const size_t size);

void printList(listArc* list);

void deleteList(listArc* list);

// Создание копии списка дуг
listArc* copy(listArc* original);

// Удалить из списка дуг все дуги, в которые входит вершина с номером vertex
// Номер вершин считается с единицы
void deleteVertexFromList(listArc*& list, int vertex);
void deleteVertexFromList(listArc*& list, int vertex, int& countOperation);

// Удалить из списка первую дугу
void deleteFirstArc(listArc*& list);

// Количество различных вершин в списке list
int listSize(listArc* list, const size_t size, int& countOperation);

int* reductio(listArc*& list, const size_t size, int* inCover, size_t& size_cover, size_t & renum_size, const int ParamK, int& countOperation, std::vector<std::string>& trace);

bool generate(listArc* list, const size_t size, int* inCover, size_t& size_cover, int* renumeration, int* arr, size_t n, size_t k, int& countOperation);

bool generate(listArc* list, const size_t size, int* inCover, size_t& size_cover, int* renumeration, int* arr, size_t n, int& countOperation, const size_t to);

bool generateRevers(listArc* list, const size_t size, int* inCover, size_t& size_cover, int* renumeration, int* arr, size_t n, size_t k, int& countOperation);

bool generateRevers(listArc* list, const size_t size, int* inCover, size_t& size_cover, int* renumeration, int* arr, size_t n, int& countOperation, const size_t from);

bool isItCover(listArc* list, const size_t size, int* renumeration, int* arr, int& countOperation);

bool isItCover(listArc* list, int* arr, size_t size_cover, int& countOperation);

