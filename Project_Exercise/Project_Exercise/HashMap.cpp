#include "stdafx.h"
#include "HashMap.h"

// Class HashMap
HashMap::HashMap() 
{
	// An array of pointers to HashEntries.
	table = new HashEntry*[TABLE_SIZE];
	for (int i = 0; i < TABLE_SIZE; i++)
		table[i] = NULL;
}

HashMap::~HashMap() 
{
	for (int i = 0; i < TABLE_SIZE; i++)
		if (table[i] != NULL)
			delete table[i];
	delete[] table;
}

int HashMap::get(int key) 
{
	// Use some nice hash function instead of mod
	int hash = (key % TABLE_SIZE);
	// Linear probing. Note that the first empty table-entry stops the probing => The key isn't in the table.
	while (table[hash] != NULL && table[hash]->getKey() != key)
		hash = (hash + 1) % TABLE_SIZE;				// Linear probing. with wrap around
	if (table[hash] == NULL)
		return -1;
	else
		return table[hash]->getValue();
}

void HashMap::put(int key, int value) 
{
	// Use same nice hash function instead of mod
	int hash = (key % TABLE_SIZE);
	while (table[hash] != NULL && table[hash]->getKey() != key)
		hash = (hash + 1) % TABLE_SIZE;
	if (table[hash] != NULL)
		delete table[hash];
	table[hash] = new HashEntry(key, value);
}     

/*
	Hashing variable-length data

		When the data values are long (or variable-length) character strings—such as personal names, web page addresses, 
	or mail messages—their distribution is usually very uneven, with complicated dependencies. 
	For example, text in any natural language has highly non-uniform distributions of characters, and character pairs, 
	very characteristic of the language. For such data, it is prudent to use a hash function that depends on 
	all characters of the string—and depends on each character in a different way.

		In cryptographic hash functions, a Merkle–Damgård construction is usually used. In general, the scheme for 
	hashing such data is to break the input into a sequence of small units (bits, bytes, words, etc.) and 
	combine all the units b[1], b[2], ..., b[m] sequentially, as follows

			S ← S0;                             // Initialize the state.
			for k in 1, 2, ..., m do             // Scan the input data units:
			  S ← F(S, b[k]);                   //   Combine data unit k into the state.
			return G(S, n)                      // Extract the hash value from the state.

	This schema is also used in many text checksum and fingerprint algorithms. The state variable S may be 
	a 32- or 64-bit unsigned integer; in that case, S0 can be 0, and G(S,n) can be just S mod n. 
	The best choice of F is a complex issue and depends on the nature of the data. If the units b[k] are single bits, 
	then F(S,b) could be, for instance

			 if highbit(S) = 0 then
			   return 2 * S + b
			 else
			   return (2 * S + b) ^ P

	Here highbit(S) denotes the most significant bit of S; the '*' operator denotes unsigned integer 
	multiplication with lost overflow; '^' is the bitwise exclusive or operation applied to words; and P is a suitable fixed word.

*/

static int HashCode(int key) {
	// Use something elegant than this.
	return key % TABLE_SIZE;
}

