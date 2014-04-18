/**
 * @file
 * A List Class for C.
 * imitates object oriented on C.
 * @copyright MIT License.
 * @author y.yamaki
 */
#ifndef _LIST_H_
#define _LIST_H_
#include <stdbool.h>

typedef struct Element Element;

/**
 * A Element that inner class of List.
 */
struct Element {
	Element* next;
	void* data;
};

/**
 * A type of List
 */
typedef struct List List;

/**
 * List class.
 */
struct List {

	/* A max index of List */
	int idx;
	/* A data of List. */
	Element* head;
	/* A cache of tail data */
	Element* tail;

	/**
	 * Appends the specified element to the end of this list.
	 * @param this a instance of List
	 * @param element to be appended to this list
	 * @return true if this List changed as a result of the call
	 */
	bool (*add)(List* this, void* element);

	/**
	 * Appends all of the elements in the specified
	 * collection to the end of this list.
	 * @param this a instance of List
	 * @param list collection containing elements to be added to this list
	 * @return true if this list changed as a result of the call
	 */
	bool (*addAll)(List* this, List* list);
	void* (*get)(List* this, int index);
	void (*clear)(List* this, bool withFree);
	void (*remove)(List* this, int index, bool withFree);
	int (*size)(List* this);
	int (*indexOf)(List* this, void* element);
	int (*lastIndexOf)(List* this, void* element);
};

extern List* List_new(void);
extern void List_destory(List** this, bool withFree);

#endif /* _LIST_H_ */

