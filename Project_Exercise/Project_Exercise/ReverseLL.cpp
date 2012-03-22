#include <iostream>
#include <malloc.h>
#include "stdafx.h"
using namespace std;
struct Node
{
	int data;
	struct Node* link;
};

/*
 Helper function that allocates a new node
 with the given data and NULL left and right
 pointers.
*/
struct Node* NewNode(int data) 
{
	struct Node* node = new(struct Node);    // "new" is like "malloc"
	node->data = data;
	node->link = NULL;
	return(node);
}
  
/*Give a binary search tree and a number, inserts a new node
 with the given number in the correct place in the tree.
 Returns the new root pointer which the caller should
 then use (the standard trick to avoid using reference
 parameters).*/

struct Node* InsertNode(struct Node* node, int data) 
{
	// 1. If the tree is empty, return a new, single node
	if (node == NULL) 
	{
		return(NewNode(data));
	}  
	else 
	{

		// 2. Otherwise, recur down the tree
		node->link = InsertNode(node->link, data);
		return(node); // return the (unchanged) node pointer
	}
}

void PrintList(struct Node* head)
{
	if(head != NULL)
	{
		printf("%d \n",head->data);
		head = head->link;
	}
}


void reverseList(struct Node** head)
{
	struct Node* temp = *head;
	struct Node* current = *head;
	*head = NULL;
	while(current->link != NULL)
	{
		temp = current->link;
		current = *head;
		*head = current;
		current = temp;
	}

}

int main()
{

	return 0;
}