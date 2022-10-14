#include <stdlib.h>

#include "queue.h"
#include "dmem.h"

struct queue_t
{
  size_t max_len;

  void ** arr;
  size_t front; // Start
  size_t rear; // End
};

queue_t * queue_new_capped(size_t max_len)
{
  if(max_len == 0)
    return NULL;

  queue_t *queue = (queue_t *) ualloc(sizeof(*queue));
  if(queue == NULL)
    return NULL;

  queue->max_len = max_len;

  if((queue->arr = (void **) ualloc(sizeof(void *) * max_len)) == NULL)
    return NULL;

  queue->front = 0UL;
  queue->rear = 0UL;

  return queue;
}

queue_t * queue_new_uncapped(void)
{
  queue_t *queue = (queue_t *) ualloc(sizeof(*queue));
  if(queue == NULL)
    return NULL;

  queue->max_len = 0UL;

  queue->arr = NULL;
  queue->front = 0UL;
  queue->rear = 0UL;

  return queue;
}

size_t queue_length(queue_t *queue)
{
  if(queue == NULL)
    return 0;

  return labs(((long)queue->rear) - ((long)queue->front));
}

int queue_addall(queue_t *queue, void **items, size_t nitems, bool reverse)
{
  if(queue == NULL || items == NULL)
    return -1;

  if(queue->max_len == 0) // Uncapped
  {

  }
  else // Capped
  {
    if(reverse)
      for(size_t i = nitems; i > 0; i--, queue->rear %= queue->max_len)
        queue->arr[queue->rear++] = items[i - 1];
    else
      for(size_t i = 0; i < nitems; i++, queue->rear %= queue->max_len)
        queue->arr[queue->rear++] = items[i];
  }

  return 0;
}

int queue_add(queue_t *queue, void *item)
{
  return queue_addall(queue, &item, 1, false);
}

void * queue_peek(queue_t *queue)
{
  if(queue == NULL)
    return NULL;

  if(queue->max_len == 0) // Uncapped
  {

  }
  else // Capped
  {
    if(queue_length(queue) == 0UL)
      return NULL;

    return queue->arr[queue->front];
  }
}

void * queue_poll(queue_t *queue)
{
  if(queue == NULL)
    return NULL;

  if(queue->max_len == 0) // Uncapped
  {

  }
  else // Capped
  {
    if(queue_length(queue) == 0UL)
      return NULL;

    void * item = queue->arr[queue->front++];
    queue->front %= queue->max_len;
    return item;
  }
}

void queue_destroy(queue_t *queue)
{
  if(queue == NULL)
    return;

  if(queue->arr != NULL)
    ufree(queue->arr);
}

