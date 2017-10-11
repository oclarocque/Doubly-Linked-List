/* list.h -- a doubly linked list implementation in C
**
** Copyright (C) 2017 Olivier C. Larocque <oclarocque@protonmail.com>
**
** This software may be modified and distributed under the terms
** of the MIT license. See the LICENSE file for details.
*/
#ifndef LIST_H_
#define LIST_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
** Includes
*/
#include <stdbool.h>


/*
** Type Declarations
*/
typedef struct element {
    void *val;
    struct element *next;
    struct element *prev;
} element_t;

typedef struct list {
    int size;
    element_t *head;
    element_t *tail;
} list_t ;


/*
** Function Declarations
*/
list_t *list_create(void);
void    list_destroy(list_t *l);
void    list_clear(list_t *l);
void    list_print(list_t *l);
bool    list_is_empty(list_t *l);
bool    list_is_not_empty(list_t *l);
int     list_first(list_t* l);
int     list_last(list_t* l);
int     list_find(list_t *l, void *val);
int     list_find_pos(list_t *l, int pos);
void    list_add_last(list_t *l, void *val);
void    list_add_first(list_t *l, void *val);
void    list_remove(list_t *l, void *val);
void    list_remove_pos(list_t *l, int pos);
void    list_sort(list_t *l);
void    list_merge(list_t *left, list_t *right, list_t *result);


#endif /* LIST_H_ */

#ifdef __cplusplus
}
#endif

