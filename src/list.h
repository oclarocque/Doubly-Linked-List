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
** Type Declarations
*/
typedef struct element {
    int val;
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
void    list_print(list_t *l);
int     list_find(list_t *l, int val);
void    list_add_last(list_t *l, int val);
void    list_add_first(list_t *l, int val);
void    list_remove(list_t *l, int val);
void    list_remove_pos(list_t *l, int pos);
void    list_sort(list_t *l);
list_t *list_merge(list_t *l1, list_t *l2);


#endif /* LIST_H_ */

#ifdef __cplusplus
}
#endif

