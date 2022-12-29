# Global Namespace



## Records

* [](.md)
* [hashset](hashset.md)
* [hashmap](hashmap.md)
* [set](set.md)
* [](.md)
* [linkedlist](linkedlist.md)
* [list](list.md)
* [linkednode](linkednode.md)
* [stack](stack.md)
* [arraylist](arraylist.md)
* [](.md)
* [logger](logger.md)
* [marker](marker.md)
* [queue](queue.md)
* [](.md)
* [buffer](buffer.md)
* [hashmap_bucket](hashmap_bucket.md)


## Functions

### hashset_new

*hashset_t * hashset_new(hashfunction_t func)*

*Defined at src/hashset.c#51*

### hashset_new_prealloc

*hashset_t * hashset_new_prealloc(size_t initial_cap, hashfunction_t func)*

*Defined at src/hashset.c#40*

### hashset_size

*size_t hashset_size(const hashset_t * set)*

*Defined at src/hashset.c#62*

### hashset_add

*int hashset_add(hashset_t * set, void * item, size_t size)*

*Defined at src/hashset.c#71*

### hashset_clear

*int hashset_clear(hashset_t * set)*

*Defined at src/hashset.c#80*

### hashset_remove

*_Bool hashset_remove(hashset_t * set, void * item, size_t size)*

*Defined at src/hashset.c#89*

### hashset_foreach

*int hashset_foreach(const hashset_t * set, void (*)(void *, size_t, void *) cb, void * pipe)*

*Defined at src/hashset.c#100*

### hashset_contains

*_Bool hashset_contains(const hashset_t * set, const void * item, size_t size)*

*Defined at src/hashset.c#113*

### hashset_destroy

*void hashset_destroy(hashset_t * set)*

*Defined at src/hashset.c#122*

### hashmap_new

*hashmap_t * hashmap_new(hashfunction_t hasher)*

*Defined at src/hashmap.c#110*

### hashmap_new_prealloc

*hashmap_t * hashmap_new_prealloc(hashfunction_t hasher, size_t initial_cap)*

*Defined at src/hashmap.c#114*

### hashmap_put

*int hashmap_put(hashmap_t * map, void * key, size_t keysize, void * value)*

*Defined at src/hashmap.c#135*

### hashmap_get

*void * hashmap_get(const hashmap_t * map, const void * key, size_t keysize)*

*Defined at src/hashmap.c#158*

### hashmap_size

*size_t hashmap_size(const hashmap_t * map)*

*Defined at src/hashmap.c#172*

### hashmap_contains_key

*_Bool hashmap_contains_key(const hashmap_t * map, const void * key, size_t keysize)*

*Defined at src/hashmap.c#181*

### hashmap_foreach

*int hashmap_foreach(const hashmap_t * map, void (*)(void *, size_t, void *, void *) cb, void * pipe)*

*Defined at src/hashmap.c#191*

### hashmap_clear

*int hashmap_clear(hashmap_t * map)*

*Defined at src/hashmap.c#208*

### hashmap_remove

*void * hashmap_remove(hashmap_t * map, void * key, size_t keysize)*

*Defined at src/hashmap.c#227*

### hashmap_destroy

*void hashmap_destroy(hashmap_t * map)*

*Defined at src/hashmap.c#247*

### hashset_alloc_struct

*hashset_t * hashset_alloc_struct()*

*Defined at src/hashset.c#16*

### cb_helper

*void cb_helper(void * key, size_t keylen, void * val, void * pipe)*

*Defined at src/hashset.c#34*

### linkedlist_new

*linkedlist_t * linkedlist_new()*

*Defined at src/linkedlist.c#99*

 Creates a new linked list.



**return** The new linked list, or NULL on error.

### linkedlist_length

*size_t linkedlist_length(linkedlist_t * list)*

*Defined at src/linkedlist.c#116*

 Returns the length of the linked list.



**list**

**return** Length of the list

### linkedlist_add

*int linkedlist_add(linkedlist_t * list, void * element)*

*Defined at src/linkedlist.c#125*

 Adds an element to the linked list.



**list**

**element**

**return** 0 on success, a negative value on error.

### linkedlist_addall

*int linkedlist_addall(linkedlist_t * list, void ** elements, size_t nitems)*

