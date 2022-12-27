#include <errno.h>
#include <string.h>

#include "dmem.h"
#include "hashmap.h"

struct hashmap_bucket {
  void *key;
  size_t keysize;

  void *value;
};

struct hashmap {
  hashfunction_t hasher;

  struct hashmap_bucket *buckets;
  size_t size;
  size_t capacity;
};

