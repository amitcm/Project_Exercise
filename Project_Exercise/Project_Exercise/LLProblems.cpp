#include "stdafx.h"
#include <string>
#include "stdio.h"
#include <iostream>
#include <utility>
#include <queue>

using namespace std;

int iMax = 0;

struct node
{
	int data;
	struct node* next;
};

//Mathematical equation in VS like we write in LaTex

/* 
For a Link list, I'm going to follow these convention:

struct node* head; 
head is going to be a pointer to the FIRST node in the list. 
Just a plain pointer! Stored in a stack as it's a local pointer. head is an Ordinary local pointer variable.

The empty list is presented by a NULL head pointer.

The last node contains a NULL in its .next field. It can be used to mark the end of the List.

All pointers to a node is simply declared as 
struct node* pNode;

Pointers to pointers to nodes are declared as 
struct node** ppNode; 
Such pointers to pointers to Nodes are often called "reference pointers".
Conventionally, refer them as headRef and declare as:
struct node** headRef;

Refer the sketch in case of doubt.

*******************************************************************************

Common features of Linked List:
1. Pass the list by passing the head pointer. It merely passes the address of the list. 
The List remains at only one place[No duplicate], where it was allocated.

2. Iterate over the Link List by using a local pointer. 
struct node* current = head;
current is The local pointer that points to a node.
while(current != NULL)
{
	do something.
	current = current->next;
}


********************************************************************************

3 STEP LINK-IN FEATURE:

1. Allocate - 
		Allocate new node in heap and set data.

2. Link next - 
		Set .next pointer of new node to point to current head of the List. 
		REMEMBER: This is just a pointer assignment.
		newNode->next = head; that's it.
		Assigning one pointer to another makes it them to point to the same thing.

3. Link head -
		Change the head pointer to point to head.
		head = newNode;  
		Making this newNode to be pointed by head. 
		newNode [is a struct node*] is a heap address and it should, also, be pointed by head to maintain the above conventions.

*******************************************************************************

REFERENCE PARAMETER COMPLICATION in here!!

whenever we wish to change a variable we pass to a function, 
we must send a reference to it to get its actual memory location reflected.
for example, whenever adding a new node we need to update the head [which is a struct node*]. 
So we must send address of head. i.e, something like struct node** head or &head.

BUT WE WILL USE ANOTHER NAME TO MAKE THE DISTINCTION:
		
		struct node** headRef;
headRef is not the actual pointer variable 
that points to the beginning of the list, rather it is the reference to the head.
Refer page 15 of LLBasics, if ever faced with a problem.

******************************************************************************

Code Techniques:

1. Iterate down the list.
2. Changing a Pointer using a reference pointer
3. Build - At head with Push()
4. Build - with tail pinter
5. Build - Special Case + Tail pointer
6. Build - Temporary Dummy Node
7. Build - Local References

****************************************************************************

int Length(struct node* head);
struct node* Build123();
void Push(struct node** headRef, int data);

Seems quite good way, but, ... interviewer ko bhi samajh me aani chahiye :)
struct node* BuildWithLocalRef()
{
	struct node* head = NULL;
	struct node** lastPtrRef = &head;
	
	for(int i = 4; i < 10; i++)
	{
		Push(lastPtrRef, i);					// lastPtrRef still points to the address of head. So, Push adds just after the head.
												// All this operation didn't do anything to lastPtrRef.
		lastPtrRef = &((*lastPtrRef)->next);    // (*lastPtrRef) is the head and its 'next' gives the node recently added
												// So, lastPtrRef is now pointing to the pointer to new node. This is also
												// the last node and hence signifies its name.
	}

	return head;								// head was pointed by lastPtrRef and the first Push made it to point to some real node.
												// Since then it has not been modified.
}
Cool right?

Other functions:
struct node* AddAtHead();
struct node

***************************************************************************************
***************************************************************************************
*/

struct node* NewNode(int data)
{
	struct node* newNode;
	newNode = (struct node* )malloc(sizeof(struct node));
	if(newNode != NULL)
	{
		newNode->data = data;
		newNode->next = NULL;
	}
	return newNode;
}
// adds at the head.
void Push(struct node** headRef, int data)
{
	struct node* temp = NewNode(data);
	if(temp != NULL)
	{
		temp->next = *headRef;
		*headRef = temp;				// Remember we pass headRef [struct node** ] just because 
										// we want to keep the head pointer persistently across different functions
	}
}

