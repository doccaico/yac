#include <assert.h>
#include <stdio.h>
#include <string.h>

#define YACC_MAP_IMPLEMENTATION
#include "../yacc_map.h"

void test_map_init_and_deinit(void)
{
    TreeMap* map;

    map = TreeMapInit();
    assert(map != NULL);
    TreeMapDeinit(map);
}

void test_map_put_and_get(void)
{
    {
        // KEY = int, VALUE = int
        TreeMap* map;

        map = TreeMapInit();

        map->put(map, (void*)(int*)1, (void*)(int*)10);
        map->put(map, (void*)(int*)2, (void*)(int*)20);
        map->put(map, (void*)(int*)3, (void*)(int*)30);
        assert(map->size(map) == 3);

        int* val = (int*)map->get(map, (void*)(int*)2);
        assert((int*)val == (int*)20);

        map->put(map, (void*)(int*)2, (void*)(int*)9000);
        assert(map->size(map) == 3);
        val = (int*)map->get(map, (void*)(int*)2);
        assert((int*)val == (int*)9000);

        TreeMapDeinit(map);
    }
    {
        // KEY = char*, VALUE = int
        TreeMap* map;

        map = TreeMapInit();

        map->put(map, (void*)(char*)"1", (void*)(int*)10);
        map->put(map, (void*)(char*)"2", (void*)(int*)20);
        map->put(map, (void*)(char*)"3", (void*)(int*)30);

        int* val = (int*)map->get(map, (void*)(char*)"2");
        assert((int*)val == (int*)20);

        TreeMapDeinit(map);
    }
    {
        // KEY = char*, VALUE = Point
        typedef struct {
            int x;
            int y;
        } Point;

        TreeMap* map;

        map = TreeMapInit();

        map->put(map, (void*)(char*)"1", (void*)(Point*)&(Point){11, 111});
        map->put(map, (void*)(char*)"2", (void*)(Point*)&(Point){22, 222});
        map->put(map, (void*)(char*)"3", (void*)(Point*)&(Point){33, 333});

        Point* val = (Point*)map->get(map, (void*)(char*)"2");
        assert(((Point*)val)->x == 22);
        assert(((Point*)val)->y == 222);

        TreeMapDeinit(map);
    }
}

void test_map_find(void)
{
    TreeMap* map;

    map = TreeMapInit();

    map->put(map, (void*)(char*)"1", (void*)(int*)10);
    map->put(map, (void*)(char*)"2", (void*)(int*)20);
    map->put(map, (void*)(char*)"3", (void*)(int*)30);

    bool found = map->find(map, (void*)(char*)"2");
    assert(found);

    found = map->find(map, (void*)(char*)"9999");
    assert(!found);

    TreeMapDeinit(map);
}

void test_map_remove(void)
{
    TreeMap* map;

    map = TreeMapInit();

    map->put(map, (void*)(char*)"1", (void*)(int*)10);
    map->put(map, (void*)(char*)"2", (void*)(int*)20);
    map->put(map, (void*)(char*)"3", (void*)(int*)30);

    assert(map->size(map) == 3);

    bool success = map->remove(map, (void*)(char*)"2");
    assert(success);

    success = map->remove(map, (void*)(char*)"2");
    assert(!success);

    bool found = map->find(map, (void*)(char*)"2");
    assert(!found);

    assert(map->size(map) == 2);

    TreeMapDeinit(map);
}

void test_map_minimum_and_maximum(void)
{
    TreeMap* map;

    map = TreeMapInit();

    map->put(map, (void*)(char*)"1", (void*)(int*)10);
    map->put(map, (void*)(char*)"2", (void*)(int*)20);
    map->put(map, (void*)(char*)"3", (void*)(int*)30);

    assert(map->size(map) == 3);

    Pair* pair_min = map->minimum(map);
    assert(strcmp((char*)(void*)pair_min->key, "1") == 0);
    assert((int*)(void*)pair_min->value == (int*)10);

    Pair* pair_max = map->maximum(map);
    assert(strcmp((char*)(void*)pair_max->key, "3") == 0);
    assert((int*)(void*)pair_max->value == (int*)30);

    TreeMapDeinit(map);
}

