#include <string.h>

#include "dmem.h"
#include "arraylist.h"

struct arraylist_t
{
  void **arr;
  size_t arr_len;
};

int arraylist_realloc(arraylist_t *list, int diff)
{
  if(diff == 0)
    return 0;

  if(
      (list->arr = (void **) urealloc(
        list->arr,
        sizeof(*list->arr) * (size_t)(list->arr_len + diff)
        )
       ) == NULL)
    return -1;
  return 0;
}

arraylist_t * arraylist_new()
{
  return arraylist_new_prealloc(0UL);
}

arraylist_t * arraylist_new_prealloc(size_t init_size)
{
  arraylist_t * list = (arraylist_t *) ualloc(sizeof(arraylist_t));
  if(list == NULL)
    return NULL;

  list->arr = NULL;
  list->arr_len = 0UL;

  if(init_size != 0UL &&
      (list->arr = (void **) ualloc(
        (list->arr_len = init_size) * sizeof(*list->arr)
      )) == NULL
    )
    return NULL;
  return list;
}

int arraylist_add(arraylist_t *list, void *item)
{
  return arraylist_addall(list, &item, 1);
}

int arraylist_addall(arraylist_t *list, void **items, size_t nitems)
{
  if(nitems == 0)
    return 0;

  if(list == NULL || items == NULL)
    return -1;

  if(arraylist_realloc(list, nitems) < 0)
    return -1;

  memmove(list->arr + list->arr_len, items, sizeof(*list->arr) * nitems);
  list->arr_len += nitems;
  return 0;
}

int arraylist_insert(arraylist_t *list, void *item, size_t index)
{
  return arraylist_insertall(list, &item, 1, index);
}

int arraylist_insertall(arraylist_t *list, void **items, size_t nitems, size_t index)
{
  if(nitems == 0)
    return 0;

  if(list == NULL || items == NULL)
    return -1;

  if(index >= list->arr_len)
    return -1;

  if(arraylist_realloc(list, nitems) < 0)
    return -1;

  memmove(list->arr + nitems, list->arr + index, sizeof(*list->arr) * (list->arr_len - index - 1));
  memmove(list->arr + index, items, sizeof(*list->arr) * nitems);
  list->arr_len += nitems;
  return 0;
}

void * arraylist_get(arraylist_t *list, size_t index)
{
  if(list == NULL)
    return NULL;
  if(index >= list->arr_len)
    return NULL;
  return list->arr[index];
}

size_t arraylist_length(arraylist_t *list)
{
  if(list == NULL)
    return 0UL;
  return list->arr_len;
}

void * arraylist_remove(arraylist_t *list, size_t index)
{
  if(list == NULL)
    return NULL;
  
  if(index >= list->arr_len)
    return NULL;

  void *tmp = list->arr[index];
  memmove(
      list->arr + index,
      list->arr + index + 1,
      sizeof(*list->arr) * (list->arr_len - index - 1)
      );
  if(arraylist_realloc(list, -1) < 0)
    return NULL;
  list->arr_len -= 1;
  return tmp;
}

int arraylist_foreach(arraylist_t *list, void (*cb)(void *))
{
  if(list == NULL || *(void **)&cb == NULL)
    return -1;

  for(size_t i = 0; i < list->arr_len; i++)
    cb(list->arr[i]);
  return 0;
}

int arraylist_clear(arraylist_t *list)
{
  if(list == NULL)
    return -1;

  if(list->arr == NULL)
    return 0;
  
  ufree(list->arr);
  list->arr = NULL;
  list->arr_len = 0UL;
  return 1;
}

void arraylist_destroy(arraylist_t *list)
{
  if(list == NULL)
    return;

  if(list->arr != NULL)
    ufree(list->arr);
  ufree(list);
}

