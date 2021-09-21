# set

A `set` maintains an unordered collection of _(key,item)_ pairs; any given _key_ can only occur in the set once. It starts out empty and grows as the caller inserts new _(key,item)_ pairs. The caller can retrieve items by asking for their _key_, but cannot remove or update pairs. Items are distinguished by their _key_.

### Usage

The *set* module, defined in `set.h` and implemented in `set.c` exports the following functions:

```c
set_t *set_new(void);
bool set_insert(set_t *bag, const char *key, void *item);
void *set_find(set_t *set, const char *key);
void set_print(set_t *set, FILE *fp, 
	       void (*itemprint)(FILE *fp, const char *key, void *item));
void set_iterate(set_t *set, void *set, void (*itemfunc)(void *arg, const char *key void *item) );
void set_delete(set_t *set, void (*itemdelete)(void *item) );
```

### Implementation

We implement this set as a linked list.
The *set* itself is represented as a `struct set` containing a pointer to the head of the list; the head pointer is NULL when the set is empty.

Each node in the list is a `struct setnode`, a type defined internally to the module.
Each setnode includes a `const char *key`, a pointer to the `void *item`, and a pointer to the next setnode on the list.

To insert a new item in the set we create a new setnode to hold the `item`, and insert it at the head of the list.

The `set_print` method prints a little syntax around the list, and between items, but mostly calls the `itemprint` function on each item by scanning the linked list.

The `set_iterate` method calls the `itemfunc` function on each item by scanning the linked list.

The `set_delete` method calls the `itemdelete` function on each item by scanning the linked list, freeing setnodes and their keys as it proceeds.
It concludes by freeing the `struct set`.

### Assumptions

No assumptions beyond those that are clear from the spec.

The `item` inserted cannot be NULL.

### Files

* `Makefile` - compilation procedure
* `set.h` - the interface
* `set.c` - the implementation
* `settest.c` - unit test driver
* `testing.out` - result of `make test &> testing.out`

### Compilation

To compile, simply `make`.

### Testing

The `settest.c` program creates a set and some key/item pairs and tests a few error and edge cases.

See `testing.out` for details of testing and an example test run.

Try testing with `MEMTEST` by editing Makefile to turn on that flag and then `make test`.

To test with valgrind, `make valgrind`.
