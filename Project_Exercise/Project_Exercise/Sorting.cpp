#include "stdafx.h"
#include "Sorting.h"
#include <iostream>
#include <queue>

using namespace std;
#define MAX 128

// Tournament method - 2nd Largest 
void largest_and_second_largest(int a[],int n,int *m,int *s)
{
	int *I,                       //stores the losers
		size,                     //stores the current level in the tree
		i,j,                      //indexed
		lu,                       //stores the last compared element in the
		//current level
		max,                      //stores the largest number
		slarge,                   //stores the second largest number
		sindex;                   //stores the index of the second largest number
	//void swap(int *a,int *b);

	size=1; lu=-1;                //initialize - level one and no number used
	I=(int *)malloc(sizeof(int)*n);
	for (i=0;i<n;i++)             //initialize - no loser yet
		I[i]=-1;
	for (;;) {                    //loop until size-1 becomes more than n
		i=size-1;
		if (i>=n)
			break;                    //loop exit
		j=size+i;
		if (j>=n && i!=n-1)         //if the last element of the array has
			j=n-1;                    //not been considered, use it
		if (j>=n)
			if (lu<0)
				break;                  //loop exit
			else {
				j=lu;                   //store the used number in lu
				lu=-1;
			}
			for (;;) {                  //another seemingly infinite loop
				if (a[i]>a[j])            //swap if out of order
					swap(&a[i],&a[j]);
				else
					I[i]=I[j];              //otherwise, just store in the loser list
				I[j]=i;
				i=j+size;                 //next number
				if (i>=n)
					break;                  //inner loop exit
				else {
					j=i+size;               //next
					if (j>=n && i!=n-1)     //if the last element of the array has
						j=n-1;                //not been considered, use it
					if (j>=n)
						if (lu>0) {
							j=lu;               //take in last used
							lu=-1;              //empty last used
						}
						else {
							lu=i;               //if there is no earlier last used, store the
							//current number as last used
							break;
						}
				}
			}
			size=2*size;                //move to the next level
	}
	max=a[n-1];                   //largest is found
	sindex=I[n-1];                //find the second largest by simple comparison
	slarge=a[sindex];             //in the loser list for the maximum
	while (sindex!=-1) {
		sindex=I[sindex];
		if (sindex!=-1 && a[sindex]>slarge)
			slarge=a[sindex];
	}
	*m=max;
	*s=slarge;
	free(I);                      //free and return
}

void threeWayPartition(int data[], int size, int low, int high) {
	int p = -1;
	int q = size;
	for (int i = 0; i < q;) {
		if (data[i] < low) {
			swap(data[i], data[++p]);
			++i;
		} else if (data[i] >= high) {
			swap(data[i], data[--q]);
		} else {
			++i;
		}
	}
}

int partition(int s[], int l, int h)
{
	int i = l, j = h;
	int pivot = s[h];
	while( i < j)
	{
		// i < j check is because we swap pivot with ith elt. 
		// we are concerned about correctness of i. correcting one of these (i or j) will have effect on both
		while( s[i] <= pivot && i < j)  
			i++;
		while (s[j] >= pivot )	
			j--;
		if( i < j)					// An extra check to ensure we don't do swap if above while 
			swap(s[i], s[j]);		// The place where elements are not in order wrt pivot element
	}
	swap (s[i], s[h]);		// pivot brought to its correct position. 
	return i;					// Return the correct position of pivot
}

// { 45, 56, 1, 31, 213, 123, 789, 543, 2, 4, 3, 89 };
// { 45, 56, 1, 31, 3, 4, 2,	 89,		 789, 123, 213, 543 };
// { 45, 56, 1, 31, 3, 4, 2,	 89,		 789, 123, 213, 543 };
// high is length of (array - 1)
void quicksort(int s[], int low, int high)
{
	if (low < high)
	{
		int k = partition(s, low, high);
		for (int i = 0; i < k; i++)
			printf("%d\t", s[i]);
		for (int i = k; i <= high; i++)
			printf("%d\t", s[i]);
		cout << endl;
		quicksort(s, low, k-1);
		quicksort(s, k+1, high);
	}
}

void mergesort(int s[], int low, int high)
{
	int i; /* counter */
	int middle; /* index of middle element */
	if (low < high) {
		middle = low + (high - low) / 2;
		mergesort(s, low, middle);
		mergesort(s, middle + 1, high);
		merge(s, low, middle, high);
	}
}

void merge(int s[], int low, int middle, int high)
{
	int i; /* counter */
	queue<int> buffer1; 
	queue<int> buffer2;  /* buffers to hold elements for merging */
	
	for (i=low; i<=middle; i++) 
		buffer1.push(s[i]);
	for (i=middle+1; i<=high; i++) 
		buffer2.push(s[i]);
	i = low;

	while (!(buffer1.empty()) && !(buffer2.empty())) {
		if (buffer1.front() <= buffer2.front()){
			s[i++] = buffer1.front();
			buffer1.pop();
		}
		else{
			s[i++] = buffer2.front();
			buffer2.pop();
		}
	}
	while (!(buffer1.empty())){
			s[i++] = buffer1.front();
			buffer1.pop();
		}
	while (!(buffer2.empty())) {
			s[i++] = buffer2.front();
			buffer2.pop();
		}
}