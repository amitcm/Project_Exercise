/******************************************************************************
* btree-mem-C/btree.h
*
* COPYRIGHT (c) 1995, 1997 by David Van Wagner ALL RIGHTS RESERVED
* This source may be distributed under the terms of the GNU General Public
* License version 2, see the file COPYING for details.
*
* davevw@alumni.cse.ucsc.edu
* http://alumni.cse.ucsc.edu/~davevw/
*****************************************************************************/

#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <strstream>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

typedef signed char BTREE_POS;

template <class KEY>
class BTREE_ITERATOR;

template <class KEY>
class BTREE {
protected:
	BTREE_POS count;		/* number of keys which are valid */
	BTREE *parent;
	BTREE **ptr;
	KEY *key;

private:
	BTREE(const BTREE&) { assert(0); } // copy constructor disabled
	BTREE& operator=(const BTREE&) { assert(0); // assignment disabled
	return *this; }

public:
	BTREE(BTREE_POS order);	// constructor
	~BTREE();	// destructor
	BTREE* find(const KEY& key, BTREE_POS& pos);
	BTREE* add(const KEY& key, BTREE_POS& pos, BTREE_POS order) {
		return add_internal(NULL, NULL, key, pos, order, -1);
	}
	void empty();	// empty out a node leaving allocation of ptr & key
	void check(BTREE_POS order);
	void print();
	void display(int only_level);
	long get_count() const;
	int levels();
	void display2(int level);
	void remove(BTREE_POS pos, BTREE_POS order);
	void fix_root_add(BTREE*& tree) const {
		if (tree->parent != NULL)
			tree = tree->parent;
	}
	void fix_root_remove(BTREE*& tree) const;
	void traverse(int (*operation)(const KEY& key));
	BTREE* find_first(BTREE_POS& pos);
	BTREE* find_next(const BTREE_POS pos, BTREE_POS &next_pos);
protected:
	BTREE* add_internal(BTREE* left, BTREE* right,
		const KEY& key, BTREE_POS& pos, BTREE_POS order, BTREE_POS split_pos);
	BTREE* find_insert_position(const KEY& key);
	void remove_internal(BTREE_POS pos, BTREE_POS order);
	void underflow(BTREE_POS order);
	friend BTREE_ITERATOR<KEY>;
};

template <class KEY>
class BTREE_ROOT {
protected:
	/* MUST BE ODD, greater than 1, less than 32 */
	BTREE_POS order;
	BTREE<KEY> *root;

public:
	inline BTREE_ROOT(BTREE_POS o) {
		order = o;
		assertf(o>1 && o%2==1, "%d", o);
		root = new BTREE<KEY>(order);
	}
	inline BTREE_ROOT(BTREE_ROOT& source) {
		order = source.order;
		root = new BTREE<KEY>(order);
		add_tree(source);
	}
	inline BTREE_ROOT& operator=(BTREE_ROOT& source) {
		delete root;
		order = source.order;
		root = new BTREE<KEY>(order);
		add_tree(source);
		return *this;
	}
	inline ~BTREE_ROOT() { delete root; }
	inline BTREE<KEY>* find(const KEY& key, BTREE_POS& pos) {
		return root->find(key, pos); }
	BTREE<KEY>* add(const KEY& key, BTREE_POS& pos) {
		BTREE<KEY>* new_node = root->add(key, pos, order);
		root->fix_root_add(root);
		return new_node;
	}
	int add_tree(BTREE_ROOT& source);
	inline BTREE<KEY>* find_first(BTREE_POS& pos) const {
		return root->find_first(pos);
	}
	inline void empty() { root->empty(); }
	inline void check() { root->check(order); }
	inline void print() { root->print(); }
	inline void display(int only_level) { root->display(only_level); }
	inline long get_count() const { return root->get_count(); }
	inline int levels() { return root->levels(); }
	inline void display2(int level) { root->display2(level); }
	inline void remove(const KEY& key) {
		BTREE<KEY> *node;
		BTREE_POS pos;
		node = root->find(key, pos);
		if (pos >= 0 && node != NULL) {
			node->remove(pos, order);
			root->fix_root_remove(root);
		}
	}
	inline void traverse(int (*operation)(const KEY& key)) const {
		root->traverse(operation);
	}
	inline BTREE_POS get_order() const { return order; }

