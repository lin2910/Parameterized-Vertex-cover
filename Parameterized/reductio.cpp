#include "reductio.h"

listArc* makeList(int** arr, const size_t size) {
	listArc* resultList = new listArc;
	listArc* p;
	listArc* q = resultList;

	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = i + 1; j < size; j++)
			if (arr[i][j] != 0) {
				p = new listArc;
				p->start = i + 1;
				p->end = j + 1;
				p->next = nullptr;
				q->next = p;
				q = q->next;
			}

	}
	deleteFirstArc(resultList);
	return resultList;
}

void printList(listArc* list) {
	listArc* q = list;
	while (q) {
		std::cout << "( " << q->start << ", " << q->end << " ) " << std::endl;
		q = q->next;
	}

}


void deleteList(listArc* list) {
	listArc* p = list;
	listArc* q = list;
	while (q && p) {
		q = q->next;
		delete p;
		p = q;
	}
}

listArc* copy(listArc* original) {
	listArc* copy = new listArc;
	listArc* p = original;
	listArc* q;
	copy->start = p->start;
	copy->end = p->end;
	copy->next = nullptr;
	listArc* t = copy;
	p = p->next;
	while (p) {
		q = new listArc;
		q->start = p->start;
		q->end = p->end;
		t->next = q;
		p = p->next;
		t = t->next;
	}
	return copy;
}


void deleteVertexFromList(listArc*& list, int vertex) {
	listArc* q;
	while (list && (list->start == vertex || list->end == vertex)) {
		q = list;
		list = list->next;
		delete q;

	}
	if (!list)
		return;
	listArc* p;
	listArc* t;

	p = list;
	q = list->next;

	while (q)
		if (q && q->start == vertex || q->end == vertex) {
			t = q;
			q = q->next;
			p->next = q;

			delete t;
		}
		else {
			q = q->next;
			p = p->next;
		}

}

void deleteVertexFromList(listArc*& list, int vertex, int& countOperation) {
	listArc* q;
	while (list && (list->start == vertex || list->end == vertex)) {
		countOperation += 3;
		q = list;
		list = list->next;
		delete q;

	}
	if (!list)
		return;
	listArc* p;
	listArc* t;

	p = list;
	q = list->next;

	while (q)
		if (q && q->start == vertex || q->end == vertex) {
			countOperation+4;
			t = q;
			q = q->next;
			p->next = q;

			delete t;
		}
		else {
			countOperation+2;
			q = q->next;
			p = p->next;
		}

}

void deleteFirstArc(listArc*& list)
{
	listArc* p = list;
	list = list->next;
	delete p;
}


int listSize(listArc* list, const size_t size, int& countOperation)
{
	int* count = new int[size];
	countOperation++;
	countOperation += size;
	for (size_t i = 0; i < size; i++)
	{
		count[i] = 0;
	}
	listArc* q = list;
	while (q) {
		countOperation += 3;
		count[q->start - 1]++;
		count[q->end - 1]++;
		q = q->next;
	}
	int countVertex = 0;
	for (size_t i = 0; i < size; i++)
	{
		countOperation++;
		if (count[i] > 0) {
			countOperation++;
			countVertex++;
		}
	}
	delete[]count;
	return countVertex;
}

int* reductio(listArc*& list, const size_t size, int* inCover, size_t& size_cover, size_t& renum_size, const int ParamK, int& countOperation, std::vector<std::string>& trace) {
	int* count = new int[size];
	int* renumeration = new int[size];
	for (size_t i = 0; i < size; i++)
	{
		renumeration[i] = 0;
	}
	countOperation += size;
	countOperation += size;
	for (size_t i = 0; i < size; i++)
	{
		count[i] = 0;
	}
	countOperation++;
	bool flag = true;
	while (flag) {
		countOperation++;
		flag = false;

		countOperation += size;
		for (size_t i = 0; i < size; i++)
		{
			if (count[i] > 0)
				count[i] = 0;
		}
		listArc* q = list;
		while (q) {
			countOperation += 3;
			count[q->start - 1]++;
			count[q->end - 1]++;
			q = q->next;
		}

		for (size_t i = 0; i < size; i++)
		{
			if (count[i] == 0) { // изолированные вершины
				countOperation++;
				if (renumeration[i] != -1) {
					trace.push_back("”дал€ем изолированную вершину " + std::to_string(i + 1) + '.');
					//std::cout << "”дал€ем изолированную вершину " << i+1 << std::endl;
				}
				countOperation++;
				renumeration[i] = -1;
			}
			if (count[i] == 1) {
				listArc* p = list;  // ищем соседнюю с вис€чей вершиной 
				while (p) {
					countOperation++;
					if (p->start == i + 1) {
						countOperation++;
						flag = true;
						trace.push_back("ƒл€ вершины " + std::to_string(i + 1) + " помещаем в покрытие ее соседа " + std::to_string(p->end) + "; k =" + std::to_string(ParamK) + '.');
						renumeration[p->end-1] = -1;
						//std::cout << "add in cover " << p->end << std::endl;
						add(inCover, size, size_cover, p->end, countOperation);
						deleteVertexFromList(list, p->end, countOperation);
						break;
					}
					else {
						countOperation++;
						if (p->end == i + 1) {
							countOperation++;
							flag = true;
							trace.push_back("ƒл€ вершины " + std::to_string(i + 1) + " помещаем в покрытие ее соседа " + std::to_string(p->start) + "; k =" + std::to_string(ParamK) + '.');
							renumeration[p->start-1] = -1;
							//std::cout << "add in cover " << p->start << std::endl;
							add(inCover, size, size_cover, p->start, countOperation);
							deleteVertexFromList(list, p->start, countOperation);
							break;
						}
					}
					countOperation++;
					p = p->next;
				}
			}
			if (count[i] > ParamK && renumeration[i] >=0) {
				flag = true;
				
				renumeration[i] = -1;
				trace.push_back("ѕомещаем в покрытие вершину " + std::to_string(i + 1) + " степени " + std::to_string(count[i]) +  " больше k; k = " + std::to_string(ParamK) + '.');
				//std::cout << "ѕомещаем в покрытие вершину " << i + 1 << std::endl;
				add(inCover, size, size_cover, i + 1, countOperation);
				deleteVertexFromList(list, i + 1);
			}
		}
	}
	int j = 0;
	// Ќесколько раз проходим в поиске новых вершин дл€ добавлени€ в покрытие
	countOperation += 2 * size;
	for (size_t i = 0; i < size; i++)
	{
		if (count[i] > 1) {
			renumeration[i] = ++j;
		}
	}
	renum_size = j;
	for (size_t i = 0; i < size; i++)
	{
		if (renumeration[i] < 0) {
			renumeration[i] = ++j;
		}
	}

	delete[]count;
	return renumeration;
}



