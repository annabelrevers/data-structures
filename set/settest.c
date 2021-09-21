/* 
 * settest.c - test program for set module
 *
 *
 * Annabel Revers, February 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"

static void itemcount(void *arg, const char *key, void *item);
static void printint(FILE *fp, const char *key, void *item);
static void intdelete(void *item);

/* **************************************** */
int main() 
{
    // make set
    set_t *set = set_new();
    printf("Added new set\n");
    printf("-------------------\n");

    // add key/item pair
    const char *mykey = "dog";
    int *myitem = malloc(sizeof(int));
    *myitem = 12;
    set_insert(set, mykey, myitem);
    printf("Added key 'dog'\n");
    printf("Item should be '12'\n");
    int *myitem2 = set_find(set, mykey);
    printf("Item for key 'dog': %d\n", *myitem2);
    printf("-------------------\n");

    // add another key/item pair
    const char *mykey2 = "cat";
    int *myitem3 = malloc(sizeof(int));
    *myitem3 = 31;
    set_insert(set, mykey2, myitem3);
    printf("Added key 'cat'\n");
    printf("Item should be '31'\n");
    char *myitem4 = set_find(set, mykey2);
    printf("Item for key 'cat': %d\n", *myitem4);
    printf("-------------------\n");

    // add another key/item pair
    const char *mykey3 = "turtle";
    int *myitem5 = malloc(sizeof(int));
    *myitem5 = 2;
    set_insert(set, mykey3, myitem5);
    printf("Added key 'turtle'\n");
    printf("Item should be 2\n");
    int *myitem6 = set_find(set, mykey3);
    printf("Item for key 'turtle': %d\n", *myitem6);
    printf("-------------------\n");

    // add key "dog" again   
    bool mybool = set_insert(set, mykey, myitem);
    printf("Tried adding key 'dog' again\n");
    printf("set_insert should return false\n");
    printf("Return value of set_insert:  %d\n", mybool);
    printf("-------------------\n");

    // none of these should be added to the set
    printf("test with null set, good key...\n");
    set_insert(NULL, "horses", NULL);
    printf("test with good set, null key...\n");
    set_insert(set, NULL, NULL); 
    printf("test with null set, null key...\n");
    set_insert(NULL, NULL, NULL);
    printf("-------------------\n");

    // count number of keys
    int key_count = 0;
    set_iterate(set, &key_count, itemcount);
    printf("Number of keys should be three\n");
    printf("Number of keys: %d\n", key_count);
    printf("-------------------\n");

    // print all key/item pairs
    printf("The set:\n");
    set_print(set, stdout, printint);
    printf("-------------------\n");

    // delete the set
    printf("delete the set...\n");
    set_delete(set, intdelete);
   
    return 0;
}

/*********** itemcount() ****************/
/* count the number of keys in a counter */
static void
itemcount(void *arg, const char *key, void *item)
{ 
    int *nitems = arg;
    (*nitems)++;
}

/************ printint() **************/
/* print an integer */
static void
printint(FILE *fp, const char *key, void *item)
{
    int *myint = item;
    fprintf(fp, "%d", *myint);
}

/*********** intdelete() *************/
/* deletes an int */
static void
intdelete(void *item)
{
    if (item != NULL) {
        free(item);
    }
}

