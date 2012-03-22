#include <cstdlib>
#include <iostream>


///* Filename:  btree.h
//
//Programmer:  Br. David Carlson
//
//Date:  November 2, 1997
//
//Last Modified:  December 21, 2001 to make Empty a const function.
//
//This is the header file to go with btree.cpp, an implementation of
//a B-tree-based table class.
//*/
//#include <cstdlib>
//#include <iostream>
//
//// The following line is commented off to omit debugging output.
////#define DEBUG
//// Remove the // at the beginning of that line and recompile if you want
//// to get extensive debugging output.
//
//
//const int MaxKeys = 11;   // max number of keys in a node
//
//const int MaxKeysPlusOne = MaxKeys + 1;
//
//const int MinKeys = 5;    // min number of keys in a node
//
//const long NilPtr = -1L;   // the L indicates a long int
//
//
//typedef struct
//{
//	int Count;               // Number of keys stored in the current node
//	int Key[MaxKeys];   // Warning: indexing starts at 0, not 1
//	long Branch[MaxKeysPlusOne];   // Fake pointers to child nodes
//} NodeType;
//
//
//void Error(char * msg);
//
//
//class BTTableClass
//{
//public:
//	BTTableClass(char Mode, char * FileName);
//	~BTTableClass(void);
//	bool Empty(void) const;
//	bool Insert(const int & Item);
//	bool Retrieve(int SearchKey, int & Item);
//	void Dump(void);   // for debugging only - could be removed
//	void Check(void);   // for debugging only
//private:
//	void CheckSubtree(long Current, int & Last); // for debugging
//	bool SearchNode(const int Target, int & location) const;
//	void AddItem(const int & NewItem, long NewRight,
//		NodeType & Node, int Location);
//	void Split(const int & CurrentItem, long CurrentRight,
//		long CurrentRoot, int Location, int & NewItem,
//		long & NewRight);
//	void PushDown(const int & CurrentItem, long CurrentRoot,
//		bool & MoveUp, int & NewItem, long & NewRight);
//	long Root;       // fake pointer to the root node
//	long NumNodes;   // number of nodes in the B-tree
//	int NodeSize;    // number of bytes per node
//	NodeType CurrentNode;   // storage for current node being worked on
//};
//
//
