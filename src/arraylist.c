#include <errno.h>
#include <string.h>

#include "arraylist.h"
#include "dmem.h"

struct arraylist {
  void **arr;
  size_t arr_len;
};

// Private functions
static int arraylist_realloc(arraylist *list, int diff) {
  if (diff == 0)
    return 0;

  if ((list->arr = (void **)urealloc(
           list->arr, sizeof(*list->arr) * (size_t)(list->arr_len + diff))) ==
      NULL) {
    errno = ENOMEM;
    return -1;
  }
  return 0;
}

// Public functions
arraylist *arraylist_new(void) {
  arraylist *list = (arraylist *)ualloc(sizeof(arraylist));
  if (list == NULL) {
    errno = ENOMEM;
    return NULL;
  }

  list->arr = NULL;
  list->arr_len = 0UL;

  return list;
}

int arraylist_add(arraylist *list, void *item) {
  return arraylist_addall(list, &item, 1);
}

int arraylist_addall(arraylist *list, void **items, size_t nitems) {
  if (nitems == 0)
    return 0;

  if (list == NULL || items == NULL) {
    errno = EINVAL;
    return -1;
  }

  if (arraylist_realloc(list, nitems) < 0)
    return -1;

  memmove(list->arr + list->arr_len, items, sizeof(*list->arr) * nitems);
  list->arr_len += nitems;
  return 0;
}

int arraylist_insert(arraylist *list, void *item, size_t index) {
  return arraylist_insertall(list, &item, 1, index);
}

int arraylist_insertall(arraylist *list, void **items, size_t nitems,
                        size_t index) {
  if (nitems == 0)
    return 0;

  if (list == NULL || items == NULL) {
    errno = EINVAL;
    return -1;
  }

  if (index >= list->arr_len) {
    errno = ELNRNG;
    return -1;
  }

  if (arraylist_realloc(list, nitems) < 0)
    return -1;

  memmove(list->arr + nitems + index, list->arr + index,
          sizeof(*list->arr) * (list->arr_len - index - 1));
  memmove(list->arr + index, items, sizeof(*list->arr) * nitems);
  list->arr_len += nitems;
  return 0;
}

void *arraylist_get(arraylist *list, size_t index) {
  if (list == NULL) {
    errno = EINVAL;
    return NULL;
  }

  if (index >= list->arr_len) {
    errno = ELNRNG;
    return NULL;
  }

  return list->arr[index];
}

size_t arraylist_length(arraylist *list) {
  if (list == NULL) {
    errno = EINVAL;
    return 0UL;
  }

  return list->arr_len;
}

void *arraylist_remove(arraylist *list, size_t index) {
  if (list == NULL) {
    errno = EINVAL;
    return NULL;
  }

  if (index >= list->arr_len) {
    errno = ELNRNG;
    return NULL;
  }

  void *tmp = list->arr[index];
  memmove(list->arr + index, list->arr + index + 1,
          sizeof(*list->arr) * (list->arr_len - index - 1));

  if (arraylist_realloc(list, -1) < 0)
    return NULL;

  list->arr_len -= 1;
  return tmp;
}

int arraylist_foreach(arraylist *list, void (*cb)(void *, void *), void *pipe) {
  if (list == NULL || *(void **)&cb == NULL) {
    errno = EINVAL;
    return -1;
  }

  for (size_t i = 0; i < list->arr_len; i++)
    cb(list->arr[i], pipe);
  return 0;
}

void **arraylist_to_array(arraylist *list) {
  if (list == NULL) {
    errno = EINVAL;
    return NULL;
  }

  void **arr = (void **) ualloc(sizeof(*arr) * list->arr_len);
  if (arr == NULL) {
    errno = ENOMEM;
    return NULL;
  }

  return memcpy(arr, list->arr, sizeof(*arr) * list->arr_len);
}

int arraylist_clear(arraylist *list) {
  if (list == NULL) {
    errno = EINVAL;
    return -1;
  }

  if (list->arr == NULL)
    return 0;

  ufree(list->arr);
  list->arr = NULL;
  list->arr_len = 0UL;
  return 0;
}

void arraylist_destroy(arraylist *list) {
  if (list == NULL)
    return;

  if (list->arr != NULL)
    ufree(list->arr);
  ufree(list);
}