	friend BTREE_ITERATOR<KEY>;
};

/******************************************************************************
* BTREE() constructor                                                        *
*                                                                            *
* INPUTS:	none															  *
* OUTPUTS:	warning errors to stderr                                          *
*				with allocated and initialized ptr and key members			  *
*****************************************************************************/
template <class KEY>
BTREE<KEY>::BTREE(BTREE_POS order)
{
	int i;

	assertf(order>1 && order%2 == 1, "%d", order);
	count = 0;
	parent = NULL;
	typedef BTREE<KEY>* PTR_BTREE;
	ptr = new PTR_BTREE[order];
	//	ptr = new (BTREE<KEY> *)[order];
	for (i=0; i<order; ++i)
		ptr[i] = NULL;
	key = new KEY[order-1];
}

template <class KEY>
void BTREE<KEY>::fix_root_remove(BTREE<KEY>*& tree) const
{
	if (tree->count == 0 && tree->ptr[0] != NULL) {
		BTREE_POS i;
		tree = tree->ptr[0];
		delete tree->parent;
		tree->parent = NULL;
		for (i=0; i<=tree->count; ++i) {
			if (tree->ptr[i] != NULL)
				tree->ptr[i]->parent = tree;
		}
	}
}

/*****************************************************************************
* find()
*
* INPUTS: 	key value to search for (or find insertion point)
*			pointer to int for returning position
* OUTPUTS:	modifies contents of pos pointer to int to position of matched key
*			(-1 if not found, 0 based into key array)
* RETURNS:	BTREE node of leaf where key is found or should be inserted  
*****************************************************************************/
template <class KEY>
BTREE<KEY>* BTREE<KEY>::find(const KEY& key, BTREE_POS& pos)
{
	BTREE_POS i;
	BTREE<KEY> *prev=NULL;
	BTREE<KEY> *node=this;

	pos = -1;

	while (node != NULL) {
		prev = node;
		for (i=0; i < node->count; ++i) {
			if (key < node->key[i]) {
				node = node->ptr[i];
				break;
			} else if (key == node->key[i]) {
				pos = i;
				node = NULL;
				break;
			}
		}
		if (node == prev && i == node->count)
			node = node->ptr[i];
	}

	return prev;
}

/*****************************************************************************
* find_insert_position()
*
* INPUTS: 	key value to search for (or find insertion point)
*			pointer to int for returning position
* OUTPUTS:	modifies contents of pos pointer to int to position of matched key
*			(-1 if not found, 0 based into key array)
*
RETURNS:	BTREE node of leaf where key is found or should be inserted
*****************************************************************************/
template <class KEY>
BTREE<KEY>* BTREE<KEY>::find_insert_position(const KEY& key)
{
	BTREE_POS i;
	BTREE<KEY> *prev=NULL;
	BTREE<KEY> *node=this;

	while (node != NULL) {
		prev = node;
		for (i=0; i < node->count; ++i) {
			if (key <= node->key[i]) {
				node = node->ptr[i];
				break;
			}
		}
		if (node == prev && i == node->count)
			node = node->ptr[i];
	}

	return prev;
}

template <class KEY>
BTREE<KEY>* BTREE<KEY>::find_first(BTREE_POS& pos)
{
	BTREE<KEY>* ptr = this;
	while(ptr->ptr[0] != 0)
		ptr = ptr->ptr[0];
	pos = 0;
	return ptr;
}

