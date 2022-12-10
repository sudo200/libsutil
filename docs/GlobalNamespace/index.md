# Global Namespace



## Records

* [](.md)
* [arraylist](arraylist.md)
* [list](list.md)
* [](.md)
* [logger](logger.md)
* [marker](marker.md)
* [linkedlist](linkedlist.md)
* [linkednode](linkednode.md)
* [queue](queue.md)
* [](.md)
* [stack](stack.md)


## Functions

### arraylist_new

*arraylist * arraylist_new()*

*Defined at src/arraylist.c#30*

 Creates a new arraylist.



**return** The new arraylist, or NULL if an error occured.

### arraylist_add

*int arraylist_add(arraylist * list, void * item)*

*Defined at src/arraylist.c#45*

 Adds the given element at the end of the arraylist.



**list**

**item**

**return** 0 if successful, else a negative value.

### arraylist_addall

*int arraylist_addall(arraylist * list, void ** items, size_t nitems)*

*Defined at src/arraylist.c#49*

 Adds the given array to the end of the arraylist.



**list**

**items**

**nitems**

**return** 0 if successful, else a negative value.

### arraylist_insert

*int arraylist_insert(arraylist * list, void * item, size_t index)*

*Defined at src/arraylist.c#66*

 Inserts the given element at index into the arraylist.



**list**

**item**

**index**

**return** 0 if successful, else a negative value.

### arraylist_insertall

*int arraylist_insertall(arraylist * list, void ** items, size_t nitems, size_t index)*

*Defined at src/arraylist.c#70*

 Inserts the given array at index into the arraylist.



**list**

**items**

**nitems**

**index**

**return** 0 if successful, else a negative value.

### arraylist_get

*void * arraylist_get(arraylist * list, size_t index)*

*Defined at src/arraylist.c#95*

 Gets the element at the given index.



**list**

**index**

**return** The element at index, or NULL if an error occured.

### arraylist_length

*size_t arraylist_length(arraylist * list)*

*Defined at src/arraylist.c#109*

 Gets the length (element count) of the arraylist.



**list**

**return** The length.

### arraylist_remove

*void * arraylist_remove(arraylist * list, size_t index)*

*Defined at src/arraylist.c#118*

 Removes the element at given index from the arraylist and returns it.



**list**

**index**

**return** The element at index, or NULL if an error occured.

### arraylist_foreach

*int arraylist_foreach(arraylist * list, void (*)(void *, void *) cb, void * pipe)*

*Defined at src/arraylist.c#140*

 Calls cb with every element in the given arraylist.



**list**

**cb**

**pipe**

**return** 0 if successful, else a negative value.

### arraylist_to_array

*void ** arraylist_to_array(arraylist * list)*

*Defined at src/arraylist.c#151*

 Returns an array with a copy of to lists elements.



**list**

**return** The generated array, or NULL on error.

### arraylist_clear

*int arraylist_clear(arraylist * list)*

*Defined at src/arraylist.c#166*

 Empties the given arraylist. Stored elements are not deallocated.



**list**

**return** 0 if successful, else a negative value.

### arraylist_destroy

*void arraylist_destroy(arraylist * list)*

*Defined at src/arraylist.c#181*

 Destroyes the given arraylist.

 IMPORTANT: Stored elements are not deallocated.



**list**

### arraylist_realloc

*int arraylist_realloc(arraylist * list, int diff)*

*Defined at src/arraylist.c#16*

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

### logger_new

*logger * logger_new(FILE * info, FILE * error, _Bool _syslog)*

*Defined at src/logger.c#36*

 Creates a new logger with given streams for writting output to.

 If both info and error are not NULL, info is used for output below WARNING and error for output from and above WARNING.

 If info is not NULL and error is NULL, or vice versa, the one stream is used for all output.

 If both info and error are NULL, info is set to stdout and error to stderr.



**info**

**error**

**_syslog**

### logger_do_trace

*_Bool logger_do_trace(logger * log)*

*Defined at src/logger.c#61*

### logger_do_debug

*_Bool logger_do_debug(logger * log)*

*Defined at src/logger.c#63*

### logger_do_info

*_Bool logger_do_info(logger * log)*

*Defined at src/logger.c#65*

### logger_do_notice

*_Bool logger_do_notice(logger * log)*

*Defined at src/logger.c#67*

### logger_do_warning

*_Bool logger_do_warning(logger * log)*

*Defined at src/logger.c#69*

### logger_do_error

*_Bool logger_do_error(logger * log)*

*Defined at src/logger.c#71*

### logger_do_fatal

*_Bool logger_do_fatal(logger * log)*

*Defined at src/logger.c#73*

### logger_printf

*int logger_printf(logger * log, loglevel lvl, marker * m, const char * format)*

*Defined at src/logger.c#75*

### logger_print

