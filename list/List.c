/**
 * @file
 * A List Class for C.
 * imitates object oriented on C.
 * implement source.
 * @copyright MIT License.
 * @author y.yamaki
 */
#include <stdlib.h>
#include "List.h"

static bool add(List* this, void* element);
static bool addAll(List* this, List* list);
static void* get(List* this, int index);
static void clear(List* this, bool withFree);
static void remove(List* this, int index, bool withFree);
static int size(List* this);
static int indexOf(List* this, void* element);
static int lastIndexOf(List* this, void* element);

List*
List_new(void)
{
	List* ins;
	ins = (List*) malloc(sizeof(List));
	if (ins == NULL) return NULL;
	ins->idx = -1;
	ins->head = NULL;
	ins->tail = NULL;

	ins->add = add;
	ins->addAll = addAll;
	ins->get = get;
	ins->clear = clear;
	ins->remove = remove;
	ins->size = size;
	ins->indexOf = indexOf;
	ins->lastIndexOf = lastIndexOf;

	return ins;
}

void
List_destory(List** this, bool withFree)
{
	(*this)->clear(*this, withFree);
	free(*this);
	*this = NULL;
}

static bool
add(List* this, void* element)
{
	bool result; 
	Element* ele;

	result = false;
	do {
		ele = (Element*) malloc(sizeof(Element));
		if (ele == NULL) break;
		ele->data = element;
		ele->next = NULL;
		if (this->head == NULL) {
			this->head = ele;
		} else {
			this->tail->next = ele;
		}
		this->tail = ele;
		this->idx++;

		result = true;
	} while(0);

	return result;
}

static bool
addAll(List* this, List* list)
{
	int i, sz;
	bool result;

	result = false;
	sz = list->size(list);
	for (i = 0; i < sz; i++)
		if (this->add(this, list->get(list, i)) == false) break;
	if (i == sz) result = true;
	return result;
}

static void*
get(List* this, int index)
{
	Element* cur;
	void* result;
	int i;

	if (index > this->idx) return NULL;
	cur = this->head;
	for (i = 0; i < (index + 1); i++)
		cur = cur->next;
	result = cur->data;
	return result;
}

static void
clear(List* this, bool withFree)
{
	Element* tgt;
	Element* next;

	next = this->head;
	while (next != NULL) {
		tgt = next;
		next = next->next;
		if (withFree == true) free(tgt->data);
		free(tgt);
	}
	this->head = NULL;
	this->tail = NULL;
	this->idx = -1;
}

static void
remove(List* this, int index, bool withFree)
{
	Element* tgt;
	Element* next;
	int i;

	if (index > this->idx) return;

	next = this->head;
	i = 0;
	while (next != NULL) {
		tgt = next;
		next = next->next;
		if (i >= index + 1) {
			/* TODO remove process */

			break;
		}



		i++;
	}

	



}

static int
size(List* this)
{
	return this->idx + 1;
}

static int indexOf(List* this, void* element){return -1;}
static int lastIndexOf(List* this, void* element){return -1;}