struct node* BuildWithLocalRef()
{
	struct node* head = NULL;
	struct node** lastPtrRef = &head;
	
	for(int i = 4; i < 10; i++)
	{
		Push(lastPtrRef, i);					// lastPtrRef still points to the address of head. So, Push adds just after the head.
												// All this operation didn't do anything to lastPtrRef.
		lastPtrRef = &((*lastPtrRef)->next);    // (*lastPtrRef) is the head and its 'next' gives the node recently added
												// So, lastPtrRef is now pointing to the pointer to new node. This is also
												// the last node and hence signifies its name.
	}

	return head;								// head was pointed by lastPtrRef and the first Push made it to point to some real node.
												// Since then it has not been modified.
}

void PrintList(struct node* head)
{
	struct node* current = head;
	while(current != NULL)
	{
		printf("%d\t",current->data);
		current = current->next;
	}
	printf("\n\n");
}

void PrintList(struct node* head, int n)
{
	struct node* current = head;
	while(current != NULL && --n >= 0 )
	{
		printf("%d\t",current->data);
		current = current->next;
	}
	printf("\n\n");
}

int Count(struct node* head, int searchFor)
{
	if(head == NULL)
		return 0;
	struct node* current  = head;
	while(current != NULL)
	{
		if(current->data == searchFor)
			return (1 + Count(current->next, searchFor));
		else
			return Count(current->next, searchFor);
	}
}

int GetNth(struct node* head, int index)
{
	if(head == NULL)
		return 0;
	struct node* current  = head;
	while(current != NULL && ((index--) > 0))
	{
		current = current->next;
	}
	if(current != NULL)
		return current->data;
	else
		return NULL;
}

void FrontBackSplit(struct node* source, struct node** frontRef, struct node** backRef)
{
	struct node *pFast = source, *pSlow = source, *temp = source, *temp1 = source;
	bool bOdd = false;
	while( pFast != NULL )
	{
		if( pFast->next != NULL )
		{
			temp = pSlow->next;
			temp1 = pSlow;
			pFast = pFast->next->next;
			pSlow = pSlow->next;
		}
		else
		{
			temp = pSlow->next;
			pSlow->next = NULL;
			pFast = pFast->next;
			bOdd = true;
			break;
		}
	}
	*frontRef = source;
	*backRef = temp;
	if(!bOdd)
		temp1->next = NULL;
}

void Reverse(struct node **headRef)
{
	struct node *current = *headRef, *temp = NULL;
	*headRef = NULL;

	while(current->next != NULL)
	{
		temp = current->next;

		current->next = *headRef;
		*headRef = current;
				
		current = temp;
	}
	current->next = *headRef;
	*headRef = current;
}

bool IsCycle(struct node * head)
{
	struct node *current = head, *pFast = head, *pSlow = head;
	if( head == NULL)
		return false;
	else
	{
		while(pFast != NULL)
		{
			if(pFast->next == NULL)
				return false;
			pFast = pFast->next->next;
			pSlow = pSlow->next;
			
			if(pFast == pSlow)
				return true;
		}
		return false;
	}
}

void CreateSimpleCycle(struct node *head)
{
	struct node *current = head, *prev = head;
	int n = 0;
	while(current != NULL)
	{
		prev = current;
		current = current->next;
		n++;
	}
	iMax = n;
	n = n / 2;
	current = head;
	while(n-- >= 0)
		current = current->next;
	prev->next = current;
}

// Given is a sorted List. To be done in a single traversal. Easy right?
void RemoveDuplicates(struct node * head)
{
	struct node *current = head, *temp = head;
	while(current != NULL)
	{
		if(current->next != NULL)					// Must check .next of next node before we carry forward.
		{
			temp = temp->next;
			if(temp->data == current->data)
			{
				current->next = temp->next;
			}
			current = current->next;
			temp = current;
		}
	}
}

