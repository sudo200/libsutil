#include <errno.h>
#include <string.h>

#include "hashset.h"
#include "dmem.h"
#include "set.h"

#define HASHSET_INITIAL_CAPACITY  4UL

#define memquals(x, y, s) (memcmp(x, y, s) == 0)

struct hashset_bucket {
  void *item;
  size_t item_size;
  struct hashset_bucket *next;
};

struct hashset {
  set_type type; // This has to be the 1st member.
 
  hashfunction_t hasher;
  struct hashset_bucket *buckets;
  size_t size;
  size_t capacity;
};

// Private functions
static void hashset_link_buckets(hashset *set) {
  for(size_t i = 0UL; i < set->capacity; i++)
    set->buckets[(i-1)%set->capacity].next = &set->buckets[i];
}

static struct hashset_bucket *hashset_get_bucket(hashset *set, const void *item, size_t size) {
  if(size == 0UL)
    return NULL;
  const hash_t hash = set->hasher(item, size);
 
  struct hashset_bucket *bucket = &set->buckets[hash % set->capacity];
  for(size_t i = 0UL; i < set->capacity; i++, bucket = bucket->next) {
    if(bucket->item_size != size || bucket->item == NULL) // Check length
      continue;

    if(memquals(bucket->item, item, size))
      return bucket;
  }

  return NULL;
}

static bool hashset_realloc(hashset *set) {
  

  return true;
}

// Public function
hashset *hashset_new_prealloc(size_t initial_cap, hashfunction_t hasher) {
  if(initial_cap <= 0UL) {
    errno = EINVAL;
    return NULL;
  }

  hashset *set = (hashset *)ualloc(sizeof(*set));
  if(set == NULL) {
    errno = ENOMEM;
    return NULL;
  }

  set->type = TYPE_HASHSET;

  set->hasher = hasher;
  set->capacity = initial_cap;
  set->size = 0UL;
  set->buckets = (struct hashset_bucket *)ualloc(sizeof(*set->buckets) * set->capacity);

  if(set->buckets == NULL) {
    errno = ENOMEM;
    return NULL;
  }

  memset(set->buckets, 0, sizeof(*set->buckets) * set->capacity);
  hashset_link_buckets(set);

  return set;
}

hashset *hashset_new(hashfunction_t hasher) {
  return hashset_new_prealloc(HASHSET_INITIAL_CAPACITY, hasher);
}

size_t hashset_size(const hashset *set) {
  if(set == NULL) {
    errno = EINVAL;
    return 0UL;
  }

  return set->size;
}

int hashset_add(hashset *set, void *item, size_t size) {
  if(set == NULL || item == NULL || size == 0UL) {
    errno = EINVAL;
    return -1;
  }

  if(set->capacity <= (set->size + 1))
    if(!hashset_realloc(set)) {
      errno = ENOMEM;
      return -1;
    }

  struct hashset_bucket *bucket = &set->buckets[set->hasher(item ,size) % set->capacity];
  for(size_t i = 0UL; bucket->item != NULL && i < set->capacity; i++)
    bucket = bucket->next;
  
  bucket->item = item;
  bucket->item_size = size;
  set->size++;

  return 0;
}

int hashset_clear(hashset *set) {
  if(set == NULL) {
    errno = EINVAL;
    return -1;
  }

  ufree(set->buckets);
  set->size = 0UL;
  set->capacity = HASHSET_INITIAL_CAPACITY;

  if((set->buckets = ualloc(sizeof(*set->buckets) * set->capacity)) == NULL) {
    errno = ENOMEM;
    return -1;
  }
  hashset_link_buckets(set);

  return 0;
}

void *hashset_remove(hashset *set, void *item, size_t size) {
  if(set == NULL || item == NULL) {
    errno = EINVAL;
    return NULL;
  }

  struct hashset_bucket *bucket = hashset_get_bucket(set, item, size);
  if(bucket == NULL) {
    errno = ENOENT;
    return NULL;
  }

  void *old = bucket->item;
  bucket->item = NULL;
  bucket->item_size = 0UL;
  set->size--;
  
  return old;
}

int hashset_foreach(hashset *set, void (*cb)(void *, size_t, void *), void *pipe) {
  if(set == NULL || *(void **)&cb == NULL) {
    errno = EINVAL;
    return -1;
  }

  for(size_t i = 0UL; i < set->capacity; i++) {
    struct hashset_bucket *const b = &set->buckets[i];
    if(b->item == NULL || b->item_size == 0UL)
      continue;
    cb(b->item, b->item_size, pipe);
  }

  return 0;
}

bool hashset_contains(hashset *set, const void *item, size_t size) {
  if(set == NULL || item == NULL) {
    errno = EINVAL;
    return false;
  }

  return hashset_get_bucket(set, item, size) != NULL;
}

void hashset_destroy(hashset *set) {
  if(set == NULL)
    return;

  ufree(set->buckets);
  ufree(set);
}
