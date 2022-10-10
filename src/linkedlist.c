#include "dmem.h"

#include "linkedlist.h"

typedef struct linkednode linkednode;
struct linkednode
{
  void * value;
  linkednode * next;
  linkednode * prev;
};

struct linkedlist
{
  linkednode * first;
  linkednode * last;
  size_t len;
};


linkedlist * linkedlist_new(void)
{
  linkedlist * list = (linkedlist *)ualloc(sizeof(linkedlist));
  list->first = list->last = NULL;
  list->len = 0;
  return list;
}

size_t linkedlist_length(linkedlist * list)
{
  if(list == NULL)
    return 0;

  return list->len;
}

linkedlist * linkedlist_add(linkedlist * list, void * element)
{
  if(list == NULL)
    return NULL;

  linkednode * node = list->first;

  if(node == NULL) // Empty
  {
    node = list->first = list->last = (linkednode *)ualloc(sizeof(linkednode));
    node->value = element;
    node->next = NULL;

    list->len = list->len + 1;
    return list;
  }

  for(size_t i = 0; i < list->len; i++)
    node = node->next;

  node = list->last = node->next = (linkednode *)ualloc(sizeof(linkednode));
  node->value = element;
  node->next = NULL;


  list->len = list->len + 1;
  return list;
}

void * linkedlist_get(linkedlist * list, size_t index)
{
  if(list == NULL)
    return NULL;

  if(list->len >= index)
    return NULL;

  linkednode * node = list->first;
  if(node == NULL)
    return NULL;

  for(size_t i = 0; i < index; ++i)
    node = node->next;

  return node->value;
}

void * linkedlist_remove(linkedlist * list, size_t index)
{
  if(list == NULL)
    return NULL;

  linkednode * node = list->first;

  if(node == NULL)
    return NULL;

  linkednode * lastnode = node;
  node = node->next;

  if(node == NULL)
    return NULL;

  if(index == 0)
  {
      linkednode * node1 = list->first;
      list->first = node1->next;
      void * value = node1->value;
      ufree(node1);
      return value;
  }

  if(list->len <= index)
    return NULL;

  for(size_t i = 0; i < (index - 1); ++i)
  {
      lastnode = node;
      node = node->next;
  }

  void * value = node->value;
  lastnode->next = node->next;

  ufree(node);
  return value;
}

linkedlist * linkedlist_foreach(linkedlist * list, void (*func)(void *))
{
    if(list == NULL)
        return NULL;

    if(func == NULL)
        return list;

    if(list->first == NULL)
        return list;

    for(linkednode * node = list->first; node; node = node->next)
        func(node->value);
    return list;
}

void linkedlist_destroy(linkedlist * list)
{
    if(list == NULL)
        return;

    do {
      if(list->first == NULL)
        break;

      linkednode *nextnode = list->first, *node = nextnode;
      while((node = nextnode))
      {
        nextnode = node->next;
        ufree(node);
      }
    }
    while(0);

    ufree(list);
}
