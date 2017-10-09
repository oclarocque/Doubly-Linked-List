/* list.c -- a doubly linked list implementation in C
**
** Copyright (C) 2017 Olivier C. Larocque <oclarocque@protonmail.com>
**
** This software may be modified and distributed under the terms
** of the MIT license. See the LICENSE file for details.
*/

/*
** Includes
*/
#include <stdlib.h>
#include <stdio.h>
#include "list.h"


/*
** Local Function Declarations
*/
static void remove_element(list_t *l, element_t *e);


/*
** Function Defintions
*/

/*
** list_create(): create a list dynamically
** in  <- none
** out -> new list
*/
list_t *list_create(void)
{
    list_t *l = (list_t *)malloc(sizeof(list_t));

    l->size  = 0;
    l->head  = NULL;
    l->tail  = NULL;

    return l;
}

/*
** list_destroy(): free the list and all its elements
** in  <- l: list
** out -> none
*/
void list_destroy(list_t *l)
{
    while (l->size) {
        remove_element(l, l->tail);
    }
    free(l);
}

/*
** list_print(): print to stdout all elements of the list
** in  <- l: list
** out -> none
*/
void list_print(list_t *l)
{
    element_t *e = l->head;
    int pos = 0;

    while (e != NULL) {
        printf("Element %d has value %d\n", pos++, e->val);
        e = e->next;
    }
}

/*
** list_find(): find an element in the list
** in  <- l:   list
**     <- val: value of the element to find
** out -> position of the element
*/
int list_find(list_t *l, int val)
{
    element_t *e = l->head;
    int pos = 0;

    while (e != NULL) {
        if (e->val == val) {
            return pos;
        }
        e = e->next;
        pos++;
    }

    return (-1);
}

/*
** list_add_last(): add an element to the list at the last position
** in  <- l:   list
**     <- val: value of the element to add
** out -> none
*/
void list_add_last(list_t *l, int val)
{
    element_t *new_tail = (element_t *)malloc(sizeof(element_t));
    element_t *old_tail = l->tail;

    new_tail->val  = val;
    new_tail->next = NULL;
    new_tail->prev = old_tail;

    if (old_tail != NULL) {
        old_tail->next = new_tail;
    }

    l->tail = new_tail;

    l->size++;

    if (l->size == 1) {
        l->head = l->tail;
    }
}

/*
** list_add_first(): add an element to the list at the first position
** in  <- l:   list
**     <- val: value of the element to add
** out -> none
*/
void list_add_first(list_t *l, int val)
{
    element_t *new_head = (element_t *)malloc(sizeof(element_t));
    element_t *old_head = l->head;

    new_head->val  = val;
    new_head->next = old_head;
    new_head->prev = NULL;

    if (old_head != NULL) {
        old_head->prev = new_head;
    }

    l->head = new_head;

    l->size++;

    if (l->size == 1) {
        l->tail = l->head;
    }
}

/*
** list_remove(): remove an element from the list
** in  <- l:   list
**     <- val: value of the element to remove
** out -> none
*/
void list_remove(list_t *l, int val)
{
    element_t *e = l->head;

    while (e != NULL) {
        if (e->val == val) {
            remove_element(l, e);
            return;
        }
        e = e->next;
    }
}

/*
** list_remove_pos(): remove an element from the list
** in  <- l:   list
**     <- pos: position of the element to remove
** out -> none
*/
void list_remove_pos(list_t *l, int pos)
{
    element_t *e = l->head;
    int i = 0;

    while (e != NULL) {
        if (i == pos) {
            remove_element(l, e);
            return;
        }
        i++;
        e = e->next;
    }
}

/*
** list_sort(): sort the list from the smallest value to the biggest
** in  <- l: list
** out -> none
*/
void list_sort(list_t *l)
{

}

/*
** list_merge(): merge two lists
** in  <- l1: fisrt list
**     <- l2: second list
** out -> combined list
*/
list_t *list_merge(list_t *l1, list_t *l2)
{
    return l1;
}


/*
** Local Function Definitions
*/

/*
** remove(): remove an element from the list
** in  <- l: list
**     <- e: element to remove
** out -> none
*/
static void remove_element(list_t *l, element_t *e)
{
    if (l->size == 1) {
        l->head = NULL;
        l->tail = NULL;
    } else if (e == l->head) {
        l->head = e->next;
        l->head->prev = NULL;
    } else if (e == l->tail) {
        l->tail = e->prev;
        l->tail->next = NULL;
    } else {
        e->prev->next = e->next;
        e->next->prev = e->prev;
    }

    free(e);

    l->size--;
}

