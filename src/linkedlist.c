#include <errno.h>

#include "dmem.h"
#include "linkedlist.h"
#include "list.h"

typedef struct linkednode linkednode;
struct linkednode {
  void *value;
  linkednode *next;
  linkednode *prev;
};

struct linkedlist {
  list_type type;

  linkednode *first;
  linkednode *last;
  size_t len;
};

// Private functions

static int __linkedlist_add(linkedlist_t *list, void *element) {
  linkednode *node = list->last;
  linkednode *newnode = (linkednode *)ualloc(sizeof(*newnode));
  if (newnode == NULL) {
    errno = ENOMEM;
    return -1;
  }

  if (node == NULL) // Empty
  {
    list->first = list->last = newnode;
    newnode->next = NULL;
    newnode->prev = NULL;
    newnode->value = element;
  } else {
    node->next = list->last = newnode;
    newnode->prev = node;
    newnode->next = NULL;
    newnode->value = element;
  }
  list->len++;
  return 0;
}

static linkednode *__linkedlist_get(linkedlist_t *list, size_t index) {
  const size_t half_len = list->len >> 1;
  linkednode *node = NULL;
  if (index > half_len) // Start from end
  {
    const size_t delta = list->len - index - 1;
    node = list->last;
    for (size_t i = 0; i < delta; i++)
      node = node->prev;
  } else // Start from beginning
  {
    node = list->first;
    for (size_t i = 0; i < index; i++)
      node = node->next;
  }
  return node;
}

static int __linkedlist_insert(linkedlist_t *list, void *element,
                               size_t index) {
  linkednode *newnode = (linkednode *)ualloc(sizeof(*newnode));
  if (newnode == NULL) {
    errno = ENOMEM;
    return -1;
  }

  newnode->value = element;
  linkednode *nodeatindex = __linkedlist_get(list, index);

  if (index == 0) {
    newnode->prev = NULL;
    newnode->next = nodeatindex;

    nodeatindex->prev = newnode;
    list->first = newnode;
  } else {
    linkednode *prevnode = nodeatindex->prev;

    newnode->prev = prevnode;
    newnode->next = nodeatindex;

    nodeatindex->prev = newnode;
    prevnode->next = newnode;
  }

  list->len++;
  return 0;
}

// Public functions

linkedlist_t *linkedlist_new(void) {
  linkedlist_t *list = (linkedlist_t *)ualloc(sizeof(*list));

  if (list == NULL) {
    errno = ENOMEM;
    return NULL;
  }

  list->first = NULL;
  list->last = NULL;
  list->len = 0UL;

  list->type = TYPE_LINKEDLIST;

  return list;
}

size_t linkedlist_length(linkedlist_t *list) {
  if (list == NULL) {
    errno = EINVAL;
    return 0;
  }

  return list->len;
}

int linkedlist_add(linkedlist_t *list, void *element) {
  if (list == NULL) {
    errno = EINVAL;
    return -1;
  }
  return __linkedlist_add(list, element);
}

int linkedlist_addall(linkedlist_t *list, void **elements, size_t nitems) {
  if (nitems == 0)
    return 0;

  if (list == NULL || elements == NULL) {
    errno = EINVAL;
    return -1;
  }

  for (size_t i = 0; i < nitems; i++)
    if (__linkedlist_add(list, elements[i]) < 0)
      return -1;
  return 0;
}

int linkedlist_insert(linkedlist_t *list, void *element, size_t index) {
  if (list == NULL) {
    errno = EINVAL;
    return -1;
  }

  if (list->len <= index) {
    errno = EINVAL;
    return -1;
  }

  return __linkedlist_insert(list, element, index);
}

int linkedlist_insertall(linkedlist_t *list, void **elements, size_t nitems,
                         size_t index) {
  if (list == NULL || elements == NULL) {
    errno = EINVAL;
    return -1;
  }

  if (list->len <= index) {
    errno = EINVAL;
    return -1;
  }

  for (size_t i = 0; i < nitems; i++)
    if (__linkedlist_insert(list, elements[i], index + i) < 0)
      return -1;
  return 0;
}

void *linkedlist_get(linkedlist_t *list, size_t index) {
  if (list == NULL) {
    errno = EINVAL;
    return NULL;
  }

  if (list->len <= index) {
    errno = EINVAL;
    return NULL;
  }

  return __linkedlist_get(list, index)->value;
}

void *linkedlist_remove(linkedlist_t *list, size_t index) {
  if (list == NULL) {
    errno = EINVAL;
    return NULL;
  }

  if (list->len <= index) {
    errno = EINVAL;
    return NULL;
  }

  linkednode *node = __linkedlist_get(list, index);
  void *value = node->value;
  linkednode *prev = node->prev, *next = node->next;

  ufree(node);

  if (prev != NULL)
    prev->next = next;
  else
    list->first = next;

  if (next != NULL)
    next->prev = prev;
  else
    list->last = prev;

  return value;
}

int linkedlist_foreach(linkedlist_t *list, void (*func)(void *, void *),
                       void *pipe) {
  if (list == NULL || *(void **)&func == NULL) {
    errno = EINVAL;
    return -1;
  }

  for (linkednode *node = list->first; node != NULL; node = node->next)
    func(node->value, pipe);

  return 0;
}

void **linkedlist_to_array(linkedlist_t *list) {
  if (list == NULL) {
    errno = EINVAL;
    return NULL;
  }

  void **arr = (void **)ualloc(sizeof(*arr) * list->len);
  if (arr == NULL) {
    errno = ENOMEM;
    return NULL;
  }

  size_t i = 0;
  for (linkednode *node = list->first; node != NULL; node = node->next)
    arr[i++] = node->value;

  return arr;
}

int linkedlist_clear(linkedlist_t *list) {
  if (list == NULL) {
    errno = EINVAL;
    return -1;
  }

  linkednode *node = list->first;
  linkednode *next;
  while (node != NULL) {
    next = node->next;
    ufree(node);
    node = next;
  }
  list->len = 0UL;
  list->first = NULL;
  list->last = NULL;
  return 0;
}

void linkedlist_destroy(linkedlist_t *list) {
  if (list == NULL)
    return;

  linkedlist_clear(list);

  ufree(list);
}
