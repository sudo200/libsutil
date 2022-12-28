#include <errno.h>
#include <string.h>

#include "arraylist.h"
#include "dmem.h"
#include "list.h"

#define ARRAYLIST_INITIAL_CAPACITY 4UL

struct arraylist {
  list_type type; // This has to be the 1st member.

  void **arr;
  size_t len;
  size_t capacity;
};

// Private functions
static int arraylist_realloc(arraylist_t *list) {

  list->capacity *= 2;
  if ((list->arr = (void **)urealloc(list->arr, sizeof(*list->arr) *
                                                    list->capacity)) == NULL) {
    errno = ENOMEM;
    return -1;
  }
  return 0;
}

// Public functions
arraylist_t *arraylist_new_prealloc(size_t initial_cap) {
  if (initial_cap <= 0UL) {
    errno = EINVAL;
    return NULL;
  }

  arraylist_t *list = (arraylist_t *)ualloc(sizeof(arraylist_t));
  if (list == NULL) {
    errno = ENOMEM;
    return NULL;
  }

  list->type = TYPE_ARRAYLIST;

  list->arr = (void **)ualloc(sizeof(*list->arr) * initial_cap);
  list->len = 0UL;
  list->capacity = initial_cap;

  return list;
}

arraylist_t *arraylist_new(void) {
  return arraylist_new_prealloc(ARRAYLIST_INITIAL_CAPACITY);
}

int arraylist_add(arraylist_t *list, void *item) {
  return arraylist_addall(list, &item, 1);
}

int arraylist_addall(arraylist_t *list, void **items, size_t nitems) {
  if (nitems == 0)
    return 0;

  if (list == NULL || items == NULL) {
    errno = EINVAL;
    return -1;
  }

  if (arraylist_realloc(list) < 0)
    return -1;

  memmove(list->arr + list->len, items, sizeof(*list->arr) * nitems);
  list->len += nitems;
  return 0;
}

int arraylist_insert(arraylist_t *list, void *item, size_t index) {
  return arraylist_insertall(list, &item, 1, index);
}

int arraylist_insertall(arraylist_t *list, void **items, size_t nitems,
                        size_t index) {
  if (nitems == 0)
    return 0;

  if (list == NULL || items == NULL) {
    errno = EINVAL;
    return -1;
  }

  if (index >= list->len) {
    errno = EINVAL;
    return -1;
  }

  if (arraylist_realloc(list) < 0)
    return -1;

  memmove(list->arr + nitems + index, list->arr + index,
          sizeof(*list->arr) * (list->len - index - 1));
  memmove(list->arr + index, items, sizeof(*list->arr) * nitems);
  list->len += nitems;
  return 0;
}

void *arraylist_get(const arraylist_t *list, size_t index) {
  if (list == NULL) {
    errno = EINVAL;
    return NULL;
  }

  if (index >= list->len) {
    errno = EINVAL;
    return NULL;
  }

  return list->arr[index];
}

size_t arraylist_length(const arraylist_t *list) {
  if (list == NULL) {
    errno = EINVAL;
    return 0UL;
  }

  return list->len;
}

void *arraylist_remove(arraylist_t *list, size_t index) {
  if (list == NULL) {
    errno = EINVAL;
    return NULL;
  }

  if (index >= list->len) {
    errno = EINVAL;
    return NULL;
  }

  void *tmp = list->arr[index];
  memmove(list->arr + index, list->arr + index + 1,
          sizeof(*list->arr) * (list->len - index - 1));

  list->len -= 1;
  return tmp;
}

int arraylist_foreach(arraylist_t *list, void (*cb)(void *, void *),
                      void *pipe) {
  if (list == NULL || *(void **)&cb == NULL) {
    errno = EINVAL;
    return -1;
  }

  for (size_t i = 0; i < list->len; i++)
    cb(list->arr[i], pipe);
  return 0;
}

void **arraylist_to_array(arraylist_t *list) {
  if (list == NULL) {
    errno = EINVAL;
    return NULL;
  }

  void **arr = (void **)ualloc(sizeof(*arr) * list->len);
  if (arr == NULL) {
    errno = ENOMEM;
    return NULL;
  }

  return memcpy(arr, list->arr, sizeof(*arr) * list->len);
}

int arraylist_clear(arraylist_t *list) {
  if (list == NULL) {
    errno = EINVAL;
    return -1;
  }

  ufree(list->arr);

  list->capacity = ARRAYLIST_INITIAL_CAPACITY;
  list->arr = (void **)ualloc(sizeof(*list->arr) * list->capacity);
  list->len = 0UL;
  return 0;
}

void arraylist_destroy(arraylist_t *list) {
  if (list == NULL)
    return;

  ufree(list->arr);
  ufree(list);
}
