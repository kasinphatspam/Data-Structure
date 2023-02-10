#include "arraylist.h"
#include <stdlib.h>

/* Create a new list with the specify capacity
 * Return pointer to the list structure if successful
 *        or NULL if the list can't be created 
 *        e.g. memory allocation error  
 */
LIST_T* listCreate(int capacity)
{
    // allocate the list structure
    LIST_T* list = (LIST_T*) calloc(1, sizeof(LIST_T));
    if (list == NULL)
    {
        return NULL;
    }
    // allocate an array to store the data
    list->data = (void**) calloc(capacity, sizeof(void*));
    if (list->data == NULL)
    {
        return NULL;
    }
    list->currentSize = 0;
    list->maxSize = capacity;
    list->currentIndex = 0;
    return list;
}

/* Destroy the list and release all memory
 */
void listDestroy(LIST_T* list)
{
    if (list != NULL)
    {
        int i=0;
        for (i=0; i<list->currentSize; i++) 
        {
            free(list->data[i]);
        }
        free(list->data);
        free(list);
    }
}

/* Returns the number of elements (could be zero)
 * or -1 if the list has not been created
 */
int listSize(LIST_T* list)
{
    if (list == NULL)
    {
        return -1;
    }
    return list->currentSize;
}

/* Insert new element into the list at the specify index
 * Return -1 if the list hasn't been created
 *        -2 if the list is full 
 *         1 if the operation is successful
 */
int listInsertAt(LIST_T* list, int index, void* data)
{
    if (list == NULL) 
    {
        return -1;
    }
    if (list->currentSize + 1 > list->maxSize)
    {
        return -2;
    }

    // move all item after index (inclusive) to next slot
    int i = 0;
    for (i = list->currentSize - 1; i >= index; i--)
    {
        list->data[i+1] = list->data[i];  
    }
    // update list size
    list->currentSize += 1;
    // add the new element
    list->data[index] = data;
    return 1;
}

/* Add new element at the end of the list
 * Return -1 if the list hasn't been created
 *        -2 if the list is full 
 *         1 if the operation is successful
 */
int listAppend(LIST_T* list, void* data)
{
    return listInsertAt(list, listSize(list), data);
}

/* Remove an element at the specify index
 * Return -1 if the list hasn't been created
 *         1 if the operation is successful
 */
int listRemoveAt(LIST_T* list, int index)
{
    if (list == NULL) 
    {
        return -1;
    }

    // move all item after index to previous slot
    int i = 0;
    for (i = index; i < list->currentSize; i++)
    {
        list->data[i] = list->data[i+1];  
    }
    // update list size
    list->currentSize -= 1;
    return 1;
}

/* Get an element at the specify index
 * Return -1 if the list hasn't been created
 *         1 if the operation is successful
 */
int listGet(LIST_T* list, int index, void** data)
{
    if (index >= list->currentSize)
    {
        return -1;
    }
    *data = list->data[index];
    return 1;
}

/* Reset currentIndex to the start point. 
 * Return -1 if the currentIndex hasn't been changed 
 *         1 if the currentIndex has been changed 
 */
int listReset(LIST_T* list)
{
    if (list == NULL) 
    {
        return -1;
    }

    list->currentIndex = 0;
    return 1;
}


/* Return value of currentIndex in the type of pointer and change it to the next index.
 * Return -2 if this function accesses an index that is not created
 *        -1 if the list is empty
 *         1 if the process is successfully
 */
int listGetNext(LIST_T* list, void** data)
{
    if (list == NULL) 
    {
        return -1;
    }
    if (list->currentIndex >= list->currentSize)
    {
        return -2;
    }

    *data = list->data[list->currentIndex];
    list->currentIndex += 1;
    return 1;
}


/* Move currentIndex to the end.
 * Return -1 if the currentIndex hasn't been changed 
 *         1 if the currentIndex has been changed 
 */
int listAtEnd(LIST_T* list)
{
    if (list == NULL) 
    {
        return -1;
    }
    
    return list->currentIndex == list->currentSize;
}