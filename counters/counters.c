/*
 * counters.c - 'counters' module
 *
 * see counters.h for more information.
 *
 * Annabel Revers, February 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "counters.h"

/************** file-local global variables **************/
/* none */

/************** local types **************/ 
typedef struct countersnode {
    int key;                        // pointer to key
    int count;                      // pointer to count
    struct countersnode *next;      // pointer to next node
} countersnode_t;

/************** global types **************/ 
typedef struct counters {
    struct countersnode *head;      // head of linked list
} counters_t;

/************** global functions **************/ 
/* see counter.h for comments about exported functions */

/************** local functions **************/ 
/* not visible outside this file */
static countersnode_t *countersnode_new(const int key);
static countersnode_t *match_key(counters_t *ctrs, const int key);

/************** counters_new() **************/ 
/* see counters.h for description */
counters_t *
counters_new(void)
{
    // create new empty counter structure 
    counters_t *counter = malloc(sizeof(counters_t)); 
    
    if (counter == NULL) {
        return NULL;                // error allocating memory
    } else {
        counter->head = NULL;       // head points to nothing
        return counter;
    }
}

/************** counters_add() **************/ 
/* see counters.h for description */
int
counters_add(counters_t *ctrs, const int key)
{
    if (ctrs == NULL || key < 0) {
        return 0;                   // error
    } else {
        // get node matching key
        countersnode_t *node = match_key(ctrs, key);
        if (node == NULL) {         // node does not yet exist
            // allocate a new node
            countersnode_t *new = countersnode_new(key);
            if (new != NULL) {
                // add to the head of the linked list
                new->next = ctrs->head;
                ctrs->head = new;
                return new->count;
            }
            else {
                return 0;           // error
            }
        } else {                    // node already exists
            // increment its count
            (node->count)++;
            return node->count;
        }
    }
}

/************** countersnode_new() **************/ 
/* Allocate and initialize a countersnode */
static countersnode_t *
countersnode_new(const int key)
{
    // create new countersnode
    countersnode_t *node = malloc(sizeof(countersnode_t));

    if (node == NULL) {             // error
        return NULL;
    } else {
        node->key = key;   
        node->count = 1;            
        return node;
    }
}

/************** match_key() **************/ 
/* return the countersnode assciated with a given key */
static countersnode_t *
match_key(counters_t *ctrs, const int key)
{
    for (countersnode_t *node = ctrs->head; node != NULL; node = node->next) {
        if ((node->key) == key) {
            return node;
        }
    }

    return NULL;                    // key does not yet exist; node not found
    
}

/************** counters_get() **************/ 
/* see counters.h for description */
int
counters_get(counters_t *ctrs, const int key)
{
    if (ctrs == NULL) {
        return 0;                   // bad counter
    }
   
    // get node matching key
    countersnode_t *node = match_key(ctrs, key);

    if (node == NULL) {             // key not found
        return 0;
    } else {
        return node->count;
    }
 }
        
/************** counters_set() *************/
/* see counters.h for description */
bool
counters_set(counters_t *ctrs, const int key, const int count)
{
    if (ctrs == NULL || key < 0 || count < 0) {
        return false;
    } else {
        // get node matching key
        countersnode_t *node = match_key(ctrs, key);

        if (node == NULL) {          // node does not yet exist
            // create new countersnode
            countersnode_t *new = countersnode_new(key);
            if (new != NULL) {
                // add to the head of the linked list
                new->next = ctrs->head;
                ctrs->head = new;
                new->count = count;  // set the new node's count to the parameter count
                return true;
            } else {
                return false;        // error
            }      
        } else {                     // node already exists
            node->count = count;     // set its count to the parameter count
            return true;
        }

    }
}

/************** counters_print() *****************/
/* see counters.h for description */
void
counters_print(counters_t *ctrs, FILE *fp)
{
    if (fp != NULL) {                  
        if (ctrs != NULL) {
            // iterature through nodes and print key/count pair
            fputc('{', fp);
            for (countersnode_t *node = ctrs->head; node != NULL; node = node->next) {
                fprintf(fp, "%d = %d", node->key, node->count);
                fputc(',', fp);
            }
            fputc('}', fp);
            fputc('\n', fp);
        } else {
            fputs("(null)", fp);
        }
    } 
}

/************* counters_iterate() ****************/
/* see counters.h for description */
void
counters_iterate(counters_t *ctrs, void *arg, 
        void (*itemfunc)(void *arg, const int key, const int count))
{
    if (ctrs != NULL && itemfunc != NULL) {
        // call itemfunc on each node
        for (countersnode_t *node = ctrs->head; node!= NULL; node = node->next) {
            (*itemfunc)(arg, node->key, node->count);
        }
    }
}


/************** counters_delete() **************/
/* see counters.h for description */
void
counters_delete(counters_t *ctrs)
{
     if (ctrs != NULL) {
        for (countersnode_t *node = ctrs->head; node != NULL; ) {
            countersnode_t *next = node->next;      // remember what comes next
            free(node);                             // free the node
            node = next;
            
        }
        free(ctrs);
     }
}