void test_map_predecessor_and_successor(void)
{
    TreeMap* map;

    map = TreeMapInit();

    map->put(map, (void*)(char*)"1", (void*)(int*)10);
    map->put(map, (void*)(char*)"2", (void*)(int*)20);
    map->put(map, (void*)(char*)"3", (void*)(int*)30);

    assert(map->size(map) == 3);

    Pair* pair_pre = map->predecessor(map, (void*)(char*)"2");
    assert(strcmp((char*)(void*)pair_pre->key, "1") == 0);
    assert((int*)(void*)pair_pre->value == (int*)10);

    Pair* pair_max = map->successor(map, (void*)(char*)"2");
    assert(strcmp((char*)(void*)pair_max->key, "3") == 0);
    assert((int*)(void*)pair_max->value == (int*)30);

    TreeMapDeinit(map);
}

void test_map_iterator(void)
{
    TreeMap* map;

    map = TreeMapInit();

    map->put(map, (void*)(char*)"1", (void*)(int*)10);
    map->put(map, (void*)(char*)"2", (void*)(int*)20);
    map->put(map, (void*)(char*)"3", (void*)(int*)30);

    // for loop
    int expected = 0;
    map->first(map);
    for (Pair *pair = map->next(map); pair != NULL; pair = map->next(map)) {
        expected += 10;
        assert((unsigned long long)(int*)pair->value == expected);
    }

    // while loop
    Pair *pair = NULL;
    expected = 0;
    map->first(map);
    while ((pair = map->next(map)) != NULL) {
        expected += 10;
        assert((unsigned long long)(int*)pair->value == expected);
    }

    // while loop (reverse version)
    pair = NULL;
    expected = 30;
    map->first(map);
    while ((pair = map->reverse_next(map)) != NULL) {
        assert((unsigned long long)(int*)pair->value == expected);
        expected -= 10;
    }

    TreeMapDeinit(map);
}

void test_map_default_compare(void)
{
    TreeMap* map;

    map = TreeMapInit();

    map->put(map, (void*)(int*)3, (void*)(int*)30);
    map->put(map, (void*)(int*)1, (void*)(int*)10);
    map->put(map, (void*)(int*)2, (void*)(int*)20);
    assert(map->size(map) == 3);

    int expected = 0;
    map->first(map);
    for (Pair *pair = map->next(map); pair != NULL; pair = map->next(map)) {
        expected += 10;
        assert((unsigned long long)(int*)pair->value == expected);
    }

    TreeMapDeinit(map);
}

int compare_key(void* lhs, void* rhs)
{
    return strcmp((char*)lhs, (char*)rhs);
}

void clean_key(void* key)
{
    (void)key;
    // puts("clean key");
}

void clean_value(void* value)
{
    (void)value;
    // puts("clean value");
}

void test_map_compare_and_clean(void)
{
    TreeMap* map;

    map = TreeMapInit();
    map->set_compare(map, compare_key);
    map->set_clean_key(map, clean_key);
    map->set_clean_value(map, clean_value);

    map->put(map, (void*)(char*)"c", (void*)(int*)30);
    map->put(map, (void*)(char*)"a", (void*)(int*)10);
    map->put(map, (void*)(char*)"b", (void*)(int*)20);

    assert(map->size(map) == 3);

    int expected = 0;
    map->first(map);
    for (Pair *pair = map->next(map); pair != NULL; pair = map->next(map)) {
        expected += 10;
        assert((unsigned long long)(int*)pair->value == expected);
    }

    TreeMapDeinit(map);
}

int main(void)
{
    test_map_init_and_deinit();
    test_map_put_and_get();
    test_map_find();
    test_map_remove();
    test_map_minimum_and_maximum();
    test_map_predecessor_and_successor();
    test_map_iterator();
    test_map_default_compare();
    test_map_compare_and_clean();

    return 0;
}
