#include <iostream>
#include <iomanip>
#include "stdafx.h"
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

struct BinaryTree
{
	int data;
	struct BinaryTree *left;
	struct BinaryTree *right;
};
//typedef node BinaryTree;
/*
 Helper function that allocates a new node
 with the given data and NULL left and right
 pointers.
*/
struct BinaryTree* NewNode(int data) 
{
	struct BinaryTree* node = new(struct BinaryTree);    // "new" is like "malloc"
	node->data = data;
	node->left = NULL;
	node->right = NULL;

	return(node);
}

struct BinaryTree* Insert(BinaryTree* BT, int data)
{
	//create and insert.
	if(BT == NULL)
	{
		return(NewNode(data)); 
	}
	else
	{
		// Note: The Insertion doesn't create a BST.
		// Try creating a non-BST for testing purpose.
		if (data >= BT->data) 
			BT->left = Insert(BT->left, data);
		else 
			BT->right = Insert(BT->right, data);

		return BT; // return the (unchanged) node pointer 
	}
}

bool isRightSubTreeGreater(BinaryTree *BT, int data)
{
	if(BT == NULL)
		return false;
	else if(BT->right == NULL)
		return false;
	else if(BT->right->data >= data)
	{
		return true;
	}
	else
		return false;
}

bool isLeftSubTreeGreater(BinaryTree *BT)
{
	return true;
}

bool isBSTBrutus(BinaryTree *BT)
{

	return true;
}


bool isBST(BinaryTree *BT)
{

	return true;
}

int main1()
{
	BinaryTree* BT = NULL;
	BT = Insert(BT, 5);
	BT = Insert(BT, 51);
	BT = Insert(BT, 15);
	BT = Insert(BT, 50);
	BT = Insert(BT, 59);
	BT = Insert(BT, 25);
	BT = Insert(BT, 53);
	BT = Insert(BT, 115);

	printf("%d", isBST(BT));
	return 0;
}