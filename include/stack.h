#ifndef ___STACK_H__
#define ___STACK_H__

#include "types.h"

typedef struct stack stack;

/**
 * Creates a new stack, which can hold a maximum of max_len items.
 * Push operations will return -2, if capacity is exhausted.
 *
 * @return A new stack with max_len capacity.
 */
stack *stack_new_capped(size_t max_len);

/**
 * Creates a new queue, which can theoretically grow to infinity.
 *
 * @return A new uncapped queue.
 */
stack *stack_new_uncapped(void);

/**
 * Pushes an item onto the stack.
 *
 * @param s The stack to push onto.
 * @param item The item to push.
 * @return 0 on success, -2 when capacity is exhausted, or another negative
 * number on error.
 */
int stack_push(stack *s, void *item);

/**
 * Get the next element from the stack without removing it.
 *
 * @param s The stack to peek from.
 * @return The next element, or NULL if empty.
 */
void *stack_peek(stack *s) __attribute__((pure));

/**
 * Pop the next element from the stack.
 *
 * @param s The stack to pop the item from.
 * @return The next element, or NULL if empty.
 */
void *stack_pop(stack *s);

/**
 * Get the current size of the stack
 *
 * @param s The stack to get size from.
 * @return The size of the stack.
 */
size_t stack_size(stack *s) __attribute__((const, pure));

/**
 * Deletes all elements from the stack.
 *
 * IMPORTANT: Stored elements are not deallocated.
 *
 * @param s The stack to clear.
 */
int stack_clear(stack *s);

/**
 * Destroys the stack.
 *
 * IMPORTANT: Stored elements are not deallocated.
 *
 * @param s The stack to destroy.
 */
void stack_destroy(stack *s);

#endif //___STACK_H__