/*****************************************************************************
* find_next()
*
* INPUTS: 	starting position
* OUTPUTS:	none
* RETURNS:	BTREE node where next key is found
*
* WARNING: because of actions of add_internal, BTREE may not be "well-formed"
*          in other words, some children may be NULL, some may not...
*****************************************************************************/
template <class KEY>
BTREE<KEY>* BTREE<KEY>::find_next(const BTREE_POS pos, BTREE_POS &next_pos)
{
	BTREE<KEY> *node;
	assert(pos >= 0);
	assert(pos < count);
	if (ptr[pos + 1] == NULL) {
		// THIS IS A LEAF, OR AT LEAST CAN'T DESCEND INTO RIGHT CHILD
		if (pos < count-1) {
			// NEXT IS NEXT ELEMENT IN LEAF
			next_pos = (BTREE_POS)(pos + 1);
			node = this;
		} else {
			if (parent == NULL) {
				next_pos = -1;
				return NULL;	// FAILED, WAS LAST KEY
			} else {
				// NEXT IS PARENT KEY WHOSE LEFT POINTER POINTS TO THIS
				node=parent;
				next_pos=0;
				while (next_pos < node->count && node->ptr[next_pos] != this)
					++next_pos;
				assert(node->ptr[next_pos] == this);
				while (next_pos == node->count)
				{
					// NO RIGHT POINTER, GO UP UNTIL FIND A RIGHT POINTER
					if (node->parent == 0)
					{
						next_pos = -1;
						return NULL;	// FAILED, WAS LAST KEY
					}
					next_pos=0;
					while (next_pos < node->parent->count
						&& node->parent->ptr[next_pos] != node)
						++next_pos;
					assert(node->parent->ptr[next_pos] == node);
					node = node->parent;
				}
			}
		}
	} else {
		// FROM INTERIOR, NEXT IS LEFTMOST GRAND*-CHILD OF RIGHT POINTER
		assert(ptr[pos+1] != NULL);
		node = ptr[pos+1];
		while (node->ptr[0] != NULL) {
			assert(key[pos] <= node->key[0]);
			node = node->ptr[0];
		}
		next_pos = 0;
	}
	assert(node != this || pos < next_pos);
	assert(next_pos < node->count);
	assert(key[pos] <= node->key[next_pos]);
	return node;
}

/*****************************************************************************
* underflow()
*
* INPUTS: 	nothing
* OUTPUTS:	resolves underflow caused by remove
* RETURNS:	nothing
*****************************************************************************/
template <class KEY>
void BTREE<KEY>::underflow(BTREE_POS order)
{
	assertf(count == 0, "%d", count);

	/* UNDERFLOW: CHECK IF CAN BORROW FROM BROTHERS */

	BTREE_POS i;

	if (parent == NULL) {
		// TREE SHOULD SHRINK IN SIZE (IF MORE THAN ONE LEVEL
		// BUT WILL ACTUALL HAPPEN IN BTREE_ROOT::remove
	} else {
		// SOLVE UNDERFLOW
		// FIND PTR IN PARENT

		for (i=0; i <= parent->count && parent->ptr[i] != this; ++i)
			; // KEEP LOOKING

		assert(i <= parent->count);
		assert(parent->ptr[i] == this);

		if (i>0 && parent->ptr[i-1]->count > 1) {
			/* BORROW FROM LEFT BROTHER */
			BTREE<KEY> *brother = parent->ptr[i-1];
			key[0] = parent->key[i-1];
			ptr[1] = ptr[0];
			ptr[0] = brother->ptr[brother->count];
			if (ptr[0] != NULL)
				ptr[0]->parent = this;
			count=1;
			parent->key[i-1] = brother->key[brother->count-1];
			--brother->count;
		} else if (i < parent->count && parent->ptr[i+1]->count > 1) {
			/* BORROW FROM RIGHT BROTHER */
			BTREE<KEY> *brother = parent->ptr[i+1];
			key[0] = parent->key[i];
			ptr[1] = brother->ptr[0];
			if (ptr[1] != NULL)
				ptr[1]->parent = this;
			count=1;
			parent->key[i] = brother->key[0];
			brother->ptr[0] = brother->ptr[1]; // REMOVE_INTERNAL WON'T DO THIS!
			brother->remove_internal(0, order);
		} else {
			// CAN'T BORROW FROM IMMEDIATE BROTHERS
			// COLLAPSE A BROTHER AND KEY FROM PARENT INSTEAD
			if (i>0) {
				/* COLLAPSE WITH LEFT BROTHER */
				BTREE<KEY> *brother = parent->ptr[i-1];
				assert(brother->count == 1);
				brother->key[1] = parent->key[i-1];
				brother->ptr[2] = ptr[0];
				if (brother->ptr[2] != NULL)
					brother->ptr[2]->parent = brother;
				assert((brother->ptr[0]==NULL && brother->ptr[1]==NULL && brother->ptr[2]==NULL)
					|| (brother->ptr[0]!=NULL && brother->ptr[1]!=NULL && brother->ptr[2]!=NULL));
				++brother->count;
				assert(brother->count == 2);
				parent->remove_internal(i-1, order);
				assert(count == 0);
				delete this;
			} else {
				/* COLLAPSE WITH RIGHT BROTHER */
				BTREE<KEY> *brother = parent->ptr[i+1];
				assert(brother->count == 1);
				key[0] = parent->key[i];
				key[1] = brother->key[0];
				ptr[1] = brother->ptr[0];
				if (ptr[1] != NULL)
					ptr[1]->parent = this;
				ptr[2] = brother->ptr[1];
				if (ptr[2] != NULL)
					ptr[2]->parent = this;
				assert((ptr[0]==NULL && ptr[1]==NULL && ptr[2]==NULL)
					|| (ptr[0]!=NULL && ptr[1]!=NULL && ptr[2]!=NULL));
				count=2;
				parent->remove_internal(i, order);
				brother->count = 0; // KEEP CHILDREN FROM BEING DELETED
				delete brother;
			}
		}
	}
}

