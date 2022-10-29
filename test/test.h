#ifndef ___TEST_H__
#define ___TEST_H__

#include <assert.h>

#define test(name, exp) if(!(exp))  __assert(name, __FILE__, __LINE__);

#endif //___TEST_H__
