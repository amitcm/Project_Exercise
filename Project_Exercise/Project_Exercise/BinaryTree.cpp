// Binary Tree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BinaryTree.h"

using namespace std;
/*
 Helper function that allocates a new node
 with the given data and NULL left and right
 pointers.
*/
struct node* NewNode(int data) 
{
	struct node* node = new(struct node);    // "new" is like "malloc"
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return(node);
}
  
/*Give a binary search tree and a number, inserts a new node
 with the given number in the correct place in the tree.
 Returns the new root pointer which the caller should
 then use (the standard trick to avoid using reference
 parameters).*/

struct node* InsertNode(struct node* node, int data) 
{
	// 1. If the tree is empty, return a new, single node
	if (node == NULL) 
	{
		return(NewNode(data));
	}  
	else 
	{
		// 2. Otherwise, recur down the tree
		if (data < node->data) 
			node->left = InsertNode(node->left, data);
		else 
			node->right = InsertNode(node->right, data);
		return(node); // return the (unchanged) node pointer
	}
}

void InorderTraversal(struct node* head)
{
	if(head != NULL)
	{
		InorderTraversal(head->left);
		printf("%d \n",head->data);
		InorderTraversal(head->right);
	}
}

void PreorderTraversal(struct node* head)
{
	if(head != NULL)
	{
		printf("%d \n",head->data);
		PreorderTraversal(head->left);
		PreorderTraversal(head->right);
	}
}

void PostorderTraversal(struct node* head)
{
	if(head != NULL)
	{
		PostorderTraversal(head->left);
		PostorderTraversal(head->right);
		printf("%d \n",head->data);
	}
}

struct node* RotateByRoot(struct node* root)
{
	struct node* newRoot = root->left;
	root->left = newRoot->right;
	newRoot->right = root;
	return newRoot;
}

//struct node* Rotate(struct node* root)
//{
//
//}
void PrintBinaryTree(struct node* root)
{
	return;
}

struct node* BinaryTreeToLinkedList(struct node* root)
{
	struct node* finalList, current;
	/*while(root->left != NULL)
		root = RotateByRoot(root->left);
	finalList = root;*/
	/*while(root->right != NULL)
	{
		while(root->right->left != NULL)
			root->right = Rotate(root->right->left);
	}*/
	return finalList;
}

int MaxDepth(struct node* node)
{
	if(node == NULL)
	{
		return 0;
	}
	else
	{
		int l = MaxDepth(node->left) + 1;
		int r = MaxDepth(node->right) + 1;
		return (l > r ? l : r);
	}
}

int MinValueNormal(struct node* node)
{
	while(node->left != NULL)
		node = node->left;
	return node->data;
}

int MinValueRecursion(struct node* node)
{
	if(node->left == NULL)
		return node->data;
	else
		return MinValueRecursion(node->left);
}

node *LCA(node *root, node *p, node *q) 
{
	if (!root) 
		return NULL;
	if (root == p || root == q) 
		return root;
	node *L = LCA(root->left, p, q);
	node *R = LCA(root->right, p, q);
	if (L && R) 
		return root;  // if p and q are on both sides
	return 
		L ? L : R;  // either one of p,q is on one side OR p,q is not in L&R subtrees
}

void printLevelOrder(node *root) {
	if (!root) return;
	queue<node*> currentLevel, nextLevel;
	currentLevel.push(root);
	while (!currentLevel.empty()) {
		node *currNode = currentLevel.front();
		currentLevel.pop();
		if (currNode) {
			cout << currNode->data << " ";
			nextLevel.push(currNode->left);
			nextLevel.push(currNode->right);
		}
		if (currentLevel.empty()) {
			cout << endl;
			swap(currentLevel, nextLevel);
		}
	}
}


int _tmain_1(int argc, _TCHAR* argv[])
{
	struct node* head;
	head = NewNode(20);
	head = InsertNode(head, 15);
	head = InsertNode(head, 10);
	head = InsertNode(head, 25);
	head = InsertNode(head, 35);
	head = InsertNode(head, 1);
	head = InsertNode(head, 15);
	head = InsertNode(head, 12);
	head = InsertNode(head, 5);
	//Operations here

	/*INPUT
						20
					   /  \
					 15	   25
				    /  \    \
				  10   15	35
				 /  \
				1	12
					/
				   5
	*/
	printf("Inorder traversal: \n");
	InorderTraversal(head);

	printf("Preorder traversal: \n");
	PreorderTraversal(head);

	printf("Postorder traversal: \n");
	PostorderTraversal(head);

	//struct node* LinkedList = BinaryTreeToLinkedList(head);
	int iDepth = MaxDepth(head);
	int iMinN = MinValueNormal(head);
	int iMinR = MinValueRecursion(head);
	printf("Hello World!");
	return 0;
}