/******************************************************************************
* add_internal()
*
* INPUTS: 	split left & right trees of node (for recursive use only,
*				should be NULL by normal callers)
*			key value to add
*			pointer to int for returning position where added
* OUTPUTS:	modifies contents of B-Tree, assertion errors to stderr
*          modifies contents of pos pointer to int to added position
*			(-1 for failure, 0 based into key array)
* RETURNS:	pointer to node where added
*
* NOTE:	currently never returns -1 as failed assert() will terminate program
*			and _not_ return
*****************************************************************************/
template <class KEY>
BTREE<KEY>* BTREE<KEY>::add_internal(BTREE<KEY> *left, BTREE<KEY> *right,
	const KEY& key, BTREE_POS& pos, BTREE_POS order, BTREE_POS split_pos)
{
	BTREE<KEY> *node = this;
	BTREE_POS i, j;

	/* verify parameters */
	assert((left==NULL && right==NULL) || (left!=NULL && right!=NULL));
	assertf(order>1 && order%2 == 1, "%d", order);

	pos = -1;

	if (split_pos < 0) {
		/* find key and position, or simply node where it should be inserted */
		node = node->find_insert_position(key);
		assert(node != NULL);
		for (i=0; i < node->count && node->key[i] <= key; ++i)
			; // find position
	} else
		i = split_pos;

	// MAY NOT BE A LEAF NODE:  because B-tree may temp. not be well formed
	//	assert (node->ptr[0] == NULL);	// must be a leaf node

	assert ((i < node->count && key <= node->key[i]) || (i == node->count));

	if (node->count < order-1) {
		/* fits, so insert it... */
		if (i < node->count) {
			// MUST SHIFT EXISTING KEYS OVER TO INSERT
			for (j=node->count-1; j>=i; --j) {
				/* move right pointer and key to right */
				node->ptr[j+2] = node->ptr[j+1];
				node->key[j+1] = node->key[j];
			}
			/* move last right pointer to right */
			node->ptr[j+2] = node->ptr[j+1];
		}

		node->key[i] = key;
		pos = i;
		++node->count;

		if (left == NULL) {
			assert(right == NULL);
		} else {
			assert(right != NULL);
			/* both left and right not NULL */
			node->ptr[pos] = left;
			left->parent = node;
			node->ptr[pos+1] = right;
			right->parent = node;
		}
	} else {
		assert(node->count == order-1);
		/* no room, split and insert into parent */
		/* note: node is full, don't need to look at count anymore... */
		BTREE<KEY> *new_node = new BTREE<KEY>(order);
		BTREE<KEY> *ptr = NULL;		// which node added in
		BTREE<KEY> *added;
		BTREE_POS temp_pos;

		assert (new_node != NULL);

		/* assume has same parent, if it splits will fix itself */
		new_node->parent = node->parent;

		/* doesn't fit, split into two nodes, right first */
		new_node->count = order/2;

		KEY median_key;

		if (i < order/2) {
			// insert in original node
			pos=i;
			ptr=node;

			// first fill in new node
			for (j=0; j<order/2; ++j) {
				new_node->key[j]=node->key[j+order/2];
				new_node->ptr[j]=node->ptr[j+order/2];
			}
			new_node->ptr[j]=node->ptr[j+order/2];

			median_key = node->key[order/2-1];

			// insert...
			for (j=order/2-1; j>i; --j) {
				node->key[j] = node->key[j-1];
				node->ptr[j+1] = node->ptr[j];
			}
			node->ptr[j+1] = node->ptr[j];
			node->key[i] = key;
			assert(ptr->key[pos] == key);
			node->count = order/2;
		} else if (i == order/2) {
			// key is median, so insert in parent instead
			median_key = key;

			// just fill in new node
			for (j=0; j<order/2; ++j) {
				new_node->key[j]=node->key[j+order/2];
				new_node->ptr[j]=node->ptr[j+order/2];
			}
			new_node->ptr[j]=node->ptr[j+order/2];
			node->count = order/2;
		} else {
			assert (i > order/2);
			// insert in new_node
			pos = i-order/2-1;
			ptr=new_node;
			for (j=0; j<pos; ++j) {
				new_node->key[j] = node->key[j+order/2+1];
				new_node->ptr[j] = node->ptr[j+order/2+1];
			}
			new_node->ptr[j] = node->ptr[j+order/2+1];
			new_node->key[j] = key;
			assert(ptr->key[pos] == key);
			median_key = node->key[order/2];
			for (j=pos+1; j<order/2; ++j) {
				new_node->key[j] = node->key[j+order/2];
				new_node->ptr[j] = node->ptr[j+order/2];
			}
			new_node->ptr[j] = node->ptr[j+order/2];
			node->count = order/2;
		}

		/* RESET CHILDREN OF NEW TO POINT TO NEW PARENT */
		for (j=0; j<=order/2; ++j) {
			if (new_node->ptr[j] != NULL)
				new_node->ptr[j]->parent = new_node;
		}

		/* wipe out pointers moved to the new_node node */
		for (j=order/2+1; j<order; ++j)
			node->ptr[j] = NULL;

		/* add to parent, create parent if necessary */
		if (node->parent == NULL) {
			node->parent = new BTREE<KEY>(order);
			split_pos = -1;
		} else {
			/* NULL terminate the parent's pointer to this node */
			for (i=0; i <= node->parent->count; ++i) {
				if (node->parent->ptr[i] == node) {
					node->parent->ptr[i] = NULL;
					break;
				}
			}
			assertf(i <= node->parent->count, "%d\n", i);
			split_pos = i;
		}

		assert(node->parent != NULL);

		/* insert the median and the split nodes into the parent node */
		if (ptr == NULL) {
			added = node->parent->add_internal(node, new_node, median_key,
				temp_pos, order, split_pos);
			pos = temp_pos;
		} else
			added = node->parent->add_internal(node, new_node, median_key,
			temp_pos, order, split_pos);

		assert(added->key[temp_pos] == median_key);

		if (left != NULL) {
			if (ptr == NULL) {
				node->ptr[order/2] = left;
				assert(left->parent == node);
				new_node->ptr[0] = right;
				right->parent = new_node;
				node = added;
			} else {
				/* both left and right not NULL */
				assert(right != NULL);
				ptr->ptr[pos] = left;
				ptr->ptr[pos+1] = right;
				left->parent = ptr;
				right->parent = ptr;
				node = ptr;
			}
		}
	}

	return node;
}

