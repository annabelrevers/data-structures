/* 
 * hashtabletest.c - test program for CS50 hashtable module
 *
 *
 * Annabel Revers, February 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

static void itemcount(void *arg, const char *key, void *item);
static void printint(FILE *fp, const char *key, void *item);
static void intdelete(void *item);

int
main()
{
    // create a set
    printf("Made a new hashtable\n");
    hashtable_t *ht = hashtable_new(10);
    printf("-------------------\n");

    // add key/item pair
    const char *mykey = "dog";
    int *myitem = malloc(sizeof(int));
    *myitem = 12;
    hashtable_insert(ht, mykey, myitem);
    printf("Added key 'dog'\n");
    int *myitem2 = hashtable_find(ht, mykey);
    printf("Item should be '12'\n");
    printf("Item for key 'dog': %d\n", *myitem2);
    printf("-------------------\n");

    // add another key/item pair
    const char *mykey2 = "cat";
    int *myitem3 = malloc(sizeof(int));
    *myitem3 = 29;
    hashtable_insert(ht, mykey2, myitem3);
    printf("Added key 'cat'\n");
    int *myitem4 = hashtable_find(ht, mykey2);
    printf("Item should be '29'\n");
    printf("Item for key 'cat': %d\n", *myitem4);
    printf("-------------------\n");
    
    // add another key/item pair
    const char *mykey3 = "mouse";
    int *myitem5 = malloc(sizeof(int));
    *myitem5 = 4;
    hashtable_insert(ht, mykey3, myitem5);
    printf("Added key 'mouse'\n");
    int *myitem6 = hashtable_find(ht, mykey3);
    printf("Item should be '4'\n");
    printf("Item for key 'mouse': %d\n", *myitem6);
    printf("-------------------\n");

    // add key "dog" again   
    bool mybool = hashtable_insert(ht, mykey, myitem);
    printf("Tried adding key 'dog' again\n");
    printf("hashtable_insert should return false\n");
    printf("Return value of hashtable_insert:  %d\n", mybool);
    printf("-------------------\n");

    // none of these should be added to the hashtable
    printf("test with null hashtable, good key...\n");
    hashtable_insert(NULL, "horses", NULL);
    printf("test with good hashtable, null key...\n");
    hashtable_insert(ht, NULL, NULL); 
    printf("test with null hashtable, null key...\n");
    hashtable_insert(NULL, NULL, NULL);
    printf("-------------------\n");

    // count number of keys
    int key_count = 0;
    hashtable_iterate(ht, &key_count, itemcount);
    printf("Number of keys should be three\n");
    printf("Number of keys: %d\n", key_count);
    printf("-------------------\n");
    
    // print all key/item pairs
    printf("The hashtable:\n");
    hashtable_print(ht, stdout, printint);
    printf("-------------------\n");

    // delete the set
    printf("delete the set...\n");
    hashtable_delete(ht, intdelete);
   
    return 0;
}

/*********** itemcount() ****************/
/* count the number of keys in a hashtable */
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
    const char *mykey = key;
    int *myint = item;
    fprintf(fp, "(%s, %d)", mykey, *myint);
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

