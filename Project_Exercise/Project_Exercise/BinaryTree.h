#include "stdafx.h"
//#include <queue>

struct node {
    int data;
    struct node* left;
    struct node* right;
};

/*
 Helper function that allocates a new node
 with the given data and NULL left and right
 pointers.
*/
struct node* NewNode(int data);  
/*Give a binary search tree and a number, inserts a new node
 with the given number in the correct place in the tree.
 Returns the new root pointer which the caller should
 then use (the standard trick to avoid using reference
 parameters).*/

struct node* InsertNode(struct node* node, int data) ;
void InorderTraversal(struct node* head);
void PreorderTraversal(struct node* head);
void PostorderTraversal(struct node* head);
struct node* RotateByRoot(struct node* root);
void PrintBinaryTree(struct node* root);
struct node* BinaryTreeToLinkedList(struct node* root);
int MaxDepth(struct node* node);
int MinValueNormal(struct node* node);
int MinValueRecursion(struct node* node);
node *LCA(node *root, node *p, node *q); 
void printLevelOrder(node *root);


