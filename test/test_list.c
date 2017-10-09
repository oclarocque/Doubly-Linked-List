/* test_list.c -- unit tests for list.c/.h
**
** Copyright (C) 2017 Olivier C. Larocque <oclarocque@protonmail.com>
**
** This software may be modified and distributed under the terms
** of the MIT license. See the LICENSE file for details.
*/

/*
** Includes
*/
#include "unity.h"
#include "list.h"

/*
** Defines
*/
#define FILL_COUNT 11


/*
** Local Data
*/
static list_t *l;


/*
** Local Functions
*/
static void fill(list_t *l, int count)
{
    int i;

    for (i = 0; i < count; i++) {
        list_add_last(l, i);
    }
}


/*
** Set Up / Tear Down
*/
void setUp(void)
{
    l = NULL;
}

void tearDown(void)
{
    list_destroy(l);
}


/*
** Unit Tests
*/
void test_list_create(void)
{
    l = list_create();

    TEST_ASSERT_NOT_NULL(l);
    TEST_ASSERT_EQUAL_INT(0, l->size);
    TEST_ASSERT_NULL(l->head);
    TEST_ASSERT_NULL(l->tail);
}

void test_list_add_first(void)
{
    l = list_create();

    list_add_first(l, 50);

    TEST_ASSERT_EQUAL_INT(1, l->size);
    TEST_ASSERT_NOT_NULL(l->head);
    TEST_ASSERT_NOT_NULL(l->tail);
    TEST_ASSERT_EQUAL(l->tail, l->head);
}

void test_list_add_last(void)
{
    l = list_create();

    list_add_last(l, 100);

    TEST_ASSERT_EQUAL_INT(1, l->size);
    TEST_ASSERT_NOT_NULL(l->head);
    TEST_ASSERT_NOT_NULL(l->tail);
    TEST_ASSERT_EQUAL(l->tail, l->head);
}

void test_list_add_first_and_last(void)
{
    l = list_create();

    list_add_first(l, 50);
    list_add_last(l, 100);

    TEST_ASSERT_EQUAL_INT(2, l->size);
    TEST_ASSERT_NOT_NULL(l->head);
    TEST_ASSERT_NOT_NULL(l->tail);
    TEST_ASSERT_NOT_EQUAL(l->head, l->tail);
}

void test_list_add_first_10(void)
{
    l = list_create();
    int i = 0;

    for (i = 0; i < 10; i++) {
        list_add_first(l, i);
    }

    TEST_ASSERT_EQUAL_INT(10, l->size);
}

void test_list_add_last_10(void)
{
    l = list_create();
    int i = 0;

    for (i = 0; i < 10; i++) {
        list_add_last(l, i);
    }

    TEST_ASSERT_EQUAL_INT(10, l->size);
}

void test_list_find(void)
{
    l = list_create();
    int i = 0;
    int pos = 0;

    fill(l, FILL_COUNT);

    pos = list_find(l, 5);

    TEST_ASSERT_EQUAL_INT(5, pos);
}

void test_list_print(void)
{
    l = list_create();
    int i = 0;
    int pos = 0;

    fill(l, 10);

    list_print(l);
}

void test_remove(void)
{
    l = list_create();
    int pos = FILL_COUNT;

    fill(l, FILL_COUNT);

    list_remove(l, 5);

    pos = list_find(l, 5);

    TEST_ASSERT_EQUAL_INT(FILL_COUNT - 1, l->size);
    TEST_ASSERT_EQUAL_INT(-1, pos);
}

void test_remove_first(void)
{
    l = list_create();
    int pos = FILL_COUNT;

    fill(l, FILL_COUNT);

    list_remove(l, 0);

    pos = list_find(l, 0);

    TEST_ASSERT_EQUAL_INT(-1, pos);
}

void test_remove_last(void)
{
    l = list_create();
    int pos = FILL_COUNT;

    fill(l, FILL_COUNT);

    list_remove(l, FILL_COUNT - 1);

    pos = list_find(l, FILL_COUNT - 1);

    TEST_ASSERT_EQUAL_INT(-1, pos);
}

void test_remove_pos(void)
{
    l = list_create();
    int pos = FILL_COUNT + 1;

    fill(l, FILL_COUNT);

    list_remove_pos(l, 5);

    pos = list_find(l, 5);

    TEST_ASSERT_EQUAL_INT(FILL_COUNT - 1, l->size);
    TEST_ASSERT_EQUAL_INT(-1, pos);
}

void test_remove_pos_first(void)
{
    l = list_create();
    int pos = FILL_COUNT;

    fill(l, FILL_COUNT);

    list_remove_pos(l, 0);

    pos = list_find(l, 0);

    TEST_ASSERT_EQUAL_INT(-1, pos);
}

void test_remove_pos_last(void)
{
    l = list_create();
    int pos = FILL_COUNT;

    fill(l, FILL_COUNT);

    list_remove_pos(l, FILL_COUNT - 1);

    pos = list_find(l, FILL_COUNT - 1);

    TEST_ASSERT_EQUAL_INT(-1, pos);
}

