#include "stdafx.h"

const int TABLE_SIZE = 128;

class HashEntry {
private:
	int key;
	int value;
public:
	/* Here is something that always works: the {body} of a constructor (or a function called from the constructor) can 
	reliably access the data members declared in a base class and/or the data members declared in the constructor's own class. 
	This is because all those data members are guaranteed to have been fully constructed 
	by the time the constructor's {body} starts executing.
	*/
	HashEntry(int key_, int value_)
		: key(key_),
		value(value_)
	{
	}

	int getKey() 
	{
		return key;
	}

	int getValue() 
	{
		return value;
	}
};

// Array of pointers of HashEntry object. An array of pointers to HashEntries.
class HashMap {
private:
	HashEntry **table;
public:
	HashMap();
	~HashMap(); 
	int get(int key);
	void put(int key, int value);
};

