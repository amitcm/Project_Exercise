#include "stdafx.h"
#include "HeapEtAl.h"

void Heap::heapify(int root)
{
	if((2 * root + 2) > index)
		return;
	else
	{
		int maxIndex = vector_heap[2*root + 1] > vector_heap[2*root + 2] ? (2*root + 1) : (2*root + 2);
		if(vector_heap[root] < vector_heap[maxIndex])
		{
			swap(vector_heap[root], vector_heap[maxIndex]);
			root = maxIndex;
			heapify(root);
		}
	}
}

void Heap::addtoheap(int heapentry)
{
	int current = index + 1;
	vector_heap.push_back(heapentry);
	index++;
	int parent = (current - 1) / 2;
	while(heapentry > vector_heap[parent])
	{
		swap(vector_heap[current], vector_heap[parent]);
		current = parent;
		parent = (current - 1) / 2;
	}
}
int Heap::removefromheap()
{
	int root;
	if(index >= 0)
	{
		root = vector_heap[0];
		vector_heap[0] = vector_heap[index];
		vector_heap.pop_back();
		index--;
		heapify(0);
		return root;
	}
	else
		return NULL;
}

vector<int> Heap::heapsort()
{
	vector<int> vector_sorted;
	while(index >= 0)
		vector_sorted.push_back(removefromheap());
	return vector_sorted;
}

