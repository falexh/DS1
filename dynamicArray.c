/*	dynamicArray.c: Dynamic Array implementation. */
#include <assert.h>
#include <stdlib.h>
#include "dynArray.h"

struct DynArr
{
	TYPE *data;		/* pointer to the data array */
	int size;		/* Number of elements in the array */
	int capacity;	/* capacity ofthe array */
};


/* ************************************************************************
	Dynamic Array Functions
************************************************************************ */

// Initialize (including allocation of data array) dynamic array.

void initDynArr(DynArr *v, int capacity)
{
	assert(capacity > 0);
	assert(v!= 0);
	v->data = (TYPE *) malloc(sizeof(TYPE) * capacity);
	assert(v->data != 0);
	v->size = 0;
	v->capacity = capacity;
}

// Allocate and initialize dynamic array.

DynArr* newDynArr(int cap)
{
	assert(cap > 0);
	DynArr *r = (DynArr *)malloc(sizeof( DynArr));
	assert(r != 0);
	initDynArr(r,cap);
	return r;
}

// Deallocate data array in dynamic array.

void freeDynArr(DynArr *v)
{
	if(v->data != 0)
	{
		free(v->data); 	/* free the space on the heap */
		v->data = 0;   	/* make it point to null */
	}
	v->size = 0;
	v->capacity = 0;
}

// Deallocate data array and the dynamic array ure.

void deleteDynArr(DynArr *v)
{
	freeDynArr(v);
	free(v);
}

// Resizes the underlying array to be the size cap

void _dynArrSetCapacity(DynArr *v, int newCap)
{
    assert(v != 0);
    TYPE *tempArr = malloc(sizeof(TYPE)* newCap);
    assert(tempArr != 0);

    for (int i = 0; i < v->size; i++){
        tempArr[i] = v->data[i];
    }

    free(v->data);

    v->data = tempArr;
    tempArr = 0;

    v->capacity = newCap;
}

// Get the size of the dynamic array

int sizeDynArr(DynArr *v)
{
	return v->size;
}

// 	Adds an element to the end of the dynamic array

void addDynArr(DynArr *v, TYPE val)
{
    if(v->size >= v->capacity){
        _dynArrSetCapacity(v, 2* v->capacity);
    }

    v->data[v->size] = val;
    v->size++;
}

//	Get an element from the dynamic array from a specified position

TYPE getDynArr(DynArr *v, int pos)
{
    assert(v != 0 && v->size != 0);
    assert(pos >= 0 && pos < v->size);

    return v->data[pos];
}

//	Put an item into the dynamic array at the specified location,

void putDynArr(DynArr *v, int pos, TYPE val)
{
    assert(v != 0 && v->size != 0);
    assert(pos >= 0 && pos < v->size);
    v->data[pos] = val;
}

//	Swap two specified elements in the dynamic array

void swapDynArr(DynArr *v, int i, int  j)
{

    assert(v != 0 && v->size != 0);
    assert(i >= 0 && i < v->size);
    assert(j >= 0 && j < v->size);

    TYPE tempArr = getDynArr(v, i);
    putDynArr(v, i, getDynArr(v, j));
    putDynArr(v, j, tempArr);
}

/*	Remove the element at the specified location from the array,
	shifts other elements back one to fill the gap*/

void removeAtDynArr(DynArr *v, int idx)
{
    assert(v != 0 && v->size != 0);
    assert(idx >= 0 && idx < v->size);

    for(int i = idx; i <= v->size-2; i++){
        v->data[i] = v->data[i+1];
    }
    v->size--;
}


/* ************************************************************************
	Stack Interface Functions
************************************************************************ */

/*	Returns boolean (encoded in an int) demonstrating whether or not the
	dynamic array stack has an item on it. */

int isEmptyDynArr(DynArr *v)
{
    assert(v != 0);
    if(sizeDynArr(v) == 0){
        return 1;
    }else{
        return 0;
    }
}

//	Push an element onto the top of the stack

void pushDynArr(DynArr *v, TYPE val)
{
    assert(v != 0);
    addDynArr(v, val);
}

//	Returns the element at the top of the stack

TYPE topDynArr(DynArr *v)
{
    assert(v != 0);
    assert(sizeDynArr(v) > 0);

    return getDynArr(v, sizeDynArr(v) - 1);
}

// Removes the element on top of the stack

void popDynArr(DynArr *v)
{
    assert(v != 0);
    assert(sizeDynArr(v) >= 1);
    removeAtDynArr(v, sizeDynArr(v) - 1);
}

/* ************************************************************************
	Bag Interface Functions
************************************************************************ */

/*	Returns boolean (encoded as an int) demonstrating whether or not
	the specified value is in the collection */

int containsDynArr(DynArr *v, TYPE val)
{
    assert(v != 0);
    assert(sizeDynArr(v) > 0);

    for (int i = 0; i < sizeDynArr(v); i++){
        if(EQ(v->data[i],val)){
            return 1;
        }
    }

    return 0;
}

/*	Removes the first occurrence of the specified value from the collection
	if it occurs
*/
void removeDynArr(DynArr *v, TYPE val)
{
    int i;
    assert(!isEmptyDynArr(v));
    for (i = 0; i < v->size; i++){
        if(EQ(v->data[i],val)){
            removeAtDynArr(v, i);
            return;
        }
    }
}
