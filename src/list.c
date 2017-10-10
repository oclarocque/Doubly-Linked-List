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
** Function Definitions
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
** list_clear(): free all list elements
** in  <- l: list
** out -> none
*/
void list_clear(list_t *l)
{
    while (l->size) {
        remove_element(l, l->tail);
    }
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
** list_is_empty(): check if the list is empty
** in  <- l: list
** out -> true if empty, false otherwise
*/
bool list_is_empty(list_t *l)
{
    return !l->size;
}

/*
** list_is_not_empty(): check if the list is not empty
** in  <- l: list
** out -> true if not empty, false otherwise
*/
bool list_is_not_empty(list_t *l)
{
    return !!l->size;
}

/*
** list_first(): return the first element value
** in  <- l: list
** out -> value
*/
int list_first(list_t* l)
{
    return l->head->val;
}

/*
** list_last(): return the last element value
** in  <- l: list
** out -> value
*/
int list_last(list_t* l)
{
    return l->tail->val;
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
** list_find_pos(): find an element in the list
** in  <- l:   list
**     <- pos: position of the element to find
** out -> value of the element
*/
int list_find_pos(list_t *l, int pos)
{
    element_t *e = l->head;
    int i = 0;

    while (e != NULL) {
        if (i == pos) {
            return e->val;
        }
        e = e->next;
        i++;
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
    list_t *left;
    list_t *right;
    int val;
    int i;

    if (l->size <= 1) {
        return;
    }

    left  = list_create();
    right = list_create();

    for (i = 0; i < l->size; i++) {
        val = list_find_pos(l, i);
        if (i < (l->size / 2)) {
            list_add_last(left, val);
        } else {
            list_add_last(right, val);
        }
    }

    list_sort(left);
    list_sort(right);

    list_merge(left, right, l);

    list_destroy(left);
    list_destroy(right);
}


/*
** list_merge(): merge two ordered lists
** in  <- left:   first ordered list
**     <- right:  second ordered list
** out -> result: merged list
*/
void list_merge(list_t *left, list_t *right, list_t *result)
{
    list_clear(result);

    while ((list_is_not_empty(left)) && (list_is_not_empty(right))) {
        if (list_first(left) <= list_first(right)) {
            list_add_last(result, list_first(left));
            list_remove_pos(left, 0);
        } else {
            list_add_last(result, list_first(right));
            list_remove_pos(right, 0);
        }
    }

    while (list_is_not_empty(left)) {
        list_add_last(result, list_first(left));
        list_remove_pos(left, 0);
    }
    while (list_is_not_empty(right)) {
        list_add_last(result, list_first(right));
        list_remove_pos(right, 0);
    }
}


/*
** Local Function Definitions
*/

/*
** remove_element(): remove an element from the list
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