/*****************************************************************************
* remove_internal()	-	forcibly remove key from specified internal node
*
* INPUTS: 	position of key to remove
* OUTPUTS:	modifies contents of B-Tree to remove key
* RETURNS:	nothing
*
* NOTE: does not modify ptr[pos]
*****************************************************************************/
template <class KEY>
void BTREE<KEY>::remove_internal(BTREE_POS pos, BTREE_POS order)
{
	BTREE_POS i;

	for (i=pos+1; i<count; ++i) {
		key[i-1] = key[i];
		ptr[i] = ptr[i+1];
	}
	if (--count == 0)
		underflow(order);
}

/*****************************************************************************
* remove()	-	remove specified node
*
* INPUTS: 	position of key to remove
* OUTPUTS:	modifies contents of B-Tree to remove key
* RETURNS:	nothing
*****************************************************************************/
template <class KEY>
void BTREE<KEY>::remove(BTREE_POS pos, BTREE_POS order)
{
	BTREE_POS i;

	assertf(order>1 && order%2 == 1, "%d", order);
	assertf(pos >= 0 && pos < order, "%d\n", pos);
	assertf(count > 0 && count < order, "%d\n", count);
	assertf2(pos == 0 || count != 1, "pos=%d, count=%d\n",
		pos, count);

	if (ptr[0] == NULL) {
		// LEAF
		for (i=pos+1; i<count; ++i)
			key[i-1] = key[i];
		if (--count == 0) {
			ptr[0] = NULL;
			underflow(order);
		}
	} else {
		/* INTERIOR: REPLACE BY ITS SUCCESSOR AND DELETE THE SUCCESSOR */
		BTREE_POS succ_pos;
		BTREE<KEY> *succ = find_next(pos, succ_pos);
		assert(succ != NULL);
		assert(succ->count > 0);
		assert(succ->ptr[0] == NULL);
		assert(succ_pos == 0);
		assert(key[pos] <= succ->key[0]);
		key[pos] = succ->key[0];
		succ->remove(0, order);
	}
}

