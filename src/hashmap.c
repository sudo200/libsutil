#include <errno.h>
#include <string.h>

#include "dmem.h"
#include "hashmap.h"

#define HASHMAP_INITIAL_CAP 4UL

struct hashmap_bucket {
  void *key;
  size_t keysize;

  void *value;

  struct hashmap_bucket *next;
};

struct hashmap {
  hashfunction_t hasher;

  struct hashmap_bucket *buckets;
  size_t size;
  size_t capacity;
};

// Private functions
static void hashmap_init_buckets(struct hashmap_bucket *buckets, size_t nbuckets) {
  memset(buckets, 0, sizeof(*buckets) * nbuckets);
  for(size_t i = 0UL; i < nbuckets; ++i)
    buckets[(i - 1) % nbuckets].next = buckets + i;
}

static struct hashmap_bucket *hashmap_get_bucket(const hashmap_t *map, const void *key, size_t keysize) {
  size_t cap = map->capacity;
  hash_t hash = map->hasher(key, keysize);
  struct hashmap_bucket *b = map->buckets + (hash % map->capacity);
  for(; b != NULL; b = b->next)
    if(cap-- <= 0UL)
      return NULL;

  return b;
}

static int hashmap_realloc(hashmap_t *map) {
  size_t old_cap = map->capacity;
  struct hashmap_bucket *old_bs = map->buckets;

  map->capacity *= 2;
  if((map->buckets = (struct hashmap_bucket *)ualloc(sizeof(*map->buckets) * map->capacity)) == NULL) {
    errno = ENOMEM;
    return -1;
  }
  hashmap_init_buckets(map->buckets, map->capacity);

  for(size_t i = 0UL; i < old_cap; i++) {
    struct hashmap_bucket *old_b = old_bs + i;
    hash_t hash = map->hasher(old_bs->key, old_bs->keysize);

    struct hashmap_bucket *new_b = map->buckets + (hash % map->capacity);

    new_b->key = old_b->key;
    new_b->keysize = old_b->keysize;
    new_b->value = old_b->value;
  }

  return 0;
}

// Public functions
hashmap_t *hashmap_new(hashfunction_t hasher) {
  return hashmap_new_prealloc(hasher, HASHMAP_INITIAL_CAP);
}

hashmap_t *hashmap_new_prealloc(hashfunction_t hasher, size_t initial_cap) {
  hashmap_t *map = (hashmap_t *)ualloc(sizeof(*map));
  if(map == NULL) {
    errno = ENOMEM;
    return NULL;
  }

  map->hasher = hasher;
  map->capacity = initial_cap;
  map->size = 0UL;

  if((map->buckets = (struct hashmap_bucket *)ualloc(sizeof(*map->buckets) * map->capacity)) == NULL) {
    errno = ENOMEM;
    return NULL;
  }
  hashmap_init_buckets(map->buckets, map->capacity);

  return map;
}

int hashmap_put(hashmap_t *map, void *key, size_t keysize, void *value) {
  if(map == NULL || key == NULL) {
    errno = EINVAL;
    return -1;
  }

  if(map->size + 1 >= map->capacity)
    if(hashmap_realloc(map) < 0)
      return -1;

  hash_t hash = map->hasher(key, keysize);
  struct hashmap_bucket *b = map->buckets + (hash % map->capacity);
  for(; b->key != NULL; b = b->next);

  b->key = key;
  b->keysize = keysize;
  b->value = value;

  return 0;
}

void *hashmap_get(const hashmap_t *map, const void *key, size_t keysize) {
  if(map == NULL || key == NULL) {
    errno = EINVAL;
    return NULL;
  }

  struct hashmap_bucket *b = hashmap_get_bucket(map, key, keysize);
  if(b == NULL) {
    errno = ENOENT;
    return NULL;
  }
  return b->value;
}

size_t hashmap_size(const hashmap_t *map) {
  if(map == NULL) {
    errno = EINVAL;
    return 0UL;
  }

  return map->size;
}

bool hashmap_contains_key(const hashmap_t *map, const void *key, size_t keysize) {
  if(map == NULL || key == NULL) {
    errno = EINVAL;
    return false;
  }

  return hashmap_get_bucket(map, key, keysize) != NULL;
}

int hashmap_foreach(const hashmap_t *map, void (*cb)(void *, size_t, void *, void *), void *pipe) {
  if(map == NULL) {
    errno = EINVAL;
    return -1;
  }

  for(size_t i = 0UL; i < map->capacity; i++) {
    struct hashmap_bucket *b = map->buckets + i;
    if(b->key == NULL)
      continue;

    cb(b->key, b->keysize, b->value, pipe);
  }
  return 0;
}

int hashmap_clear(hashmap_t *map) {
  if(map == NULL) {
    errno = EINVAL;
    return -1;
  }

  ufree(map->buckets);
  map->capacity = HASHMAP_INITIAL_CAP;
  map->size = 0UL;
  if((map->buckets = (struct hashmap_bucket *)ualloc(sizeof(*map->buckets) * map->capacity)) == NULL) {
    errno = ENOMEM;
    return -1;
  }
  hashmap_init_buckets(map->buckets, map->capacity);

  return 0;
}

void *hashmap_remove(hashmap_t *map, void *key, size_t keysize) {
  if(map == NULL || key == NULL) {
    errno = EINVAL;
    return NULL;
  }

  struct hashmap_bucket *b = hashmap_get_bucket(map, key, keysize);
  if(b == NULL) {
    errno = ENOENT;
    return NULL;
  }

  void *value = b->value;
  b->key = NULL;
  b->value = NULL;
  b->keysize = 0UL;
  return value;
}

void hashmap_destroy(hashmap_t *map) {
  if(map == NULL)
    return;

  ufree(map->buckets);
}

