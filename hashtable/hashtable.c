/* 
 * hashtable.c - 'hashtable' module
 *
 * see hashtable.h for more information.
 *
 * Annabel Revers, January 2020
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include </thayerfs/home/f003m1k/cs50-dev/lab3-annierevers/set/set.h>
#include "jhash.h"

/**************** file-local global variables ****************/
/* none */

/**************** global types ****************/
typedef struct hashtable {
    set_t **myarray;                // array of pointers to sets
    int slots;                // length of myarray
} hashtable_t;

/**************** global functions ******i**********/
/* that is, visible outside this file */
/* see hashtable.h for comments about exported functions */

/**************** local functions ****************/
/* not visible outside this file */
static bool key_exists(hashtable_t *ht, const char *key);

/**************** hashtable_new() ****************/
/* see hashtable.h for description */
hashtable_t *
hashtable_new(const int num_slots)
{
    hashtable_t *hashtable  = malloc(sizeof(hashtable_t));
    if (hashtable == NULL) {
        return NULL;              // error allocating hashtable
    } else {
      // initialize array of pointers to sets
      hashtable->myarray = calloc(num_slots, sizeof(set_t *));
      hashtable->slots = num_slots;
      return hashtable;
    }
}

/**************** hashtable_insert() ****************/
/* see hashtable.h for description */
bool
hashtable_insert(hashtable_t *ht, const char *key, void *item)
{
    if (ht != NULL && item != NULL && key != NULL) {
         if (key_exists(ht, key)) {
             return false;
         }
         // get index for key
         int index = JenkinsHash(key, ht->slots);
         // check if there is already a set at this index
         set_t *myset = (ht->myarray)[index];
         if (myset == NULL) {
             // allocate a new set to be added to the array
             set_t *new = set_new();
             if (new != NULL) {
                 // add key and item 
                 set_insert(new, key, item);
                 // add set to array
                 (ht->myarray)[index] = new;
                  return true;              // successful insert
              } else {
                  return false;             // error creating set
              }
         } else {
            // add key and item to existing set
            set_insert(myset, key, item);
            return true;                    // successful insert
         }
    
     } else {
         return false;                      // some parameter NULL
     }
}

/**************** key_exists **************/
/* check if key exists */
bool
key_exists(hashtable_t *ht, const char *key)
{
    for (int i = 0; i < ht->slots; i++) {
        // get the set at index i
        set_t *myset = (ht->myarray)[i];
        void *item = set_find(myset, key);
        if (item != NULL) {
            return true;
        }
    }
    return false;
}


/**************** hashtable_find() ****************/
/* see hashtable.h for description */
void *
hashtable_find(hashtable_t *ht, const char *key)
{
    if (ht == NULL || key == NULL) {
        return NULL;                    // bad hashtable or key
    } else {
        // get index for key
        int index = JenkinsHash(key, ht->slots);
        set_t *myset = (ht->myarray)[index];
        if (myset == NULL) {
             return NULL;               // no set exists at this index
        } else {
             void *item = set_find(myset, key);
             if (item == NULL) {
                 return NULL;           // key does not exist
             } else {
                 return item;           // key exists
             }
        }
    }
}

/**************** hash_print() ****************/
/* see hashtable.h for description */
void
hashtable_print(hashtable_t *ht, FILE *fp, 
        void (*itemprint)(FILE *fp, const char *key, void *item) )
{
    if (fp != NULL) {
        if (ht != NULL) {
            for (int i = 0; i < (ht->slots); i++) {
                // get the set at the index
                set_t *myset = (ht->myarray)[i];
                if (myset != NULL) {
                    set_print(myset, fp, itemprint);
                } 
                fputc('\n', fp);
             }
          } else {
              fputs("(null)", fp);
          }
    }
}

/**************** hashtable_iterate() ****************/
/* see hashtable.h for description */
void
hashtable_iterate(hashtable_t *ht, void *arg,
        void (*itemfunc)(void *arg, const char *key, void *item) )
{
    if (ht != NULL && itemfunc != NULL) {
        // loop through hashtable array
        for (int i = 0; i < (ht->slots); i++) {
            // get set at index i
            set_t *myset = (ht->myarray)[i];
            // iterature through set
            set_iterate(myset, arg, itemfunc);
        }
    }
}

/**************** hashtable_delete() ****************/
/* see hashtable.h for description */
void 
hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item) )
{
    if (ht != NULL) {
        // loop through hashtable array
        for (int i = 0; i < (ht->slots); i++) {
             set_t *myset = (ht->myarray)[i];  // get the set at index i
             set_delete(myset, itemdelete);              // free the set
        }
        // free the array
        free(ht->myarray);
        // free the hashtable
        free(ht);
    }
}