*int logger_print(logger * log, loglevel lvl, marker * m, const char * msg)*

*Defined at src/logger.c#104*

### logger_destroy

*void logger_destroy(logger * log)*

*Defined at src/logger.c#110*

 Destroys the given logger instance.

 IMPORTANT: Used streams are NOT closed BUT flushed.

### marker_new

*marker * marker_new(const char * name)*

*Defined at src/logger.c#123*

 Creates a new marker with the given name.



**name**

**return** The new marker or NULL on error.

### marker_destroy

*void marker_destroy(marker * m)*

*Defined at src/logger.c#133*

 Destroys the given marker.



**m**

### msprintf

*int msprintf(char ** out, const char * format)*

*Defined at src/mstring.c#8*

 Like sprintf, but allocates a buffer big enough to hold the finished string.



**out**

**format**

**...**

**return** The amount of bytes written, or a negative value on error.

### vmsprintf

*int vmsprintf(char ** out, const char * format, va_list args)*

*Defined at src/mstring.c#16*

 Like msprintf, but gets the varargs from a va_list.



**out**

**format**

**args**

**return** The amount of bytes written, or a negative value on error.

### mstrcat

*char * mstrcat(char ** dest, const char * src)*

*Defined at src/mstring.c#35*

 Like strcat, but automatically reallocates the dest-buffer to hold the concatenated string.

 IMPORTANT: dest has to be dynamically allocates using another library function or ualloc/urealloc.



**dest**

**src**

**return** dest, or NULL on error.

### startswith

*_Bool startswith(const char * str, const char * start)*

*Defined at src/mstring.c#42*

 Returns true if str starts with start, false otherwise.



**str**

**start**

**return** true if str starts with start, false otherwise.

### endswith

*_Bool endswith(const char * str, const char * end)*

*Defined at src/mstring.c#51*

 Returns true if str ends with end, false otherwise.



**str**

**end**

**return** true if str ends with end, false otherwise.

### strspl

*int strspl(string_array_t * out, const char * str, const char * delim)*

*Defined at src/mstring.c#60*

 Splits the string str on every occurance of delim.



**out**

**str**

**delim**

**return** 0 on success, a negative value otherwise.

### strjoin

*int strjoin(char ** out,  arr, const char * first, const char * delim, const char * last)*

*Defined at src/mstring.c#80*

 Joins a string array to a string.



**out**

**arr**

**first**

**delim**

**last**

### strreplace

*char * strreplace(char ** str, const char * search, const char * replace)*

*Defined at src/mstring.c#106*

 Replaces search by replace for every occurance in str.



**str**

**search**

**replace**

**return** str or NULL on error.

### logger2syslog

*int logger2syslog(loglevel lvl)*

*Defined at src/logger.c#12*

### linkedlist_new

*linkedlist * linkedlist_new()*

*Defined at src/linkedlist.c#98*

 Creates a new linked list.



**return** The new linked list, or NULL on error.

### linkedlist_length

*size_t linkedlist_length(linkedlist * list)*

*Defined at src/linkedlist.c#115*

 Returns the length of the linked list.



**list**

**return** Length of the list

### linkedlist_add

*int linkedlist_add(linkedlist * list, void * element)*

*Defined at src/linkedlist.c#124*

 Adds an element to the linked list.



**list**

**element**

**return** 0 on success, a negative value on error.

### linkedlist_addall

*int linkedlist_addall(linkedlist * list, void ** elements, size_t nitems)*

*Defined at src/linkedlist.c#132*

 Adds an array of elements to the linked list.



**list**

**elements**

**nitems**

**return** 0 on success, a negative value on error.

### linkedlist_insert

*int linkedlist_insert(linkedlist * list, void * element, size_t index)*

*Defined at src/linkedlist.c#147*

 Inserts an element at index to the linked list.



**list**

**element**

**index**

**return** 0 on success, a negative value on error.

### linkedlist_insertall

*int linkedlist_insertall(linkedlist * list, void ** elements, size_t nitems, size_t index)*

*Defined at src/linkedlist.c#161*

 Inserts an array of elements at index to the linked list.



**list**

**elements**

**nitems**

**index**

**return** 0 on success, a negative value on error.

### linkedlist_get

*void * linkedlist_get(linkedlist * list, size_t index)*

*Defined at src/linkedlist.c#179*

 Get the element at specified index.



**list**

**index**

**return** The item, or NULL on error.

### linkedlist_remove

*void * linkedlist_remove(linkedlist * list, size_t index)*

*Defined at src/linkedlist.c#193*

 Removes an element at index, and returns it.



**list**

**index**

**return** The removed element, or NULL on error.

### linkedlist_foreach

*int linkedlist_foreach(linkedlist * list, void (*)(void *, void *) cb, void * pipe)*

*Defined at src/linkedlist.c#223*

 Executes a function for each element in the list.



