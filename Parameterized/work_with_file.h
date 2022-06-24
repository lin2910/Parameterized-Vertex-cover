#pragma once
#include <string>
#include <iostream>
#include <cassert>
#include <fstream>
#include <vector>

using namespace std;

int get_number(const char* filename);

int* get_array(const char* filename);

int* get_array(const char* filename, size_t& size);

int** get_array(const char* filename, size_t& size, size_t& uCount);

void put_number(const char* filename, const size_t number);

void put_number(const char* filename, const double time);

void put_number(const char* filename, const double time, const int number);

void put_trace(const char* filename, std::vector<std::string>& trace);

void put_string(const char* filename, const char* str);

void put_array(const char* filename, const int* array, const size_t size);

void put_number_in_end(const char* filename, const double time, const int number);

void put_number_in_end(const char* filename, const int number);

void put_array_in_end(const char* filename, const int* array, const size_t size);

