#include <errno.h>

#include <string.h>

#include <pthread.h>

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

  pthread_mutex_t lock;
};

queue_t *queue_new_capped(size_t max_len) {
  if (max_len == 0) {
    errno = EINVAL;
    return NULL;
  }

  queue_t *q = (queue_t *)ualloc(sizeof(*q));
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
  pthread_mutex_init(&q->lock, NULL);

  return q;
}

queue_t *queue_new_uncapped(void) {
  queue_t *q = (queue_t *)ualloc(sizeof(*q));
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
  pthread_mutex_init(&q->lock, NULL);

  return q;
}

size_t queue_length(queue_t *q) {
  if (q == NULL) {
    errno = EINVAL;
    return 0;
  }

  pthread_mutex_lock(&q->lock);
  size_t len = 0UL;

  if (q->max_len == 0UL) // Uncapped
    len = linkedlist_length((linkedlist_t *)q->arr);
  else // Capped
    len = q->len;

  pthread_mutex_unlock(&q->lock);

  return len;
}

int queue_addall(queue_t *q, void **items, size_t nitems, bool reverse) {
  if (q == NULL || items == NULL) {
    errno = EINVAL;
    return -1;
  }

  pthread_mutex_lock(&q->lock);
  int ret = 0;

  do {
    if (q->max_len == 0) { // Uncapped
      if (reverse)
        memrev(items, nitems, sizeof(*items));

      if (linkedlist_addall((linkedlist_t *)q->arr, items, nitems) < 0) {
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
        for (size_t i = 0UL; i < nitems; i++, q->rear %= q->max_len)
          q->arr[q->rear++] = items[i];
      q->len += nitems;
    }
  } while (false);

  pthread_mutex_unlock(&q->lock);

  return ret;
}

int queue_add(queue_t *q, void *item) {
  return queue_addall(q, &item, 1, false);
}

void *queue_peek(queue_t *q) {
  if (q == NULL) {
    errno = EINVAL;
    return NULL;
  }

  pthread_mutex_lock(&q->lock);
  void *ret = NULL;

  do {
    if (q->max_len == 0) { // Uncapped
      ret = linkedlist_get((linkedlist_t *)q->arr, 0);
      break;
    }

    // Capped
    if (q->len == 0UL)
      break;

    ret = q->arr[q->front];
  } while (false);

  pthread_mutex_unlock(&q->lock);

  return ret;
}

void *queue_poll(queue_t *q) {
  if (q == NULL) {
    errno = EINVAL;
    return NULL;
  }

  pthread_mutex_lock(&q->lock);
  void *ret = NULL;

  do {
    if (q->max_len == 0) { // Uncapped
      ret = linkedlist_remove((linkedlist_t *)q->arr, 0);
      break;
    }

    // Capped
    if (q->len == 0UL)
      break;

    void *item = q->arr[q->front++];
    q->front %= q->max_len;
    q->len--;
    ret = item;
  } while (false);

  pthread_mutex_unlock(&q->lock);

  return ret;
}

void queue_destroy(queue_t *q) {
  if (q == NULL)
    return;

  if (q->max_len == 0) // Uncapped
  {
    linkedlist_destroy((linkedlist_t *)q->arr);
  } else // Capped
  {
    if (q->arr != NULL)
      ufree(q->arr);
  }

  pthread_mutex_destroy(&q->lock);
  ufree(q);
}
