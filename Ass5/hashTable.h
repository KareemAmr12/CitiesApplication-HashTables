#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
using namespace std;


template <class keyType, class dataType>

class hashTable
{
  public:
	    
    // Member Functions
	// Constructor with two arguments, 
      	// Table size is nelements, k is "empty" value of keyType
	hashTable(int nelements, const keyType &k);		
	~hashTable();						// Destructor
	
	// Functions Prototype Definitions
	
	bool tableIsEmpty() const;		// return True if table is empty
	bool tableIsFull() const;		// return True if table is full
	int  occupancy() const;			// return no. of occupied slots
	// insert key and data at a hashed slot, return true if successful
	bool insert(const keyType &, const dataType & );	
	
	// Search the table for the slot that matches key. 
// 	// If found, return True, set current position to slot
	bool search(const keyType & );		// Search given key 

    void updateData(const dataType & );	// Update data part of current slot 
	void retrieveData(dataType &) const;	// retrieve data part of current slot
	void traverse() const;	// Traverse whole table
	void advance();
	int currentSlot();
	keyType retrieveKey();
	
  private:
	
	// Slot Class
	   class slot
	   {
		public:
			keyType key; 		// key 
			dataType data;		// Data
		}; // end of class slot declaration

	slot *T;					// Pointer to Storage Array
	int h;						// Index to a slot
	int MaxSize, csize;	// Maximum and Current Sizes
	
	keyType Empty;					// Key value to consider as "Empty" 

	// Private Member function
	int hash(const keyType & ) const;	// Hashing function
	void reallocate(int extraSize);
}; // End of class hashTable definition
 // HASH_TABLE_H




// Constructor with two arguments, 
// Table size is nelements, k is "empty" value of keyType
template <class keyType, class dataType>
hashTable<keyType, dataType>::hashTable(int nelements, const keyType& k)
{
	MaxSize = nelements; T = new slot[MaxSize];
	Empty = k;
	for (int i = 0; i < MaxSize; i++) T[i].key = Empty;
	h = -1;  csize = 0;
}

// Destructor
template <class keyType, class dataType>
hashTable<keyType, dataType>::~hashTable()
{
	delete[] T;
}

// return True if table is empty
template <class keyType, class dataType>
bool hashTable<keyType, dataType>::tableIsEmpty() const
{
	return (csize == 0);
}

// return True if table is full
template <class keyType, class dataType>
bool hashTable<keyType, dataType>::tableIsFull() const
{
	return (csize == MaxSize);
}

// return no. of occupied slots
template <class keyType, class dataType>
int hashTable<keyType, dataType>::occupancy() const
{
	return csize; 
}


// insert key and data at a hashed slot, return true if successful
template <class keyType, class dataType>
bool hashTable<keyType, dataType>::insert(const keyType& k, const dataType& d)
{
	if (tableIsFull()) //here we add more free slots into the table to be able to take new city if the table was full
	{
		reallocate(50);
	}
	
		h = hash(k);
		while (T[h].key != Empty)
			h = (h + 1) % MaxSize;
		T[h].key = k;  T[h].data = d; csize++;
		return true;
	
	
}
template <class keyType, class dataType>
void hashTable<keyType, dataType>::advance()
{
	h = (h + 1) % MaxSize;
	
}
template <class keyType, class dataType>
int hashTable<keyType, dataType>::currentSlot()
{
	return h;
}

template <class keyType, class dataType>
keyType hashTable<keyType, dataType>::retrieveKey()
{
	return T[h].key;
}


// Search the table for the slot that matches key. 
// If found, return True, set current position to slot
template <class keyType, class dataType>
bool hashTable<keyType, dataType>::search(const keyType& k)
{

	if (!tableIsEmpty())
	{
		h = hash(k); int start = h;
		for (; ; )
		{
			if (T[h].key == Empty) return false;
			if (k == T[h].key) return true;
			h = (h + 1) % MaxSize;
			if (h == start) return false;
		}
	}
	else return false;
}


// Update the data part of the current slot
template <class keyType, class dataType>
void hashTable<keyType, dataType>::updateData(const dataType& d)
{
	if ((h >= 0) && (h < MaxSize)) T[h].data = d;
}

// Retrieve the data part of the current slot
template <class keyType, class dataType>
void hashTable<keyType, dataType>::retrieveData(dataType& d) const
{
	if ((h >= 0) && (h < MaxSize)) d = T[h].data;
	else d = T[0].data;
}



// Traverse whole table
template <class keyType, class dataType>
void hashTable<keyType, dataType>::traverse() const
{
	
	for (int i = 0; i < MaxSize; i++)
	{
		
		if (T[i].key != Empty)
		{
			cout << T[i].key << endl;
		}
	}

}

// Private Hashing Function
template <class keyType, class dataType>
int hashTable<keyType, dataType>::hash(const keyType& k) const
{
	return (k.length() % MaxSize);
}


//here we make a funcation to add more free slots into the table if the maximum is reached and the user wants to input a new city
template <class keyType, class dataType>
void hashTable<keyType, dataType>::reallocate(int extraSize)
{
	int newsize = MaxSize + extraSize;
	slot* temp = new slot[newsize];
	
	for (int i = 0; i < MaxSize; i++)
	{
		temp[i] = T[i];
	}

	delete[] T;
	T = temp;
	temp = NULL;
	for (int i = MaxSize; i < newsize; i++)
	{
		T[i].key = Empty;
	}
	MaxSize = newsize;
}
#endif