/*****************************************************************************
* print() - output contents of B-Tree to stdout on one line
*****************************************************************************/
template <class KEY>
void BTREE<KEY>::print()
{
	BTREE_POS i;

	if (count == 0) {
		cout << "EMPTY" << endl;
		return;
	}

	for (i=0; i < count; ++i) {
		if (ptr[i] != NULL) {
			cout << flush;
			assert(ptr[i]->parent == this);
			ptr[i]->print();
		}
		cout << key[i] << ' ';
	}
	if (ptr[i] != NULL) {
		cout << flush;
		assert(ptr[i]->parent == this);
		ptr[i]->print();
	}
}

/*****************************************************************************
* levels()	-	count levels of the B-Tree
*****************************************************************************/
template <class KEY>
int BTREE<KEY>::levels()
{
	BTREE_POS i;
	int levels;
	int max=1;

	for (i=0; i <= count; ++i) {
		levels = 1;
		if (ptr[i] != NULL)
			levels += ptr[i]->levels();
		if (levels > max)
			max = levels;
	}
	return max;
}

/*****************************************************************************
* get_count()	-	count members of the B-Tree
*****************************************************************************/
template <class KEY>
long BTREE<KEY>::get_count() const
{
	BTREE_POS i;
	long c=0;

	for (i=0; i <= count; ++i) {
		if (i<count)
			++c;
		if (ptr[i] != NULL)
			c += ptr[i]->get_count();
	}

	return c;
}

/*****************************************************************************
* display() - output contents of B-Tree to stdout showing hierarchy
*						horizontally.  Recommended only for very small B-Trees
*****************************************************************************/
template <class KEY>
void BTREE<KEY>::display(int only_level)
{
	BTREE_POS i;
	int level=1;
	char buffer[80];
	ostrstream s(buffer, sizeof(buffer));

	if (count == 0) {
		cout << "EMPTY" << endl;
		return;
	}

	for (i=0; i < count; ++i) {
		if (ptr[i] != NULL) {
			assert(ptr[i]->parent == this);
			ptr[i]->display(only_level-1);
		}
		s << key[i] << ' ';
		if (level != only_level)
			memset(buffer, ' ', strlen(buffer));
		cout << buffer;
	}
	if (ptr[i] != NULL) {
		cout << flush;
		assert(ptr[i]->parent == this);
		ptr[i]->display(only_level-1);
	}
}

