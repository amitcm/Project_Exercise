//
// STREE2006.CPP - Suffix tree creation
//
// Mark Nelson, updated December, 2006
//
// This code has been tested with Borland C++ and
// Microsoft Visual C++.
//
// This program asks you for a line of input, then
// creates the suffix tree corresponding to the given
// text. Additional code is provided to validate the
// resulting tree after creation.
//

#include "stdafx.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string.h>
#include <cassert>
#include <string>

using std::cout;
using std::cin;
using std::cerr;
using std::setw;
using std::flush;
using std::endl;

//
// When a new tree is added to the table, we step
// through all the currently defined suffixes from
// the active point to the end point.  This structure
// defines a Suffix by its final character.
// In the canonical representation, we define that last
// character by starting at a node in the tree, and
// following a string of characters, represented by
// first_char_index and last_char_index.  The two indices
// point into the input string.  Note that if a suffix
// ends at a node, there are no additional characters
// needed to characterize its last character position.
// When this is the case, we say the node is Explicit,
// and set first_char_index > last_char_index to flag
// that.
//

class Suffix {
public :
	int origin_node;
	int first_char_index;
	int last_char_index;
	Suffix( int node, int start, int stop )
		: origin_node( node ),
		first_char_index( start ),
		last_char_index( stop ){};
	int Explicit(){ return first_char_index > last_char_index; }
	int Implicit(){ return last_char_index >= first_char_index; }
	void Canonize();
};

//
// The suffix tree is made up of edges connecting nodes.
// Each edge represents a string of characters starting
// at first_char_index and ending at last_char_index.
// Edges can be inserted and removed from a hash table,
// based on the Hash() function defined here.  The hash
// table indicates an unused slot by setting the
// start_node value to -1.
//

class Edge {
public :
	int first_char_index;
	int last_char_index;
	int end_node;
	int start_node;
	void Insert();
	void Remove();
	Edge();
	Edge( int init_first_char_index,
		int init_last_char_index,
		int parent_node );
	int SplitEdge( Suffix &s );
	static Edge Find( int node, int c );
	static int Hash( int node, int c );
};

//
//  The only information contained in a node is the
//  suffix link. Each suffix in the tree that ends
//  at a particular node can find the next smaller suffix
//  by following the suffix_node link to a new node.  Nodes
//  are stored in a simple array.
//
class Node {
public :
	int suffix_node;
	Node() { suffix_node = -1; }
	static int Count;
};

//
// The maximum input string length this program
// will handle is defined here.  A suffix tree
// can have as many as 2N edges/nodes.  The edges
// are stored in a hash table, whose size is also
// defined here.
//
const int MAX_LENGTH = 1000;
const int HASH_TABLE_SIZE = 2179;  //A prime roughly 10% larger

//
// This is the hash table where all the currently
// defined edges are stored.  You can dump out
// all the currently defined edges by iterating
// through the table and finding edges whose start_node
// is not -1.
//

Edge Edges[ HASH_TABLE_SIZE ];

//
// The array of defined nodes.  The count is 1 at the
// start because the initial tree has the root node
// defined, with no children.
//

int Node::Count = 1;
Node Nodes[ MAX_LENGTH * 2 ];

//
// The input buffer and character count.  Please note that N
// is the length of the input string -1, which means it
// denotes the maximum index in the input buffer.
//

char T[ MAX_LENGTH ];
int N;

//
// Necessary forward references
//
void validate();
int walk_tree( int start_node, int last_char_so_far );

//
// This routine prints out the contents of the suffix tree
// at the end of the program by walking through the
// hash table and printing out all used edges.  It
// would be really great if I had some code that will
// print out the tree in a graphical fashion, but I don't!
//

void dump_edges( int current_n );


//
// This routine constitutes the heart of the algorithm.
// It is called repetitively, once for each of the prefixes
// of the input string.  The prefix in question is denoted
// by the index of its last character.
//
// At each prefix, we start at the active point, and add
// a new edge denoting the new last character, until we
// reach a point where the new edge is not needed due to
// the presence of an existing edge starting with the new
// last character.  This point is the end point.
//
// Luckily for use, the end point just happens to be the
// active point for the next pass through the tree.  All
// we have to do is update it's last_char_index to indicate
// that it has grown by a single character, and then this
// routine can do all its work one more time.
//

void AddPrefix( Suffix &active, int last_char_index );


//
// The validation code consists of two routines.  All it does
// is traverse the entire tree.  walk_tree() calls itself
// recursively, building suffix strings up as it goes.  When
// walk_tree() reaches a leaf node, it checks to see if the
// suffix derived from the tree matches the suffix starting
// at the same point in the input text.  If so, it tags that
// suffix as correct in the GoodSuffixes[] array.  When the tree
// has been traversed, every entry in the GoodSuffixes array should
// have a value of 1.
//
// In addition, the BranchCount[] array is updated while the tree is
// walked as well.  Every count in the array has the
// number of child edges emanating from that node.  If the node
// is a leaf node, the value is set to -1.  When the routine
// finishes, every node should be a branch or a leaf.  The number
// of leaf nodes should match the number of suffixes (the length)
// of the input string.  The total number of branches from all
// nodes should match the node count.
//

char CurrentString[ MAX_LENGTH ];
char GoodSuffixes[ MAX_LENGTH ];
char BranchCount[ MAX_LENGTH * 2 ] = { 0 };

void validate();
int walk_tree( int start_node, int last_char_so_far );

