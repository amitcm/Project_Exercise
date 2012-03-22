#ifndef _VECTOR_H
#define _VECTOR_H

#include <stdlib.h>
#include <assert.h>
//#include <iostream.h>
#include <stdio.h>

// templated vector class, partially based on Budd,
//                         Classic Data Structures in C++
// written 11/5/93, modified 3/23/94
// changed on 3/9/95 to make all methods inline (defined in class decl)
//
// for a vector of Items use AVector<Item>, e.g., AVector <int> intvector;
//                           
//                           note: Item must have a default constructor
//
// constructors:
//   AVector()                   -- default, vector of size 0 (no entries)
//   AVector(int size)           -- vector with size entries
//   AVector(int size,
//          Item fillValue)     -- vector w/ size entries all == fillValue
//   AVector(const AVector & vec) -- copy constructor
//    
//   int Length()                -- returns size of vector (capacity)
//   void SetSize(int newSize)   -- resizes the vector to newSize elements
//                                  (can result in losing elements if
//                                   new size < old size)
//   void resize(int newSize)     -- synonym for SetSize
//
//   void Fill(Item fillValue)    -- set all entries == fillValue
//
//   operator =                   -- assignment operator works properly
//   operator []                  -- indexes both const and non-const vectors
//    
//
//  examples of use:
//             AVector<double> dlist(100);       // a list of 100 doubles
//             AVector<double> dzlist(100,0.0);  // initialized to 0.0
//
//             AVector<String> slist(300);       // 300 strings
//
//             AVector<int> ilist;               // has room for 0 ints

template <class Item> class AVector
{
  public:
    AVector()                               // default constructor 0 elts
    // postcondition: vector of zero items constructed
    {
        myLength = 0; myList = 0;
    }
    
    AVector(int size)                       // specify size of vector
    // postcondition: vector of size items constructed   
    {
        myLength = size;
        myList = new Item [size];
        assert(myList != 0);
    }
    
    AVector(int size, Item fillValue)      // specify size and fill value
    // postcondition: vector of size items, each initialized to fillValue
    //                constructed    
    {
        myLength = size;
        myList = new Item [size];
        assert(myList != 0);
        for(int k = 0; k < size; k++){
            myList[k] = fillValue;
        }       
    }

    AVector(const AVector<Item> & vec)             // copy constructor
    // precondition: Item supports assignment
    // postcondition: return copy of vec        
    {
        // allocate storage
        
        myList = new Item [myLength = vec.myLength];
        assert(myList != 0);
        
        // copy elements
        for(int k = 0; k < vec.myLength; k++)
        {
            myList[k] = vec.myList[k];
        }       
    }
    
    ~AVector ()                            // free new'd storage
     // postcondition: dynamically allocated storage freed
     {
         delete [] myList;
         myList = 0;
         myLength = 0;               // leave in "empty" state
     }
    AVector & operator = (const AVector<Item> & vec) // overload assignment
    // precondition: Item supports assignment     
    // postcondition: self is assigned vec
    {
        if (this != &vec)      // don't assign to self!
        {       
            delete [] myList;            // out with old list, in with new
            myList = new Item [myLength = vec.myLength]; 
            assert(myList != 0);
            
            // copy vec
            myLength = vec.myLength;
            for(int k=0; k < myLength; k++)
            {
                myList[k] = vec.myList[k];
            }
        }
        return *this;           
    }
    
    int Length() const                    // capacity of vector
    {
        return myLength;
    }
    int length() const
    {
        return Length();
    }

    void Fill(Item fillValue)
    // postcondition: all entries == fillvalue
    {
        int k;
        for(k=0; k < myLength; k++)
        {
            myList[k] = fillValue;
        }
    }

    void SetSize(int newSize)             // change size dynamically
    // precondition: vector has room for myLength entries     
    // postcondition: vector has room for newSize entries
    //                the first myLength of which are copies of original
    //                unless newSize < myLength, then truncated copy occurs       
    {
        int numToCopy = newSize < myLength ? newSize : myLength;
    
        // allocate new storage
        Item * newList = new Item[newSize];
        assert(newList != 0);   // be sure storage allocated
        
        int k;
        for(k=0; k < numToCopy;k++)
        {
            newList[k] = myList[k];
        }
        
        delete [] myList;         // de-allocate old storage
        myLength = newSize;
        myList = newList;
    }

    void resize(int newSize)
    {
        SetSize(newSize);
    }
    
    Item & operator [] (int index)      
    // safe indexing, returning reference
    // precondition: 0 <= index < myLength
    // postcondition: return index-th item
    // exception: aborts if index is out-of-bounds
    {
        if ((unsigned) index >= (unsigned)myLength || index < 0)
        {
            cerr << "Illegal vector index: " << index
                 << " (max = " << myLength-1 << ")" << endl;
            assert(index >= 0);
            assert(index < myLength);
        }
    
        return myList[index];     
    }
    
    const Item & operator [] (int index) const // const index 
    // safe indexing, returning const reference to avoid modification
    // precondition: 0 <= index < myLength
    // postcondition: return index-th item
    // exception: aborts if index is out-of-bounds
    {
    
        if ((unsigned) index >= (unsigned)myLength || index < 0)
        {
            cerr << "Illegal vector index: " << index
                 << " (max = " << myLength << ")" << endl;
            assert(index >= 0);
            assert(index < myLength);
        }
    
        return myList[index]; 
    }


  private:
    Item * myList;   // the array of items
    int myLength;   // # things in vector (array), 0,1,...,(myLength-1)
};

#endif                          // _VECTOR_H not defined
