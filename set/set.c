/* 
 * set.c - 'set' module
 *
 * see set.h for more information.
 *
 * Annabel Revers, January 2020
 * */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "set.h"
#include "string.h"

/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
typedef struct setnode {
    char *key;              // pointer to key
    void *item;                   // pointer to data
    struct setnode *next;         // link to next node
} setnode_t;

/**************** global types ****************/
typedef struct set {
    struct setnode *head;         // head of the list of items in set
} set_t;

/**************** global functions ****************/
/* that is, visible outside this file */
/* see set.h for comments about exported functions */

/**************** local functions ****************/
/* not visible outside this file */
static setnode_t * setnode_new(const char *key, void *item);
static setnode_t * key_match(set_t *set, const char *key);


/**************** set_new() ****************/
/* see set.h for description */
set_t *
set_new(void)
{
    // create new empty set
    set_t *set = malloc(sizeof(set_t));
    
    if (set == NULL) {
        return NULL;            // error 
    } else {
        set->head = NULL;
        return set;
    }
}
  
/**************** set_insert() ****************/
/* see set.h for description */
bool
set_insert(set_t *set, const char *key, void *item)
{
    if (set != NULL && key!= NULL && item != NULL) {
        // check if key exists
        setnode_t *node = key_match(set, key);
        if (node != NULL) {
            return false;               // key already exists
        } else {
            // allocate a new setnode 
             setnode_t *new = setnode_new(key, item);
             if (new != NULL) {
                 // add it to the head of the list
                 new->next = set->head;
                 set->head = new;
                 return true;           // new node successfully inserted
             } else {
                 return false;          // out of memory
             }
        }
    } else {
        return false;                   // some parameter is NULL
    }
}

/**************** setnode_new() ****************/
/* Allocate and initialize a bagnode */
static setnode_t * 
setnode_new(const char *key, void *item)
{
    // create new setnode
    setnode_t *node = malloc(sizeof(setnode_t));

    if (node == NULL) {
        return NULL;                    // return error
    } else {
        // allocate space for copy of key string
        node->key = malloc(strlen(key)+1);
        if (node->key == NULL) {
            // error allocating memory for key
            free(node);                 // cleanup
            return NULL;                // return error
        } else {
            strcpy(node->key, key);
            node->item = item;
            node->next = NULL;
            return node;
        }
    }
}

/**************** key_match() ****************/
/* Check if key exists */
static setnode_t *
key_match(set_t *set, const char *key)
{
    for (setnode_t *node = set->head; node != NULL; node = node->next) {
       
        int match = strcmp((node->key), key);
        if (match == 0) {
            return node;              // key exists
        }
    }
    return NULL;                      // key does not yet exist
}
    
/**************** set_find() ****************/
/* see set.h for description */
void *
set_find(set_t *set, const char *key)
{
    if (set == NULL || key == NULL) {
        return NULL;                     // bad set
    } else {
        setnode_t *node = key_match(set, key);
        if (node == NULL) {
            return NULL;                 // key not found
        } else {
            return node->item;           // key successfully found
        }
    }
}

/**************** set_print() ****************/
/* see set.h for description */
void
set_print(set_t *set, FILE *fp, 
        void (*itemprint)(FILE *fp, const char *key, void *item) )
{
    if (fp != NULL) {
        if (set != NULL) {
            if (itemprint != NULL) {
                // print comma-separated list of items 
                fputc('{', fp);
                for (setnode_t *node = set->head; node != NULL; 
                        node = node->next) { 
                    (*itemprint)(fp, node->key, node->item);
                    fputc(',', fp);
                }
                fputc('}', fp);
                fputc('\n', fp);
            } else {
                fputs("{}", fp);            // NULL itemprint
            }
        } else {
            fputs("(null)", fp);            // NULL set
        }
     }
}

/**************** set_iterate() ****************/
/* see set.h for description */
void
set_iterate(set_t *set, void *arg, 
        void (*itemfunc)(void *arg, const char*key, void *item) )
{
    if (set != NULL && itemfunc != NULL) {
        // call itemfunc on each item
        for (setnode_t *node = set->head; node != NULL; node = node->next) {
            (*itemfunc)(arg, node->key, node->item); 
        }
    }
}

/**************** set_delete() ****************/
/* see set.h for description */
void 
set_delete(set_t *set, void (*itemdelete)(void *item) )
{
    if (set != NULL) {
        for (setnode_t *node = set->head; node != NULL; ) {
            if (itemdelete != NULL) {           // if possible...
                (*itemdelete)(node->item);      // free node's item
            }
            setnode_t *next = node->next;       // remember what comes next
            free(node->key);                    // free key
            free(node);                         // free the node
            node = next;                        // move on to next node
        }
        free(set);                              // free the set itself
    }
} 

