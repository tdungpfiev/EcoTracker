#ifndef _WRAPPERS_HPP_
#define _WRAPPERS_HPP_
#include <stdlib.h>

// platform independent aligned memory allocation (see also alFree)
void* alMalloc( size_t size, int alignment );

// platform independent alignned memory de-allocation (see also alMalloc)
void alFree(void* aligned);

#endif
