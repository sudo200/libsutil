#include <errno.h>

#include <string.h>

#include "dmem.h"
#include "queue.h"

#include "linkedlist.h"
#include "util.h"

struct queue {
  size_t len;
  size_t max_len;

  void **arr;
  size_t front; // Start
  size_t rear;  // End
  bool lock;
};

#define lock(q)   (q->lock = true)
#define unlock(q)   (q->lock = false)

queue *queue_new_capped(size_t max_len) {
  if (max_len == 0) {
    errno = EINVAL;
    return NULL;
  }

  queue *q = (queue *)ualloc(sizeof(*q));
  if (q == NULL) {
    errno = ENOMEM;
    return NULL;
  }

  q->len = 0UL;
  q->max_len = max_len;

  if ((q->arr = (void **)ualloc(sizeof(void *) * max_len)) == NULL) {
    errno = ENOMEM;
    return NULL;
  }

  q->front = 0UL;
  q->rear = 0UL;
  q->lock = false;

  return q;
}

queue *queue_new_uncapped(void) {
  queue *q = (queue *)ualloc(sizeof(*q));
  if (q == NULL) {
    errno = EINVAL;
    return NULL;
  }

  q->len = 0UL;
  q->max_len = 0UL;

  if ((q->arr = (void **)linkedlist_new()) == NULL) {
    errno = ENOMEM;
    return NULL;
  }

  q->front = 0UL;
  q->rear = 0UL;
  q->lock = false;

  return q;
}

size_t queue_length(queue *restrict q) {
  if (q == NULL) {
    errno = EINVAL;
    return 0;
  }

  if(q->lock) {
    errno = ENOLCK;
    return 0;
  }

  lock(q);
  size_t len = 0UL;

  if (q->max_len == 0UL) // Uncapped
    len = linkedlist_length((linkedlist *)q->arr);
  else // Capped
    len = q->len;

  unlock(q);

  return len;
}

int queue_addall(queue *q, void **items, size_t nitems, bool reverse) {
  if (q == NULL || items == NULL) {
    errno = EINVAL;
    return -1;
  }

  if(q->lock) {
    errno = ENOLCK;
    return -1;
  }

  lock(q);
  int ret = 0;

  do {
    if (q->max_len == 0) { // Uncapped
      if (reverse)
        memrev(items, nitems, sizeof(*items));

      if (linkedlist_addall((linkedlist *)q->arr, items, nitems) < 0) {
        ret = -1;
        break;
      }
    } else { // Capped
      if (q->len + nitems > q->max_len) {
        ret = -2;
        break;
      }

      if (reverse)
        for (size_t i = nitems - 1; i >= 0; i--, q->rear %= q->max_len)
          q->arr[q->rear++] = items[i];
      else
        for (size_t i = 0; i < nitems; i++, q->rear %= q->max_len)
          q->arr[q->rear++] = items[i];
      q->len += nitems;
    }
  } while(false);

  unlock(q);

  return ret;
}

int queue_add(queue *q, void *item) { return queue_addall(q, &item, 1, false); }

void *queue_peek(queue *restrict q) {
  if (q == NULL) {
    errno = EINVAL;
    return NULL;
  }

  if(q->lock) {
    errno = ENOLCK;
    return NULL;
  }

  lock(q);
  void *ret = NULL;

  do {
    if (q->max_len == 0) { // Uncapped
      ret = linkedlist_get((linkedlist *)q->arr, 0);
      break;
    }

    // Capped
    if (q->len == 0UL)
      break;

    ret = q->arr[q->front];
  } while(false);

  unlock(q);

  return ret;
}

void *queue_poll(queue *q) {
  if (q == NULL) {
    errno = EINVAL;
    return NULL;
  }

  if(q->lock) {
    errno = ENOLCK;
    return NULL;
  }

  lock(q);
  void *ret = NULL;

  do {
    if (q->max_len == 0) { // Uncapped
      ret = linkedlist_remove((linkedlist *)q->arr, 0);
      break;
    }

    // Capped
    if (q->len == 0UL)
      break;

    void *item = q->arr[q->front++];
    q->front %= q->max_len;
    q->len--;
    ret = item;
  } while(false);

  unlock(q);

  return ret;
}

void queue_destroy(queue *q) {
  if (q == NULL)
    return;

  if (q->max_len == 0) // Uncapped
  {
    linkedlist_destroy((linkedlist *)q->arr);
  } else // Capped
  {
    if (q->arr != NULL)
      ufree(q->arr);
  }
  ufree(q);
}