*Defined at src/linkedlist.c#133*

 Adds an array of elements to the linked list.



**list**

**elements**

**nitems**

**return** 0 on success, a negative value on error.

### linkedlist_insert

*int linkedlist_insert(linkedlist_t * list, void * element, size_t index)*

*Defined at src/linkedlist.c#148*

 Inserts an element at index to the linked list.



**list**

**element**

**index**

**return** 0 on success, a negative value on error.

### linkedlist_insertall

*int linkedlist_insertall(linkedlist_t * list, void ** elements, size_t nitems, size_t index)*

*Defined at src/linkedlist.c#162*

 Inserts an array of elements at index to the linked list.



**list**

**elements**

**nitems**

**index**

**return** 0 on success, a negative value on error.

### linkedlist_get

*void * linkedlist_get(linkedlist_t * list, size_t index)*

*Defined at src/linkedlist.c#180*

 Get the element at specified index.



**list**

**index**

**return** The item, or NULL on error.

### linkedlist_remove

*void * linkedlist_remove(linkedlist_t * list, size_t index)*

*Defined at src/linkedlist.c#194*

 Removes an element at index, and returns it.



**list**

**index**

**return** The removed element, or NULL on error.

### linkedlist_foreach

*int linkedlist_foreach(linkedlist_t * list, void (*)(void *, void *) cb, void * pipe)*

*Defined at src/linkedlist.c#224*

 Executes a function for each element in the list.



**list**

**cb**

**pipe**

**return** 0 on success, a negative value on error.

### linkedlist_to_array

*void ** linkedlist_to_array(linkedlist_t * list)*

*Defined at src/linkedlist.c#237*

 Returns an array with a copy of the list's elements.



**list**

**return** The generated array, or NULL on error.

### linkedlist_clear

*int linkedlist_clear(linkedlist_t * list)*

*Defined at src/linkedlist.c#256*

 Clears the linked list.



**list**

**return** 0 on success, a negative value on error.

### linkedlist_destroy

*void linkedlist_destroy(linkedlist_t * list)*

*Defined at src/linkedlist.c#275*

  Destroys the linked list.

  IMPORTANT: Stored elements are not deallocated!



**list**

### __linkedlist_add

*int __linkedlist_add(linkedlist_t * list, void * element)*

*Defined at src/linkedlist.c#24*

### __linkedlist_get

*linkednode * __linkedlist_get(linkedlist_t * list, size_t index)*

*Defined at src/linkedlist.c#48*

### __linkedlist_insert

*int __linkedlist_insert(linkedlist_t * list, void * element, size_t index)*

*Defined at src/linkedlist.c#66*

### stack_new_capped

*stack_t * stack_new_capped(size_t max_len)*

*Defined at src/stack.c#16*

 Creates a new stack, which can hold a maximum of max_len items. Push operations will return -2, if capacity is exhausted.



**return** A new stack with max_len capacity.

### stack_new_uncapped

*stack_t * stack_new_uncapped()*

*Defined at src/stack.c#39*

 Creates a new queue, which can theoretically grow to infinity.



**return** A new uncapped queue.

### stack_push

*int stack_push(stack_t * s, void * item)*

*Defined at src/stack.c#57*

 Pushes an item onto the stack.



**s**

**item**

**return** 0 on success, -2 when capacity is exhausted, or another negative number on error.

### stack_peek

*void * stack_peek(stack_t * s)*

*Defined at src/stack.c#76*

 Get the next element from the stack without removing it.



**s**

**return** The next element, or NULL if empty.

### stack_pop

*void * stack_pop(stack_t * s)*

*Defined at src/stack.c#90*

 Pop the next element from the stack.



**s**

**return** The next element, or NULL if empty.

### stack_size

*size_t stack_size(stack_t * s)*

*Defined at src/stack.c#103*

 Get the current size of the stack



**s**

**return** The size of the stack.

### stack_clear

*int stack_clear(stack_t * s)*

*Defined at src/stack.c#114*

 Deletes all elements from the stack.

 IMPORTANT: Stored elements are not deallocated.



**s**

### stack_destroy

*void stack_destroy(stack_t * s)*

*Defined at src/stack.c#127*

 Destroys the stack.

 IMPORTANT: Stored elements are not deallocated.



**s**

