# counters

A counter set is a set of counters, each distinguished by an integer _key_. It’s a set - each key can only occur once in the set - and it tracks a _counter_ for each _key_. It starts empty. Each time `counters_add` is called on a given _key_, the corresponding _counter_ is incremented. The current _counter_ value can be retrieved by asking for the relevant _key_.

### Usage

The *counters* module, defined in `counters.h` and implemented in `counters.c`, implements a set of `const char' keys, and exports the following functions:

```
counters_t *counters_new(void); 
int counters_add(counters_t *ctrs, const int key);
int counts_get(counters_t *ctrs, const int key);
bool counters_set(counters_t *ctrs, const int key, const int count);
void counts_print(counters_t *ctrs, FILE *fp);
void counters_iterate(counters_t *ctrs, void *arg, void (*itemfunc)(void *arg, const int key, const in count));
void counters_delete(counters_t *ctrs);
```

### Implementation

We implement this counter as a linked list.
The *counter* itself is represented as a `struct counters` containing a pointer to the head of the list; the head pointer is NULL when the counter is empty.

Each node in the list is a `struct countersnode`, a type defined internally to the module.
Each counters node includes a `const int key`, `const int count`, and pointer to the next countersnode in the list.

To insert a new key in the counter we create a new countersnode to hold the `key`, and insert it at the head of the list.
```
The `counters_t` method returns the count of a key.

THe `counters_set` method sets the count of a key.

The `counters_print` method prints the list of counters.

The `counters_iterate` method calls the `itemfunc` function on each key by scanning the linked list.

The `counters_delete` method frees each countersnode, concluding by freeing the counter itself.
```
### Assumptions

No assumptions beyond those that are clear from the spec.

The _key_ inserted cannot be negative, and a return of 0 from `counters_add` indicates a negative _key_ or NULL _counters_t_.


### Files

* `Makefile` - compilation procedure
* `counters.h` - the interface
* `counters.c` - the implementation
* `counterstest.c` - unit test driver
* `testing.out` - result of `make test &> testing.out`

### Compilation

To compile, simply `make`.

### Testing

The `counterstest.c` program creates a counter and adds a few countersnodes to it.
It tests a few error and edge cases.

To test, simply `make test`.
See `testing.out` for details of testing and an example test run.

Try testing with `MEMTEST` by editing Makefile to turn on that flag and then `make test`.

To test with valgrind, `make valgrind`.
