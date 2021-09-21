# hashtable

A *hashtable* is a set of _(key,item)_ pairs. It acts just like a set, but is far more efficient for large collections. It implements an array of pointers to sets.

### Usage

The *hashtable* module, defined in `hashtable.h` and implemented in `hashtable.c`, exports the following functions:

```c
hashtable_t *hashtable_new(const int num_slots);
bool hashtable_insert(hashtable_t *ht, const char *key, void *item);
void *hashtable_find(hashtbale_t *ht);
void hashtable_print(hashtable_t *ht, FILE *fp, 
	       void (*itemprint)(FILE *fp, const char *key, void *item));
void hashtable_iterate(hashtable_t *ht, void *arg, void (*itemfunc)(void *arg,const char *key, void *item) );
void hashtable_delete(hasbtable_t *ht, void (*itemdelete)(void *item) );
```

### Implementation

We implement this bag as an array of pointers to sets.
The *hashtable* itself is represented as a `struct hashtable` containing an array of pointers to sets.

To insert a new item in the hashtable we map the item to a slot in the array with out `JenkinsHash` hash function then add it to the set at that index.

The `hashnode_print` method prints a little syntax around the list, and between items, but mostly calls the `itemprint` function on each item by scanning the sets.

The `hashtable_iterate` method calls the `itemfunc` function on each item by scanning the sets.

The `hashtable_delete` method calls the `itemdelete` function on each item by scanning the array and freeing the sets as it proceeds.
It concludes by freeing the `struct hashtable`.

### Assumptions

No assumptions beyond those that are clear from the spec.

### Files

* `Makefile` - compilation procedure
* `hashtable.h` - the interface
* `hashtable.c` - the implementation
* `hashtabletest.c` - unit test driver
* `testing.out` - result of `make test &> testing.out`

### Compilation

To compile, simply `make`.

### Testing

The `hashtabletest.c` program makes a hashtable and does a few insertions. It tests a few error and edge cases.

See `testing.out` for details of testing and an example test run.

Try testing with `MEMTEST` by editing Makefile to turn on that flag and then `make test`.

To test with valgrind, `make valgrind`.