### push_NULL

*void push_NULL()*

*Defined at test/stack_test.c#12*

### uncapped_non_NULL

*void uncapped_non_NULL()*

*Defined at test/stack_test.c#19*

### uncapped_check_empty_size

*void uncapped_check_empty_size()*

*Defined at test/stack_test.c#24*

### uncapped_push

*void uncapped_push()*

*Defined at test/stack_test.c#29*

### uncapped_check_size

*void uncapped_check_size()*

*Defined at test/stack_test.c#37*

### uncapped_pop

*void uncapped_pop()*

*Defined at test/stack_test.c#42*

### uncapped_clear

*void uncapped_clear()*

*Defined at test/stack_test.c#51*

### capped_non_NULL

*void capped_non_NULL()*

*Defined at test/stack_test.c#60*

### capped_check_empty_size

*void capped_check_empty_size()*

*Defined at test/stack_test.c#65*

### capped_push

*void capped_push()*

*Defined at test/stack_test.c#70*

### capped_check_size

*void capped_check_size()*

*Defined at test/stack_test.c#78*

### capped_check_full

*void capped_check_full()*

*Defined at test/stack_test.c#83*

### capped_pop

*void capped_pop()*

*Defined at test/stack_test.c#88*

### capped_clear

*void capped_clear()*

*Defined at test/stack_test.c#97*

### main

*int main()*

*Defined at test/stack_test.c#106*

### arraylist_new

*arraylist_t * arraylist_new()*

*Defined at src/arraylist.c#52*

 Creates a new arraylist.



**return** The new arraylist, or NULL if an error occured.

### arraylist_add

*int arraylist_add(arraylist_t * list, void * item)*

*Defined at src/arraylist.c#56*

 Adds the given element at the end of the arraylist.



**list**

**item**

**return** 0 if successful, else a negative value.

### arraylist_addall

*int arraylist_addall(arraylist_t * list, void ** items, size_t nitems)*

*Defined at src/arraylist.c#60*

 Adds the given array to the end of the arraylist.



**list**

**items**

**nitems**

**return** 0 if successful, else a negative value.

### arraylist_insert

*int arraylist_insert(arraylist_t * list, void * item, size_t index)*

*Defined at src/arraylist.c#77*

 Inserts the given element at index into the arraylist.



**list**

**item**

**index**

**return** 0 if successful, else a negative value.

### arraylist_insertall

*int arraylist_insertall(arraylist_t * list, void ** items, size_t nitems, size_t index)*

*Defined at src/arraylist.c#81*

 Inserts the given array at index into the arraylist.



**list**

**items**

**nitems**

**index**

**return** 0 if successful, else a negative value.

### arraylist_get

*void * arraylist_get(const arraylist_t * list, size_t index)*

*Defined at src/arraylist.c#106*

 Gets the element at the given index.



**list**

**index**

**return** The element at index, or NULL if an error occured.

### arraylist_length

*size_t arraylist_length(const arraylist_t * list)*

*Defined at src/arraylist.c#120*

 Gets the length (element count) of the arraylist.



**list**

**return** The length.

### arraylist_remove

*void * arraylist_remove(arraylist_t * list, size_t index)*

*Defined at src/arraylist.c#129*

 Removes the element at given index from the arraylist and returns it.



**list**

**index**

**return** The element at index, or NULL if an error occured.

### arraylist_foreach

*int arraylist_foreach(arraylist_t * list, void (*)(void *, void *) cb, void * pipe)*

*Defined at src/arraylist.c#148*

 Calls cb with every element in the given arraylist.



**list**

**cb**

**pipe**

**return** 0 if successful, else a negative value.

### arraylist_to_array

*void ** arraylist_to_array(arraylist_t * list)*

*Defined at src/arraylist.c#160*

 Returns an array with a copy of to lists elements.



**list**

**return** The generated array, or NULL on error.

### arraylist_clear

*int arraylist_clear(arraylist_t * list)*

*Defined at src/arraylist.c#175*

 Empties the given arraylist. Stored elements are not deallocated.



**list**

**return** 0 if successful, else a negative value.

### arraylist_destroy

*void arraylist_destroy(arraylist_t * list)*

*Defined at src/arraylist.c#189*

 Destroyes the given arraylist.

 IMPORTANT: Stored elements are not deallocated.



