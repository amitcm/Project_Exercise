#include<stdio.h>
#include<stdlib.h>
 
/* Link list node */
struct LNode
{
    int data;
    struct LNode* next;
};
 
/* A Binary Tree node */
struct TNode
{
    int data;
    struct TNode* left;
    struct TNode* right;
};
 
/* This function counts the number of nodes in Linked List and then calls
   sortedListToBSTRecur() to construct BST */
struct TNode* sortedListToBST(struct LNode *head);
 
/* The main function that constructs balanced BST and returns root of it.
       head_ref -->  Pointer to pointer to head node of linked list
       n  --> No. of nodes in Linked List */
struct TNode* sortedListToBSTRecur(struct LNode **head_ref, int n);
 
/* UTILITY FUNCTIONS */
 
/* A utility function that returns count of nodes in a given Linked List */
int countLNodes(struct LNode *head);
 
/* Function to insert a node at the beginging of the linked list */
void push(struct LNode** head_ref, int new_data);
 
/* Function to print nodes in a given linked list */
void printList(struct LNode *node);
 
/* Helper function that allocates a new node with the
   given data and NULL left and right pointers. */
struct TNode* newNode(int data);
 
/* A utility function to print preorder traversal of BST */
void preOrder(struct TNode* node);
