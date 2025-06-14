#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define YAC_UNORDERED_MAP_IMPLEMENTATION
#include "../yac_unordered_map.h"

int compare_key(void* lhs, void* rhs)
{
    return strcmp((char*)lhs, (char*)rhs);
}

typedef struct _Employ {
    char year;
    char level;
    int id;
} Employ;

void test_init_and_deinit(void)
{
    YacUnorderedMap* map = YacUnorderedMapInit();
    assert(map != NULL);
    YacUnorderedMapDeinit(map);
}

void test_put_and_get(void)
{
    {
        // KEY = int, VALUE = int
        YacUnorderedMap* map;

        map = YacUnorderedMapInit();

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

        YacUnorderedMapDeinit(map);
    }
    {
        // KEY = char*, VALUE = int
        YacUnorderedMap* map = YacUnorderedMapInit();
        map->set_compare(map, compare_key);

        map->put(map, (void*)(char*)"one", (void*)(int*)1);
        map->put(map, (void*)(char*)"two", (void*)(int*)2);
        map->put(map, (void*)(char*)"three", (void*)(int*)3);

        int* val = (int*)map->get(map, (void*)(char*)"two");
        assert((int*)val == (int*)2);

        YacUnorderedMapDeinit(map);
    }
    {
        // KEY = char*, VALUE = Point
        typedef struct {
            int x;
            int y;
        } Point;

        YacUnorderedMap* map = YacUnorderedMapInit();
        map->set_compare(map, compare_key);

        map->put(map, (void*)(char*)"one", (void*)(Point*)&(Point){11, 111});
        map->put(map, (void*)(char*)"two", (void*)(Point*)&(Point){22, 222});
        map->put(map, (void*)(char*)"three", (void*)(Point*)&(Point){33, 333});

        Point* val = (Point*)map->get(map, (void*)(char*)"two");
        assert(((Point*)val)->x == 22);
        assert(((Point*)val)->y == 222);

        YacUnorderedMapDeinit(map);
    }
}

void test_contain(void)
{
    {
        YacUnorderedMap* map = YacUnorderedMapInit();
        map->set_compare(map, compare_key);

        map->put(map, (void*)(char*)"one", (void*)(int*)1);
        map->put(map, (void*)(char*)"two", (void*)(int*)2);
        map->put(map, (void*)(char*)"three", (void*)(int*)3);

        int* val = (int*)map->get(map, (void*)(char*)"not found");
        assert(val == NULL);

        YacUnorderedMapDeinit(map);
    }
    {
        YacUnorderedMap* map = YacUnorderedMapInit();
        map->set_compare(map, compare_key);

        map->put(map, (void*)(char*)"one", (void*)(int*)1);
        map->put(map, (void*)(char*)"two", (void*)(int*)2);
        map->put(map, (void*)(char*)"three", (void*)(int*)3);

        bool found = map->contain(map, (void*)(char*)"not found");
        assert(found == false);

        YacUnorderedMapDeinit(map);
    }
}

void test_remove(void)
{
    YacUnorderedMap* map = YacUnorderedMapInit();
    map->set_compare(map, compare_key);

    map->put(map, (void*)(char*)"one", (void*)(int*)1);
    map->put(map, (void*)(char*)"two", (void*)(int*)2);
    map->put(map, (void*)(char*)"three", (void*)(int*)3);

    bool found = map->contain(map, (void*)(char*)"two");
    assert(found == true);

    assert(map->remove(map, (void*)(char*)"two") == true);

    found = map->contain(map, (void*)(char*)"two");
    assert(found == false);

    YacUnorderedMapDeinit(map);
}

void test_iterator(void)
{
    YacUnorderedMap* map = YacUnorderedMapInit();
    map->set_compare(map, compare_key);

    map->put(map, (void*)(char*)"one", (void*)(int*)1);
    map->put(map, (void*)(char*)"two", (void*)(int*)2);
    map->put(map, (void*)(char*)"three", (void*)(int*)3);

    // for loop
    {
        int expected = 0;
        map->first(map);
        for (YacUnorderedMapPair *pair = map->next(map); pair != NULL; pair = map->next(map)) {
            expected += 1;
            assert((unsigned long long)(int*)pair->value == expected);
        }
    }

    // while loop
    {
        YacUnorderedMapPair *pair = NULL;
        int expected = 0;
        map->first(map);
        while ((pair = map->next(map)) != NULL) {
            expected += 1;
            assert((unsigned long long)(int*)pair->value == expected);
        }
    }

    YacUnorderedMapDeinit(map);
}

void test_hash_murmur32(void)
{
    unsigned value = YacUnorderedMapHashMurMur32(NULL, 32);
    assert(value == 0);

    value = YacUnorderedMapHashMurMur32("NULL", 0);
    assert(value == 0);

    // Test string key.
    value = YacUnorderedMapHashMurMur32((void*)"1", 1);
    value = YacUnorderedMapHashMurMur32((void*)"12", 2);
    value = YacUnorderedMapHashMurMur32((void*)"123", 3);
    value = YacUnorderedMapHashMurMur32((void*)"1234", 4);
    value = YacUnorderedMapHashMurMur32((void*)"12345", 5);

    // Test integer key.
    int key_int = 32767;
    value = YacUnorderedMapHashMurMur32((void*)&key_int, sizeof(int));
    long long key_long = 32767;
    value = YacUnorderedMapHashMurMur32((void*)&key_long, sizeof(long long));

    // Test Floating point key.
    float key_float = 32767.0;
    value = YacUnorderedMapHashMurMur32((void*)&key_float, sizeof(float));
    double key_double = 32767.0;
    value = YacUnorderedMapHashMurMur32((void*)&key_double, sizeof(double));

    // Test structure key.
    Employ* employ = malloc(sizeof(Employ));
    memset(employ, 0, sizeof(Employ));
    employ->year = 1;
    employ->level = 10;
    employ->id = 25692;
    value = YacUnorderedMapHashMurMur32((void*)employ, sizeof(Employ));
    free(employ);

}

int main(void)
{
    test_init_and_deinit();
    test_put_and_get();
    test_contain();
    test_remove();
    test_iterator();

    test_hash_murmur32();

    return 0;
}