**list**

### cb_function

*void cb_function(void * ptr, void * pipe)*

*Defined at test/arraylist_test.c#13*

### add_NULL

*void add_NULL()*

*Defined at test/arraylist_test.c#19*

### addall_NULL

*void addall_NULL()*

*Defined at test/arraylist_test.c#21*

### new_non_NULL

*void new_non_NULL()*

*Defined at test/arraylist_test.c#25*

### empty_after_creation

*void empty_after_creation()*

*Defined at test/arraylist_test.c#30*

### add_0

*void add_0()*

*Defined at test/arraylist_test.c#35*

### add_1

*void add_1()*

*Defined at test/arraylist_test.c#40*

### add_2

*void add_2()*

*Defined at test/arraylist_test.c#45*

### check_after_add

*void check_after_add()*

*Defined at test/arraylist_test.c#50*

### add_3

*void add_3()*

*Defined at test/arraylist_test.c#55*

### addall

*void addall()*

*Defined at test/arraylist_test.c#60*

### confirm_length

*void confirm_length()*

*Defined at test/arraylist_test.c#65*

### to_array_not_NULL

*void to_array_not_NULL()*

*Defined at test/arraylist_test.c#69*

### to_array_equal

*void to_array_equal()*

*Defined at test/arraylist_test.c#74*

### foreach_0

*void foreach_0()*

*Defined at test/arraylist_test.c#79*

### remove_5

*void remove_5()*

*Defined at test/arraylist_test.c#84*

### remove_0

*void remove_0()*

*Defined at test/arraylist_test.c#89*

### foreach_1

*void foreach_1()*

*Defined at test/arraylist_test.c#94*

### insert

*void insert()*

*Defined at test/arraylist_test.c#100*

### foreach_2

*void foreach_2()*

*Defined at test/arraylist_test.c#105*

### clear

*void clear()*

*Defined at test/arraylist_test.c#111*

### empty_after_clear

*void empty_after_clear()*

*Defined at test/arraylist_test.c#116*

### spawn

*pid_t spawn(process * proc, const char * file, char *const * argv, char *const * envp)*

*Defined at src/util.c#11*

 Spawns a new child process with the given arguments and environment, and stdin, stdout and stderr redirected into pipes for communication.



**proc**

**file**

**argv**

**envp**

**return** The child's PID, or a negative value if an error occured.



**see** execve

### memrev

*void * memrev(void * arr, size_t nitems, size_t size)*

*Defined at src/util.c#64*

 Reverses the order of elements in memory.



**arr**

**nitems**

**size**

**return** a pointer to arr, or NULL if an error occured.

### setsignal

*int setsignal(int signum, sighandler_t handler)*

*Defined at src/util.c#89*

 Changes the signal handler for the specified signal to the given handler.



**signum**

**handler**

**return** 0 on success, a negative value on error.

### memrev_test

*void memrev_test()*

*Defined at test/util_test.c#15*

### spawn_test

*void spawn_test()*

*Defined at test/util_test.c#22*

### logger_new

*logger_t * logger_new(FILE * info, FILE * error, _Bool _syslog)*

*Defined at src/logger.c#41*

 Creates a new logger with given streams for writting output to.

 If both info and error are not NULL, info is used for output below WARNING and error for output from and above WARNING.

 If info is not NULL and error is NULL, or vice versa, the one stream is used for all output.

 If both info and error are NULL, info is set to stdout and error to stderr.



**info**

**error**

**_syslog**

### logger_do_trace

*_Bool logger_do_trace(logger_t * log)*

*Defined at src/logger.c#66*

### logger_do_debug

*_Bool logger_do_debug(logger_t * log)*

*Defined at src/logger.c#68*

### logger_do_info

*_Bool logger_do_info(logger_t * log)*

*Defined at src/logger.c#70*

### logger_do_notice

*_Bool logger_do_notice(logger_t * log)*

*Defined at src/logger.c#72*

### logger_do_warning

*_Bool logger_do_warning(logger_t * log)*

*Defined at src/logger.c#74*

### logger_do_error

*_Bool logger_do_error(logger_t * log)*

*Defined at src/logger.c#76*

### logger_do_fatal

*_Bool logger_do_fatal(logger_t * log)*