// Take the node from the front of source
// move it to the front of the dest.
// Error when called with an empty source List
void MoveNode(struct node **destHeadRef, struct node **sourceHeadRef)
{
	struct node *temp;
	if(*sourceHeadRef == NULL)
		return;
	else
	{
		temp = (*sourceHeadRef);
		Push(destHeadRef, (*sourceHeadRef)->data);
		*sourceHeadRef = (*sourceHeadRef)->next;
		// Remove node pointed by temp in heap.
		free(temp);
	}
}

// a1->b1->a2->b2->a3->b3->a4->a5->a6->NULL
struct node* ShuffleMerge(struct node *a, struct node *b)
{
	struct node *temp, *temp1;
	int n = 0;
	while( a != NULL || b != NULL )
	{
		if( a != NULL )
		{
			MoveNode(&temp, &a);
			n++;
		}
		if( b != NULL )
		{
			MoveNode(&temp, &b);
			n++;
		}
	}
	temp1 = temp;				//We must return the beginning of the List. we're going to modify temp to make it point to the last elt.
								// So preserving it.
	while(--n > 0)
		temp = temp->next;		// Must terminate the list.
	temp->next = NULL;
	return temp1;				// Return the beginning of the List.
}

struct node* RecurShuffleMerge(struct node *a, struct node *b)
{
	struct node *temp = NULL;

	if( a == NULL)
		return b;
	else if (b == NULL)
		return a;
	else
	{
		a->next = RecurShuffleMerge(b, a);
	}
	return a;
}

// Compute a new sorted list that represents the intersection of two given sorted lists
// The new list should be made with its own memory.
// 
struct node* SortedIntersect(struct node *a, struct node *b)
{
	return a;
}

void Append(struct node **aRef, struct node **bRef)
{
	struct node *current;
	if( (*aRef) == NULL)
		(*aRef) = (*bRef);
	else
	{
		current = (*aRef);						// Always try to do traversal through a local pointer variable.
												// Reduces the possibility of an error.
		while(current->next != NULL)
			current = current->next;
		current->next = (*bRef);
	}
}

struct node* SortedMerge(struct node *a, struct node *b)
{
	struct node *temp = NULL;
	struct node **lastPtrRef = &temp;		// Used to do operations. node ** chosen to suit for MoveNode but, primarily to store an empty temp.
	while(1)
	{
		if(a == NULL)
		{
			*lastPtrRef = b;
			break;
		}
		else if(b == NULL)
		{
			*lastPtrRef = a;
			break;
		}
		if(a->data <= b->data)
			MoveNode(lastPtrRef, &a);
		else
			MoveNode(lastPtrRef, &b);

		lastPtrRef = &((*lastPtrRef)->next);
	}
	return temp;
}

void MergeSort(struct node** headRef)
{
	struct node *head = *headRef;
	struct node *a, *b;
	if((head == NULL) || (head->next == NULL))
		return;
	else
	{
		FrontBackSplit(head, &a, &b);

		MergeSort(&a);
		MergeSort(&b);

		*headRef = SortedMerge(a, b);
	}
}



int main1()
{
	struct node *LL = NULL, *FL = NULL, *BL = NULL, *SL = NULL;
	//Push(&LL, 9);
	LL = BuildWithLocalRef();
	//Push(&LL, 5);
	PrintList(LL);
	printf("\n%d\n", Count(LL, 5));
	printf("\n%d\n", GetNth(LL, 5));
	
	FrontBackSplit(LL, &FL, &BL);
	PrintList(FL);
	PrintList(BL);
	SortedMerge(FL, BL);
	PrintList(FL);
	MergeSort(&LL);
	//Append(&FL, &BL);
	//PrintList(FL);
	//MoveNode(&FL, &BL);
	//PrintList(FL);
	//PrintList(BL);
	//SL = ShuffleMerge(FL, BL);
	//PrintList(SL);
	//Reverse(&SL);
	//PrintList(SL);

	Reverse(&LL);
	PrintList(LL);
	printf("\n%d\n", (IsCycle(LL) ? 1 : 0));
	//CreateSimpleCycle(LL); //This function must be called before 1st PrintList(LL, iMax) call or make change to iMax through macro.
	//PrintList(LL, iMax + iMax + 2);
	//printf("\n%d\n", (IsCycle(LL) ? 1 : 0));
	RemoveDuplicates(LL);
	PrintList(LL);		
	return 0;
}