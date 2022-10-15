#include <errno.h>

#include <string.h>

#include "queue.h"
#include "dmem.h"

#include "linkedlist.h"

struct queue
{
  size_t len;
  size_t max_len;

  void ** arr;
  size_t front; // Start
  size_t rear; // End
};

// TODO: Move into seperate part of lib

void * memrev(void *arr, size_t nitems, size_t size)
{
  if(nitems == 0UL || size == 0UL)
  {
    errno = EINVAL;
    return NULL;
  }

  void * buffer = ualloc(size);
  if(buffer == NULL)
  {
    errno = ENOMEM;
    return NULL;
  }

  size_t i = nitems - 1, j = 0;
  while(j < i)
  {
    memcpy(buffer, ((uint8_t *) arr) + (j * size), size);
    memcpy(((uint8_t *) arr) + (j * size), ((uint8_t *) arr) + (i * size), size);
    memcpy(((uint8_t *) arr) + (i * size), buffer, size);
    j++;
    i--;
  }
  ufree(buffer);

  return arr;
}

queue * queue_new_capped(size_t max_len)
{
  if(max_len == 0)
  {
    errno = EINVAL;
    return NULL;
  }

  queue *q = (queue *) ualloc(sizeof(*q));
  if(q == NULL)
  {
    errno = ENOMEM;
    return NULL;
  }

  q->len = 0UL;
  q->max_len = max_len;

  if((q->arr = (void **) ualloc(sizeof(void *) * max_len)) == NULL)
  {
    errno = ENOMEM;
    return NULL;
  }

  q->front = 0UL;
  q->rear = 0UL;

  return q;
}

queue * queue_new_uncapped(void)
{
  queue *q = (queue *) ualloc(sizeof(*q));
  if(q == NULL)
  {
    errno = EINVAL;
    return NULL;
  }

  q->len = 0UL;
  q->max_len = 0UL;

  if((q->arr = (void **) linkedlist_new()) == NULL)
  {
    errno = ENOMEM;
    return NULL;
  }

  q->front = 0UL;
  q->rear = 0UL;

  return q;
}

size_t queue_length(queue *q)
{
  if(q == NULL)
  {
    errno = EINVAL;
    return 0;
  }

  if(q->max_len == 0UL) // Uncapped
    return linkedlist_length((linkedlist *) q->arr);
  
  // Capped
  return q->len;
}

int queue_addall(queue *q, void **items, size_t nitems, bool reverse)
{
  if(q == NULL || items == NULL)
  {
    errno = EINVAL;
    return -1;
  }

  if(q->max_len == 0) // Uncapped
  {
    if(reverse)
      memrev(items, nitems, sizeof(*items));

    if(linkedlist_addall((linkedlist *) q->arr, items, nitems) < 0)
      return -1;
  }
  else // Capped
  {
    if(q->len + nitems > q->max_len)
      return -2;

    if(reverse)
      for(size_t i = nitems - 1; i >= 0; i--, q->rear %= q->max_len)
        q->arr[q->rear++] = items[i];
    else
      for(size_t i = 0; i < nitems; i++, q->rear %= q->max_len)
        q->arr[q->rear++] = items[i];
    q->len += nitems;
  }

  return 0;
}

int queue_add(queue *q, void *item)
{
  return queue_addall(q, &item, 1, false);
}

void * queue_peek(queue *q)
{
  if(q == NULL)
  {
    errno = EINVAL;
    return NULL;
  }

  if(q->max_len == 0) // Uncapped
    return linkedlist_get((linkedlist *) q->arr, 0);
  
  // Capped
  if(queue_length(q) == 0UL)
    return NULL;

  return q->arr[q->front];
}

void * queue_poll(queue *q)
{
  if(q == NULL)
  {
    errno = EINVAL;
    return NULL;
  }

  if(q->max_len == 0) // Uncapped
    return linkedlist_remove((linkedlist *) q->arr, 0);

  // Capped
  if(queue_length(q) == 0UL)
    return NULL;

  void * item = q->arr[q->front++];
  q->front %= q->max_len;
  q->len--;
  return item;
}

void queue_destroy(queue *q)
{
  if(q == NULL)
    return;

  if(q->max_len == 0) // Uncapped
  {
    linkedlist_destroy((linkedlist *) q->arr);
  }
  else // Capped
  {
    if(q->arr != NULL)
      ufree(q->arr);
  }
}