*Defined at src/logger.c#78*

### logger_printf

*int logger_printf(logger_t * log, loglevel lvl, marker * m, const char * format)*

*Defined at src/logger.c#80*

### logger_print

*int logger_print(logger_t * log, loglevel lvl, marker * m, const char * msg)*

*Defined at src/logger.c#111*

### logger_destroy

*void logger_destroy(logger_t * log)*

*Defined at src/logger.c#117*

 Destroys the given logger instance.

 IMPORTANT: Used streams are NOT closed BUT flushed.

### marker_new

*marker * marker_new(const char * name)*

*Defined at src/logger.c#130*

 Creates a new marker with the given name.



**name**

**return** The new marker or NULL on error.

### marker_destroy

*void marker_destroy(marker * m)*

*Defined at src/logger.c#140*

 Destroys the given marker.



**m**

### debug

*void debug(const char * buf)*

*Defined at test/logger_test.c#15*

### clear

*void clear()*

*Defined at test/logger_test.c#22*

### flush

*void flush()*

*Defined at test/logger_test.c#30*

### con

*void con()*

*Defined at test/logger_test.c#35*

### des

*void des()*

*Defined at test/logger_test.c#41*

### logger_printf_NULL_ptr

*void logger_printf_NULL_ptr()*

*Defined at test/logger_test.c#46*

### logger_print_NULL_ptr

*void logger_print_NULL_ptr()*

*Defined at test/logger_test.c#51*

### logger_new_non_NULL

*void logger_new_non_NULL()*

*Defined at test/logger_test.c#58*

### test_std_log_level

*void test_std_log_level()*

*Defined at test/logger_test.c#63*

### check_verbosity

*void check_verbosity()*

*Defined at test/logger_test.c#80*

### check_marker_non_NULL

*void check_marker_non_NULL()*

*Defined at test/logger_test.c#103*

### check_output_marker

*void check_output_marker()*

*Defined at test/logger_test.c#108*

### queue_new_capped

*queue_t * queue_new_capped(size_t max_len)*

*Defined at src/queue.c#24*

 Creates a new queue, which can hold a maximum of max_len items. Insert operations will return -2, if capacity is exhausted.



**return** A new queue with max_len capacity.

### queue_new_uncapped

*queue_t * queue_new_uncapped()*

*Defined at src/queue.c#51*

 Creates a new queue, which can theoretically grow to infinity.



**return** A new uncapped queue.

### queue_add

*int queue_add(queue_t * queue, void * item)*

*Defined at src/queue.c#141*

 Adds an element to the queue.



**queue**

**item**

### queue_addall

*int queue_addall(queue_t * queue, void ** items, size_t nitems, _Bool reverse)*

*Defined at src/queue.c#97*

 Adds an array of elements to the queue.



**queue**

**items**

**nitems**

**reverse**

### queue_peek

*void * queue_peek(queue_t * queue)*

*Defined at src/queue.c#145*

 Get the next element from the queue without removing it.



**queue**

**return** The next element, or NULL if empty.

### queue_poll

*void * queue_poll(queue_t * queue)*

*Defined at src/queue.c#177*

 Get the next element from the queue and removes it.



**queue**

**return** The next element, or NULL if empty.

### queue_length

*size_t queue_length(queue_t * queue)*

*Defined at src/queue.c#73*

 Get the length of the queue.



**queue**

**return** The length of the queue.

### queue_destroy

*void queue_destroy(queue_t * queue)*

*Defined at src/queue.c#212*

 Destroys the queue. IMPORTANT: Stored elements are not deallocated.



**queue**

### add_NULL

*void add_NULL()*

*Defined at test/queue_test.c#12*

### addall_NULL

*void addall_NULL()*

*Defined at test/queue_test.c#17*

### peek_NULL

*void peek_NULL()*

*Defined at test/queue_test.c#22*

### poll_NULL

*void poll_NULL()*

*Defined at test/queue_test.c#27*

### zero_length_capped_NULL

*void zero_length_capped_NULL()*

*Defined at test/queue_test.c#32*

### uncapped_non_NULL

*void uncapped_non_NULL()*

*Defined at test/queue_test.c#39*

### uncapped_add_0

*void uncapped_add_0()*

*Defined at test/queue_test.c#44*