bool generate(listArc* list, const size_t size, int* inCover, size_t& size_cover, int * renumeration, int* arr, size_t n, size_t k, int& countOperation) {
	if (k == -1 || n == -1) {
		// проверка 

		countOperation++;
		if (isItCover(copy(list), size, renumeration, arr, countOperation)) {
			for (size_t j = 0; j < size; j++)
			{
				countOperation++;
				if (arr[j] == 0)
					break;
				for (size_t k = 0; k < size; k++)
				{
					countOperation++;
					if (renumeration[k] == arr[j])
					{
						add(inCover, size, size_cover, k + 1, countOperation);
						break;
					}
				}
			}
			return true;
		}
		

	}
	else {
		for (size_t i = k; i < n; i++)
		{
			countOperation++;
			arr[k] = i + 1;
			countOperation++;
			if (generate(list, size, inCover, size_cover, renumeration, arr, i, k - 1, countOperation))
				return true;
		}
	}
	return false;
}

bool generate(listArc* list, const size_t size, int* inCover, size_t& size_cover, int* renumeration, int* arr, size_t n, int& countOperation, const size_t to) {
	for (size_t i = 0; i < to ; i++) {
		countOperation++;
		if (generate(list, size, inCover, size_cover, renumeration, arr, n, i, countOperation ))
			return true;
	}
	return false;
}


bool generateRevers(listArc* list, const size_t size, int* inCover, size_t& size_cover, int* renumeration, int* arr, size_t n, size_t k, int& countOperation) {
	if (k == -1 || n == -1) {
		// проверка 
		countOperation++;
		size_t arr_size = 0;
		for (size_t i = 0; i < size; i++) {
			if (arr[i] == 0)
				break;
			countOperation++;
			arr_size++;
		}

		countOperation++;
		if (isItCover(copy(list), size, renumeration, reversArr(arr, size, arr_size, countOperation), countOperation)) {
			for (size_t j = 0; j < size; j++)
			{

				countOperation++;
				if (arr[j] == 0)
					break;
				for (size_t k = 0; k < size; k++)
				{
					countOperation++;
					if (renumeration[k] == arr[j])
					{
						add(inCover, size, size_cover, k + 1, countOperation);
						break;
					}
				}
			}
			return true;
		}
	}
	else {
		for (size_t i = k; i < n; i++)
		{
			countOperation++;
			arr[k] = i + 1;
			countOperation++;
			if (generateRevers(list, size, inCover, size_cover, renumeration, arr, i, k - 1, countOperation))
				return true;
		}
	}
	return false;
}

bool generateRevers(listArc* list, const size_t size, int* inCover, size_t& size_cover, int* renumeration, int* arr, size_t n, int& countOperation, const size_t from) {
	for (size_t i = from - 1; i != -1; i--) {
		countOperation++;
		if (generateRevers(list, size, inCover, size_cover, renumeration, arr, n, i, countOperation))
			return true;
		countOperation++;
		arr[i] = 0;
	}
	return false;
}

bool isItCover(listArc* list, const size_t size, int * renumeration, int* arr, int& countOperation) {
	for (size_t i = 0; i < size; i++)
	{
		countOperation++;
		if (arr[i] == 0)
			break;
		for (size_t j = 0; j < size; j++)
		{
			countOperation++;
			if (renumeration[j] == arr[i])
			{
				//std::cout << renumeration[j] << ' ' << j +1 << std::endl;
				deleteVertexFromList(list, j + 1);// удал€ть соответсвующую перенумерованную вершину
				break;
			}
		}
	}
	if (!list)
		return true;
	return false;
}

bool isItCover(listArc* list, int* arr, size_t size_cover, int& countOperation)
{
	for (size_t i = 0; i < size_cover; i++)
	{
		deleteVertexFromList(list, arr[i]);
	}
	countOperation++;
	if (!list)
		return true;
	return false;
}
