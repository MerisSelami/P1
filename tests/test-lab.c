#include "harness/unity.h"
#include "../src/lab.h"
#include <string.h>
#include <stdlib.h>

void destroy_data(void *data) {
    free(data);
}

int compare_to(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}

void setUp(void) {}
void tearDown(void) {}

void test_list_init_and_destroy(void) {
    list_t *list = list_init(destroy_data, compare_to);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_NOT_NULL(list->head);
    TEST_ASSERT_EQUAL(0, list->size);
    list_destroy(&list);
    TEST_ASSERT_NULL(list);
}

void test_list_add(void) {
    list_t *list = list_init(destroy_data, compare_to);

    char *data = strdup("Test Data");
    list_add(list, data);

    TEST_ASSERT_EQUAL(1, list->size);
    TEST_ASSERT_EQUAL_STRING("Test Data", (char *)list->head->next->data);

    list_destroy(&list);
}

void test_list_remove_index(void) {
    list_t *list = list_init(destroy_data, compare_to);

    char *data1 = strdup("First");
    char *data2 = strdup("Second");
    list_add(list, data1);
    list_add(list, data2);

    void *removed = list_remove_index(list, 0);
    TEST_ASSERT_EQUAL_STRING("Second", (char *)removed);
    free(removed);

    TEST_ASSERT_EQUAL(1, list->size);

    list_destroy(&list);
}

void test_list_indexof(void) {
    list_t *list = list_init(destroy_data, compare_to);

    char *data1 = strdup("First");
    char *data2 = strdup("Second");
    list_add(list, data1);
    list_add(list, data2);

    int index = list_indexof(list, "Second");
    TEST_ASSERT_EQUAL(0, index);

    index = list_indexof(list, "First");
    TEST_ASSERT_EQUAL(1, index);

    index = list_indexof(list, "Nonexistent");
    TEST_ASSERT_EQUAL(-1, index);

    list_destroy(&list);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_list_init_and_destroy);
    RUN_TEST(test_list_add);
    RUN_TEST(test_list_remove_index);
    RUN_TEST(test_list_indexof);
    return UNITY_END();
}