### uncapped_add_1

*void uncapped_add_1()*

*Defined at test/queue_test.c#49*

### uncapped_add_2

*void uncapped_add_2()*

*Defined at test/queue_test.c#54*

### uncapped_peek

*void uncapped_peek()*

*Defined at test/queue_test.c#59*

### uncapped_addall

*void uncapped_addall()*

*Defined at test/queue_test.c#66*

### uncapped_poll

*void uncapped_poll()*

*Defined at test/queue_test.c#71*

### capped_non_NULL

*void capped_non_NULL()*

*Defined at test/queue_test.c#80*

### capped_addall

*void capped_addall()*

*Defined at test/queue_test.c#85*

### capped_peek

*void capped_peek()*

*Defined at test/queue_test.c#90*

### capped_add

*void capped_add()*

*Defined at test/queue_test.c#96*

### capped_full

*void capped_full()*

*Defined at test/queue_test.c#101*

### capped_poll

*void capped_poll()*

*Defined at test/queue_test.c#106*

### msprintf

*int msprintf(char ** out, const char * format)*

*Defined at src/mstring.c#10*

 Like sprintf, but allocates a buffer big enough to hold the finished string.



**out**

**format**

**...**

**return** The amount of bytes written, or a negative value on error.

### vmsprintf

*int vmsprintf(char ** out, const char * format, va_list args)*

*Defined at src/mstring.c#18*

 Like msprintf, but gets the varargs from a va_list.



**out**

**format**

**args**

**return** The amount of bytes written, or a negative value on error.

### mstrcat

*char * mstrcat(char ** dest, const char * src)*

*Defined at src/mstring.c#37*

 Like strcat, but automatically reallocates the dest-buffer to hold the concatenated string.

 IMPORTANT: dest has to be dynamically allocates using another library function or ualloc/urealloc.



**dest**

**src**

**return** dest, or NULL on error.

### startswith

*_Bool startswith(const char * str, const char * start)*

*Defined at src/mstring.c#44*

 Returns true if str starts with start, false otherwise.



**str**

**start**

**return** true if str starts with start, false otherwise.

### endswith

*_Bool endswith(const char * str, const char * end)*

*Defined at src/mstring.c#53*

 Returns true if str ends with end, false otherwise.



**str**

**end**

**return** true if str ends with end, false otherwise.

### strspl

*int strspl(string_array_t * out, const char * str, const char * delim)*

*Defined at src/mstring.c#62*

 Splits the string str on every occurance of delim.



**out**

**str**

**delim**

**return** 0 on success, a negative value otherwise.

### strjoin

*int strjoin(char ** out,  arr, const char * first, const char * delim, const char * last)*

*Defined at src/mstring.c#82*

 Joins a string array to a string.



**out**

**arr**

**first**

**delim**

**last**

### strreplace

*char * strreplace(char ** str, const char * search, const char * replace)*

*Defined at src/mstring.c#108*

 Replaces search by replace for every occurance in str.



**str**

**search**

**replace**

**return** str or NULL on error.

### strupp

*char * strupp(char * str)*

*Defined at src/mstring.c#136*

 Converts the string {

**arg** str} to UPPERCASE.



**str**

**return** {

**arg** str} or {**<not a builtin command>**  NULL} on error.

### strlow

*char * strlow(char * str)*

*Defined at src/mstring.c#147*

 Converts the string {

**arg** str} to lowercase.



**str**

**return** {

**arg** str} or {**<not a builtin command>**  NULL} on error.

### logger2syslog

*int logger2syslog(loglevel lvl)*

*Defined at src/logger.c#11*

### argparse

*argparser_status argparse(int argc, char ** argv, argparser_opt * opts, int * optint, const char * longopt_start, char shortopt_start, char longopt_seperator, const char * parse_stop)*

*Defined at src/argparser.c#57*

 Parses program arguments.



**argc**

**argv**

**opts**

**optint**

**longopt_start**

**shortopt_start**

**longopt_seperator**

**parse_stop**

**return** The status of parsing.

### argparse_exec_0

*void argparse_exec_0()*

*Defined at test/argparser_test.c#24*

### argparse_args_0

*void argparse_args_0()*

*Defined at test/argparser_test.c#29*

### argparse_exec_1

