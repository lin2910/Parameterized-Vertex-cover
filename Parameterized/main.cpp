#include <string>
#include <iostream>

#include "work_with_file.h"
#include "crtdynmem.h"
#include "reductio.h"

using namespace std;

int main(int argc, const char* argv[]) {
	setlocale(LC_ALL, "Russian");
	if (argc == 6) {
		try {
			const char* InputFile = argv[1];
			const char* InputFile_k = argv[2];
			const char* OutputFile_r = argv[3];
			const char* OutputFile_v = argv[4];
			const char* OutputFile_t = argv[5];

			size_t size;
			size_t uCount;
			int ParamK = get_number(InputFile_k);

			int** arr = get_array(InputFile, size, uCount);

			listArc* list = makeList(arr, size);
			listArc* original = copy(list);

			int* inCover = new int[size];
			int* temp = new int[size];
			for (size_t i = 0; i < size; i++) {
				inCover[i] = 0;
				temp[i] = 0;
			}
			size_t record = 0;
			size_t size_cover = 0;
			size_t renum_size = 0;
			int countOperation = 0;
			bool isSolveExist = false;

			vector<string> trace;

			//начало отсчета времени
			clock_t start = clock();

			// Редуция данных
			int* renumeration = reductio(list, size, inCover, size_cover, renum_size, ParamK, countOperation, trace);

			countOperation++;
			if (size_cover <= ParamK) {
				countOperation++;
				if (isItCover(copy(original), inCover, size_cover, countOperation)) {
					countOperation++;
					isSolveExist = true;
				}
				else {
					// обработка ядра
					trace.push_back("Обрабатываем ядро из " + to_string(listSize(list, size, countOperation)) + " вершин.");

					generate(list, size, inCover, size_cover, renumeration, temp, renum_size, countOperation, renum_size / 2);
					if (isItCover(copy(original), inCover, size_cover, countOperation)) {
						countOperation++;
						if (size_cover <= ParamK)
							isSolveExist = true;
						else
							isSolveExist = false;
					}
					else {
						countOperation++;
						if (size % 2 == 0)
							generateRevers(list, size, inCover, size_cover, renumeration, temp, renum_size, countOperation, renum_size / 2);
						else
							generateRevers(list, size, inCover, size_cover, renumeration, temp, renum_size, countOperation, renum_size / 2 + 1);
						countOperation++;
						if (size_cover <= ParamK)
							isSolveExist = true;
						else
							isSolveExist = false;
					}
				}
			}
			// конец отсчета времени
			clock_t stop = clock();

			// количество секунд
			double seconds = double(stop - start) / CLOCKS_PER_SEC;


			if (isSolveExist) {
				put_array(OutputFile_r, inCover, size_cover);
				put_number(OutputFile_v, size_cover);
			}
			else {
				put_string(OutputFile_r, "No solution");
				put_number(OutputFile_v, (double)0);
			}
			put_number(OutputFile_t, seconds, countOperation);
			put_trace(OutputFile_t, trace);

			deleteList(list);
			deleteList(original);
			delete[]renumeration;
			delete[]inCover;
			delete[]temp;
			for (size_t i = 0; i < size; i++)
				delete[]arr[i];
			delete[]arr;


		}
		catch (const std::exception& e) {
			cout << "Exeption: " << e.what() << endl;
		}
		//system("pause");
		return 0;
	}

	cout << "Invalid count of arguments" << endl;
	/*
	const char* InputFile = "test.txt"; //"test.txt"
	const char* InputFile_k = "VC1_k.txt";
	const char* OutputFile_r = "VC1_r.txt";
	const char* OutputFile_v = "VC1_v.txt";
	const char* OutputFile_t = "VC1_t.txt";

	size_t size;
	size_t uCount;
	int ParamK = get_number(InputFile_k);

	int** arr = get_array(InputFile, size, uCount);

	listArc* list = makeList(arr, size);
	listArc *original = copy(list);

	int* inCover = new int[size];
	int* temp = new int[size];
	for (size_t i = 0; i < size; i++) {
		inCover[i] = 0;
		temp[i] = 0;
	}
	size_t record = 0;
	size_t size_cover = 0;
	size_t renum_size  = 0;
	int countOperation = 0;
	bool isSolveExist = false;

	vector<string> trace;

	//начало отсчета времени
	clock_t start = clock();

	// Редуция данных
	int* renumeration = reductio(list, size, inCover, size_cover, renum_size, ParamK, countOperation, trace);
	for (size_t i = 0; i < size; i++)
	{
		cout << renumeration[i] << ' ';
	}
	cout << endl;
	printList(list);
	countOperation++;

	if (size_cover <= ParamK) {
		countOperation++;
		if (isItCover(copy(original), inCover, size_cover, countOperation)) {
			countOperation++;
			isSolveExist = true;
		}
		else {
			// обработка ядра
			trace.push_back("Обрабатываем ядро из " + to_string(listSize(list, size, countOperation))+ " вершин.");
			if (generate(list, size, inCover, size_cover, renumeration, temp, renum_size, countOperation, renum_size / 2)) {
				countOperation++;
				if (size_cover <= ParamK)
					isSolveExist = true;
				else
					isSolveExist = false;
			}
			else {
				countOperation++;
				if (size % 2 == 0)
					generateRevers(list, size, inCover, size_cover, renumeration, temp, renum_size, countOperation, renum_size / 2);
				else
					generateRevers(list, size, inCover, size_cover, renumeration, temp, renum_size, countOperation, renum_size / 2 + 1);
				countOperation++;
				if (size_cover <= ParamK)
					isSolveExist = true;
				else
					isSolveExist = false;
			}
		}
	}
	

	// конец отсчета времени
	clock_t stop = clock();

	// количество секунд
	double seconds = double(stop - start) / CLOCKS_PER_SEC;

	if (isSolveExist) {
		put_array(OutputFile_r, inCover, size_cover);
		put_number(OutputFile_v, size_cover);
	}
	else {
		put_string(OutputFile_r, "нет решения");
		put_number(OutputFile_v, (double)0);
	}
	put_number(OutputFile_t, seconds, countOperation);
	put_trace(OutputFile_t, trace);

	deleteList(list);
	deleteList(original); 
	delete[]renumeration;
	delete[]inCover;
	delete[]temp;
	for (size_t i = 0; i < size; i++)
		delete[]arr[i];
	delete[]arr;

	//_CrtDumpMemoryLeaks();
	//*/


	system("pause");
	return 0;
}
