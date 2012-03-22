#include "stdafx.h"
#include <vector>

using namespace std;
#define SIZE 2

class Heap{
private:
	int index;
	vector<int> vector_heap;
public:
	Heap(): index(-1)/*, vector_heap(0)*/
	{
		vector_heap.reserve(SIZE);
	}
	/*~Heap()
	{

	}*/
	void heapify(int root);
	void addtoheap(int heapentry);
	int removefromheap();
	vector<int> heapsort();
};