*void argparse_exec_1()*

*Defined at test/argparser_test.c#50*

### argparse_args_1

*void argparse_args_1()*

*Defined at test/argparser_test.c#55*

### djb2

*hash_t djb2(const void * data, size_t size)*

*Defined at src/hash.c#3*

 Hashes data using the djb2 algorithm.

### fnv1a

*hash_t fnv1a(const void * data, size_t size)*

*Defined at src/hash.c#13*

 Hashes data using the fnv1a algorithm.

### murmurhash3

*hash_t murmurhash3(const void * data, size_t size)*

*Defined at src/hash.c#25*

 Hashes data using murmurhash3.

### fpeek

*int fpeek(FILE * stream)*

*Defined at src/file.c#7*

 Get an character from the specified stream without removing it from the stream.



**stream**

**return** The peeked character, or a negative value if an error occured.

### fpeeks

*char * fpeeks(FILE * stream, size_t n)*

*Defined at src/file.c#16*

 Get a string with n characters from the specified stream without removing them from the stream.



**stream**

**n**

**return** The peeked string, or NULL if an error occured.

### fsize

*size_t fsize(FILE * stream)*

*Defined at src/file.c#40*

 Get the size of the stream in bytes.

 IMPORTANT: Only works with streams, which support seeking (i.e. Files).



**stream**

**return** The size in bytes of the stream.

### test_fsize

*void test_fsize()*

*Defined at test/file_test.c#14*

### test_fpeek

*void test_fpeek()*

*Defined at test/file_test.c#16*

### test_fpeeks

*void test_fpeeks()*

*Defined at test/file_test.c#25*

### put_NULL

*void put_NULL()*

*Defined at test/hashmap_test.c#17*

### get_NULL

*void get_NULL()*

*Defined at test/hashmap_test.c#23*

### size_NULL

*void size_NULL()*

*Defined at test/hashmap_test.c#29*

### contains_key_NULL

*void contains_key_NULL()*

*Defined at test/hashmap_test.c#35*

### foreach_NULL

*void foreach_NULL()*

*Defined at test/hashmap_test.c#41*

### clear_NULL

*void clear_NULL()*

*Defined at test/hashmap_test.c#48*

### remove_NULL

*void remove_NULL()*

*Defined at test/hashmap_test.c#54*

### new_non_NULL

*void new_non_NULL()*

*Defined at test/hashmap_test.c#62*

### check_empty_size

*void check_empty_size()*

*Defined at test/hashmap_test.c#67*

### put_0

*void put_0()*

*Defined at test/hashmap_test.c#72*

### put_1

*void put_1()*

*Defined at test/hashmap_test.c#77*

### put_2

*void put_2()*

*Defined at test/hashmap_test.c#82*

### check_after_add

*void check_after_add()*

*Defined at test/hashmap_test.c#87*

### put_3

*void put_3()*

*Defined at test/hashmap_test.c#99*

### put_4

*void put_4()*

*Defined at test/hashmap_test.c#104*

### put_5

*void put_5()*

*Defined at test/hashmap_test.c#109*

### check_size

*void check_size()*

*Defined at test/hashmap_test.c#114*

### cb_func

*void cb_func(void * key, size_t keysize, void * value, void * pipe)*

*Defined at test/hashmap_test.c#119*

### foreach

*void foreach()*

*Defined at test/hashmap_test.c#138*

### remove_

*void remove_()*

*Defined at test/hashmap_test.c#145*

### clear

*void clear()*

*Defined at test/hashmap_test.c#155*

### buffer_new

*buffer_t * buffer_new(size_t len)*

*Defined at src/buffer.c#13*

### buffer_new_from_string

*buffer_t * buffer_new_from_string(const char * str)*

*Defined at src/buffer.c#41*

### buffer_new_from_pointer

*buffer_t * buffer_new_from_pointer(const void * buf, size_t len)*

*Defined at src/buffer.c#30*

### buffer_get

*void * buffer_get(buffer_t * buf)*

*Defined at src/buffer.c#48*

### buffer_size

*size_t buffer_size(buffer_t * buf)*

*Defined at src/buffer.c#57*

### buffer_destroy

*void buffer_destroy(buffer_t * buffer)*

*Defined at src/buffer.c#66*

### arraylist_realloc

