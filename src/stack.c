#include <errno.h>
#include <string.h>

#include "linkedlist.h"

#include "dmem.h"
#include "stack.h"

struct stack {
  size_t max_top;
  size_t top;

  void **arr;
};

stack_t *stack_new_capped(size_t max_len) {
  if (max_len == 0) {
    errno = EINVAL;
    return NULL;
  }

  stack_t *s = (stack_t *)ualloc(sizeof(*s));
  if (s == NULL) {
    errno = ENOMEM;
    return NULL;
  }

  s->max_top = max_len;
  s->top = 0UL;

  if ((s->arr = (void **)ualloc(sizeof(*s->arr) * max_len)) == NULL) {
    errno = ENOMEM;
    return NULL;
  }

  return s;
}

stack_t *stack_new_uncapped(void) {
  stack_t *s = (stack_t *)ualloc(sizeof(*s));
  if (s == NULL) {
    errno = ENOMEM;
    return NULL;
  }

  s->max_top = 0UL;
  s->top = 0UL;

  if ((s->arr = (void **)linkedlist_new()) == NULL) {
    errno = ENOMEM;
    return NULL;
  }

  return s;
}

int stack_push(stack_t *s, void *item) {
  if (s == NULL) {
    errno = EINVAL;
    return -1;
  }

  if (s->max_top == 0UL) {
    if (linkedlist_length((linkedlist_t *)s->arr) == 0UL)
      return linkedlist_add((linkedlist_t *)s->arr, item);
    return linkedlist_insert((linkedlist_t *)s->arr, item, 0UL);
  } else {
    if (s->top >= s->max_top)
      return -2;
    s->arr[s->top++] = item;
  }

  return 0;
}

void *stack_peek(stack_t *s) {
  if (s == NULL) {
    errno = EINVAL;
    return NULL;
  }

  if (s->max_top == 0UL)
    return linkedlist_get((linkedlist_t *)s->arr, 0UL);

  if (s->top == 0UL)
    return NULL;
  return s->arr[s->top - 1];
}

void *stack_pop(stack_t *s) {
  if (s == NULL) {
    errno = EINVAL;
    return NULL;
  }

  if (s->max_top == 0UL)
    return linkedlist_remove((linkedlist_t *)s->arr, 0UL);
  if (s->top == 0UL)
    return NULL;
  return s->arr[--s->top];
}

size_t stack_size(stack_t *s) {
  if (s == NULL) {
    errno = EINVAL;
    return 0UL;
  }

  if (s->max_top == 0UL)
    return linkedlist_length((linkedlist_t *)s->arr);
  return s->top;
}

int stack_clear(stack_t *s) {
  if (s == NULL) {
    errno = EINVAL;
    return -1;
  }

  if (s->max_top == 0UL)
    return linkedlist_clear((linkedlist_t *)s->arr);
  memset(s->arr, 0, sizeof(*s->arr) * s->top);
  s->top = 0UL;
  return 0;
}

void stack_destroy(stack_t *s) {
  if (s == NULL)
    return;

  if (s->max_top == 0UL)
    linkedlist_destroy((linkedlist_t *)s->arr);
  else
    ufree(s->arr);
  ufree(s);
}