/*****************************************************************************
* display2() - output contents of B-Tree to stdout showing hierarchy
*						vertically, easier to read display for large B-Trees
*****************************************************************************/
template <class KEY>
void BTREE<KEY>::display2(int level)
{
	BTREE_POS i, j;

	if (count == 0) {
		cout << "EMPTY" << endl;
		return;
	}

	for (i=0; i < count; ++i) {
		if (ptr[i] != NULL) {
			cout << flush;
			assert(ptr[i]->parent == this);
			ptr[i]->display2(level+1);
		}
		for (j=0; j<level*6; ++j)
			cout << ' ';
		cout.width(5);
		cout << key[i] << endl;
	}
	if (ptr[i] != NULL) {
		cout << flush;
		assert(ptr[i]->parent == this);
		ptr[i]->display2(level+1);
	}
}

/*****************************************************************************
* ~BTREE()	-	free all memory allocated for the B-Tree - destructor
*****************************************************************************/
template <class KEY>
BTREE<KEY>::~BTREE()
{
	BTREE_POS i;

	if (count > 0) {
		for (i=0; i <= count; ++i)
			delete ptr[i];
	}

	delete [] ptr;
	delete [] key;
}

/*****************************************************************************
* check()	-	check consistency of B-Tree while traversing it
*						halts program if error found
*****************************************************************************/
template <class KEY>
void BTREE<KEY>::check(BTREE_POS order)
{
	BTREE_POS i, c;

	if (count == 0)
		return;

	assertf(order>1 && order%2 == 1, "%d", order);
	assert(count > 0 && count < order);

	for (i=c=0; i <= count; ++i) {
		if (i < count)
			++c;
		if (ptr[i] != NULL) {
			assert(ptr[i]->parent == this);
			ptr[i]->check(order);
		}
	}

	assertf2(count == c, "count=%d, c=%d\n", count, c);
}

/*****************************************************************************
* empty()	-	empty out a B-Tree node leaving allocation of key and ptr
*****************************************************************************/
template <class KEY>
void BTREE<KEY>::empty() {
	BTREE_POS i;

	for (i=0; i<=count; ++i) {
		if (ptr[i] != NULL) {
			delete ptr[i];
			ptr[i] = NULL;
		}
		if (i<count)
			key[i] = KEY();
	}

	count=0;
}

template <class KEY>
void BTREE<KEY>::traverse(int (*operation)(const KEY& key))
{
	BTREE_POS i;
	static int bExit;

	bExit = 0;

	if (count == 0) {
		return;
	}

	for (i=0; !bExit && i < count; ++i) {
		if (ptr[i] != NULL) {
			assert(ptr[i]->parent == this);
			ptr[i]->traverse(operation);
		}
		if (!operation(key[i]))
		{
			bExit = 1;
		}
	}
	if (!bExit && ptr[i] != NULL) {
		assert(ptr[i]->parent == this);
		ptr[i]->traverse(operation);
	}
}

template <class KEY>
class BTREE_ITERATOR
{
private:
	/*const*/ BTREE<KEY> /*const*/ *ptr;
	BTREE_POS pos;

public:
	BTREE_ITERATOR(const BTREE_ROOT<KEY>& root)
	{
		ptr = root.find_first(pos);
	}

	// prefix
	BTREE_ITERATOR operator ++()
	{
		if (*this)
			ptr = ptr->find_next(pos, pos);
		return *this;
	}

	// postfix
	BTREE_ITERATOR operator ++(int)
	{
		BTREE_ITERATOR ret = *this;
		++(*this);
		return ret;
	}

	// dereference
	const KEY operator *() const
	{
		return ptr->key[pos];
	}

	operator int() const
	{
		return (ptr != 0 && pos >= 0);
	}
};

template <class KEY>
int BTREE_ROOT<KEY>::add_tree(BTREE_ROOT<KEY>& source)
{
	BTREE_POS pos;
	int total = 0;
	for (BTREE_ITERATOR<KEY> p(source); p != 0; ++p)
	{
		if (add(*p, pos) != 0 && pos >= 0)
			++total;
	}
	return total;
}

#endif // BTREE_H

