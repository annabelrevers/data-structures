/* 
 * counterstest.c - test program for counters module
 *
 * Annabel Revers, February 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counters.h"

static void itemcount(void *arg, const int key, const int count);

/* **************************************** */
int main() 
{
    // make new counter
    counters_t *counter = counters_new();
    printf("Added new counter\n");
    printf("-------------------\n");

    // add key/item pair
    counters_add(counter, 1);
    printf("Added key 1\n");
    printf("Count should be 1\n");
    int key = counters_get(counter, 1);
    printf("Count for key 1: %d\n", key);
    printf("-------------------\n");

    // add another key/item pair
    counters_add(counter, 20);
    printf("Added key 20\n");
    printf("Count should be 1\n");
    int key2 = counters_get(counter, 20);
    printf("Count for key 20: %d\n", key2);
    printf("-------------------\n");

    // add another key/item pair
    counters_add(counter, 100);
    printf("Added key 100\n");
    printf("Count should be 1\n");
    int key3 = counters_get(counter, 100);
    printf("Count for key 100: %d\n", key3);
    printf("-------------------\n");

    // set count of key 1 to 12
    counters_set(counter, 1, 12);
    printf("Changed count of key 1 to 12\n");
    int key4 = counters_get(counter, 1);
    printf("Count should be 12\n");
    printf("Count for key 1: %d\n", key4);
    printf("-------------------\n");

    // set count of key 100 to 24
    counters_set(counter, 100, 24);
    printf("Changed count of key 100 to 24\n");
    int key5 = counters_get(counter, 100);
    printf("Count should be 24\n");
    printf("Count for key 100: %d\n", key5);
    printf("-------------------\n");

    // add key 20 again
    counters_add(counter, 20);
    printf("Added key 20 again\n");
    int key6 = counters_get(counter, 20);
    printf("Count should be 2\n");
    printf("Count for key 20: %d\n", key6);
    printf("-------------------\n");

    // count number of keys
    int key_count = 0;
    counters_iterate(counter, &key_count, itemcount);
    printf("Number of keys should be three\n");
    printf("Number of keys: %d\n", key_count);
    printf("-------------------\n");
    
    printf("test with null count, good key...\n");
    counters_add(NULL, 3);
    printf("test with negative key...\n");
    counters_add(counter, -3); 
    printf("test with null counter, negative key...\n");
    counters_add(NULL, -10);
    printf("-------------------\n");

    // print all key=item pairs
    printf("The counter:\n");
    counters_print(counter, stdout);
    printf("-------------------\n");

    // delete counter
    printf("delete the counter...\n");
    counters_delete(counter);
   
    return 0;
}

/*********** itemcount() ****************/
/* count the number of keys in a counter */
static void itemcount(void *arg, const int key, const int count)
{ 
    int *nitems = arg;
    (*nitems)++;
}

