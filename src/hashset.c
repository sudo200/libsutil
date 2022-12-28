#include <errno.h>

#include "hashset.h"

#include "dmem.h"
#include "hashmap.h"
#include "set.h"

struct hashset {
  set_type type; // Top member

  hashmap_t *map;
};

// Private functions
__attribute__((always_inline)) static hashset_t *hashset_alloc_struct(void) {
  hashset_t *set = (hashset_t *)ualloc(sizeof(*set));

  if (set == NULL) {
    errno = ENOMEM;
    return NULL;
  }

  set->type = TYPE_HASHSET;

  return set;
}

typedef struct {
  void (*real_cb)(void *, size_t, void *);
  void *pipe;
} pipe_struct;

static void cb_helper(void *key, size_t keylen, void *val, void *pipe) {
  pipe_struct *struc = (pipe_struct *)pipe;
  struc->real_cb(key, keylen, struc->pipe);
}

// Public functions
hashset_t *hashset_new_prealloc(size_t initial_cap, hashfunction_t hasher) {
  hashset_t *set = hashset_alloc_struct();
  if (set == NULL)
    return NULL;

  if ((set->map = hashmap_new_prealloc(hasher, initial_cap)) == NULL)
    return NULL;

  return set;
}

hashset_t *hashset_new(hashfunction_t hasher) {
  hashset_t *set = hashset_alloc_struct();
  if (set == NULL)
    return NULL;

  if ((set->map = hashmap_new(hasher)) == NULL)
    return NULL;

  return set;
}

size_t hashset_size(const hashset_t *set) {
  if (set == NULL) {
    errno = EINVAL;
    return 0UL;
  }

  return hashmap_size(set->map);
}

int hashset_add(hashset_t *set, void *item, size_t size) {
  if (set == NULL || item == NULL) {
    errno = EINVAL;
    return -1;
  }

  return hashmap_put(set->map, item, size, NULL);
}

int hashset_clear(hashset_t *set) {
  if (set == NULL) {
    errno = EINVAL;
    return -1;
  }

  return hashmap_clear(set->map);
}

bool hashset_remove(hashset_t *set, void *item, size_t size) {
  if (set == NULL) {
    errno = EINVAL;
    return false;
  }

  errno = 0;
  hashmap_remove(set->map, item, size);
  return errno == 0;
}

int hashset_foreach(const hashset_t *set, void (*cb)(void *, size_t, void *),
                    void *pipe) {
  if (set == NULL || *(void **)&cb == NULL) {
    errno = EINVAL;
    return -1;
  }
  pipe_struct struc = {
      .pipe = pipe,
      .real_cb = cb,
  };
  return hashmap_foreach(set->map, cb_helper, &struc);
}

bool hashset_contains(const hashset_t *set, const void *item, size_t size) {
  if (set == NULL) {
    errno = EINVAL;
    return false;
  }

  return hashmap_contains_key(set->map, item, size);
}

void hashset_destroy(hashset_t *set) {
  if (set == NULL)
    return;

  hashmap_destroy(set->map);
  ufree(set);
}