**list**

**cb**

**pipe**

**return** 0 on success, a negative value on error.

### linkedlist_to_array

*void ** linkedlist_to_array(linkedlist * list)*

*Defined at src/linkedlist.c#236*

 Returns an array with a copy of the list's elements.



**list**

**return** The generated array, or NULL on error.

### linkedlist_clear

*int linkedlist_clear(linkedlist * list)*

*Defined at src/linkedlist.c#255*

 Clears the linked list.



**list**

**return** 0 on success, a negative value on error.

### linkedlist_destroy

*void linkedlist_destroy(linkedlist * list)*

*Defined at src/linkedlist.c#274*

  Destroys the linked list.

  IMPORTANT: Stored elements are not deallocated!



**list**

### __linkedlist_add

*int __linkedlist_add(linkedlist * list, void * element)*

*Defined at src/linkedlist.c#24*

### __linkedlist_get

*linkednode * __linkedlist_get(linkedlist * list, size_t index)*

*Defined at src/linkedlist.c#48*

### __linkedlist_insert

*int __linkedlist_insert(linkedlist * list, void * element, size_t index)*

*Defined at src/linkedlist.c#66*

### queue_new_capped

*queue * queue_new_capped(size_t max_len)*

*Defined at src/queue.c#24*

 Creates a new queue, which can hold a maximum of max_len items. Insert operations will return -2, if capacity is exhausted.



**return** A new queue with max_len capacity.

### queue_new_uncapped

*queue * queue_new_uncapped()*

*Defined at src/queue.c#51*

 Creates a new queue, which can theoretically grow to infinity.



**return** A new uncapped queue.

### queue_add

*int queue_add(queue * queue, void * item)*

*Defined at src/queue.c#141*

 Adds an element to the queue.



**queue**

**item**

### queue_addall

*int queue_addall(queue * queue, void ** items, size_t nitems, _Bool reverse)*

*Defined at src/queue.c#97*

 Adds an array of elements to the queue.



**queue**

**items**

**nitems**

**reverse**

### queue_peek

*void * queue_peek(queue * queue)*

*Defined at src/queue.c#143*

 Get the next element from the queue without removing it.



**queue**

**return** The next element, or NULL if empty.

### queue_poll

*void * queue_poll(queue * queue)*

*Defined at src/queue.c#175*

 Get the next element from the queue and removes it.



**queue**

**return** The next element, or NULL if empty.

### queue_length

*size_t queue_length(queue * queue)*

*Defined at src/queue.c#73*

 Get the length of the queue.



**queue**

**return** The length of the queue.

### queue_destroy

*void queue_destroy(queue * queue)*

*Defined at src/queue.c#210*

 Destroys the queue. IMPORTANT: Stored elements are not deallocated.



**queue**

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

### not_terminate

*_Bool not_terminate(const argparser_opt * opt)*

*Defined at src/argparser.c#11*

### getlongopt

*argparser_opt * getlongopt(const argparser_opt * opts, const char * long_name, size_t len)*

*Defined at src/argparser.c#29*

### getshortopt

*argparser_opt * getshortopt(const argparser_opt * opts, char short_name)*

*Defined at src/argparser.c#44*

### stack_new_capped

*stack * stack_new_capped(size_t max_len)*

*Defined at src/stack.c#16*

 Creates a new stack, which can hold a maximum of max_len items. Push operations will return -2, if capacity is exhausted.



**return** A new stack with max_len capacity.

### stack_new_uncapped

*stack * stack_new_uncapped()*

*Defined at src/stack.c#39*

 Creates a new queue, which can theoretically grow to infinity.



**return** A new uncapped queue.

### stack_push

*int stack_push(stack * s, void * item)*

*Defined at src/stack.c#57*

 Pushes an item onto the stack.



**s**

**item**

**return** 0 on success, -2 when capacity is exhausted, or another negative number on error.

### stack_peek

*void * stack_peek(stack * s)*

*Defined at src/stack.c#76*

 Get the next element from the stack without removing it.



**s**

**return** The next element, or NULL if empty.

### stack_pop

*void * stack_pop(stack * s)*

*Defined at src/stack.c#90*

 Pop the next element from the stack.



**s**

**return** The next element, or NULL if empty.

### stack_size

*size_t stack_size(stack * s)*

*Defined at src/stack.c#103*

 Get the current size of the stack



**s**

**return** The size of the stack.

### stack_clear

*int stack_clear(stack * s)*

*Defined at src/stack.c#114*

 Deletes all elements from the stack.

 IMPORTANT: Stored elements are not deallocated.



**s**

### stack_destroy

*void stack_destroy(stack * s)*

*Defined at src/stack.c#127*

 Destroys the stack.

 IMPORTANT: Stored elements are not deallocated.



**s**



## Enums

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