*int arraylist_realloc(arraylist_t * list)*

*Defined at src/arraylist.c#19*

### arraylist_new_prealloc

*arraylist_t * arraylist_new_prealloc(size_t initial_cap)*

*Defined at src/arraylist.c#31*

### check_msprintf

*void check_msprintf()*

*Defined at test/mstring_test.c#14*

### check_mstrcat

*void check_mstrcat()*

*Defined at test/mstring_test.c#21*

### check_startswith

*void check_startswith()*

*Defined at test/mstring_test.c#29*

### check_endswith

*void check_endswith()*

*Defined at test/mstring_test.c#34*

### check_strspl

*void check_strspl()*

*Defined at test/mstring_test.c#41*

### check_strjoin

*void check_strjoin()*

*Defined at test/mstring_test.c#49*

### check_strreplace

*void check_strreplace()*

*Defined at test/mstring_test.c#60*

### check_strupp

*void check_strupp()*

*Defined at test/mstring_test.c#74*

### check_strlow

*void check_strlow()*

*Defined at test/mstring_test.c#80*

### hashmap_init_buckets

*void hashmap_init_buckets(struct hashmap_bucket * buckets, size_t nbuckets)*

*Defined at src/hashmap.c#28*

### hashmap_get_bucket

*struct hashmap_bucket * hashmap_get_bucket(const hashmap_t * map, const void * key, size_t keysize)*

*Defined at src/hashmap.c#35*

### hashmap_realloc

*int hashmap_realloc(hashmap_t * map)*

*Defined at src/hashmap.c#55*

### not_terminate

*_Bool not_terminate(const argparser_opt * opt)*

*Defined at src/argparser.c#11*

### getlongopt

*argparser_opt * getlongopt(const argparser_opt * opts, const char * long_name, size_t len)*

*Defined at src/argparser.c#29*

### getshortopt

*argparser_opt * getshortopt(const argparser_opt * opts, char short_name)*

*Defined at src/argparser.c#44*

### add_NULL

*void add_NULL()*

*Defined at test/hashset_test.c#15*

### size_NULL

*void size_NULL()*

*Defined at test/hashset_test.c#20*

### clear_NULL

*void clear_NULL()*

*Defined at test/hashset_test.c#25*

### remove_NULL

*void remove_NULL()*

*Defined at test/hashset_test.c#30*

### contains_NULL

*void contains_NULL()*

*Defined at test/hashset_test.c#35*

### new_non_NULL

*void new_non_NULL()*

*Defined at test/hashset_test.c#42*

### check_empty_size

*void check_empty_size()*

*Defined at test/hashset_test.c#47*

### add_0

*void add_0()*

*Defined at test/hashset_test.c#52*

### add_1

*void add_1()*

*Defined at test/hashset_test.c#57*

### add_2

*void add_2()*

*Defined at test/hashset_test.c#62*

### check_after_add

*void check_after_add()*

*Defined at test/hashset_test.c#67*

### add_3

*void add_3()*

*Defined at test/hashset_test.c#75*

### add_4

*void add_4()*

*Defined at test/hashset_test.c#80*

### add_5

*void add_5()*

*Defined at test/hashset_test.c#85*

### check_size

*void check_size()*

*Defined at test/hashset_test.c#90*

### cb_func

*void cb_func(void * item, size_t size, void * pipe)*

*Defined at test/hashset_test.c#95*

### foreach

*void foreach()*

*Defined at test/hashset_test.c#106*



## Enums

| enum  |

--

| TYPE_HASHSET |


*Defined at include/set.h#6*

| enum  |

--

| TYPE_ARRAYLIST |
| TYPE_LINKEDLIST |


*Defined at include/list.h#6*

| enum  |

--

| TRACE |
| DEBUG |
| INFO |
| NOTICE |
| WARNING |
| ERROR |
| FATAL |


*Defined at include/logger.h#11*

| enum  |

--

| ARGPARSE_OK |
| ARGPARSE_GENERIC_ERROR |
| ARGPARSE_ARG_REQ |
| ARGPARSE_UNKNOWN_FLAG |


*Defined at include/argparser.h#11*

| enum  |

--

| NO_ARG |
| OPT_ARG |
| REQ_ARG |


*Defined at include/argparser.h#33*



