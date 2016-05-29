#ifndef RAYTRACING_DEBUG_HEADER_
#define RAYTRACING_DEBUG_HEADER_

/*
 *  This file implement, debug printing utilities
 */

#define DEBUG_MODE 1

#if DEBUG_MODE
#   include <cstdio>
#   define DEBUG(X) printf(X "\n")
#   define FDEBUG(str, ...) printf(str "\n",  __VA_ARGS__)
#   define DEBUG_VAR(x, str, ...) printf(#x ": " str "\n", __VA_ARGS__)
#else
#   define DEBUG(X)
#   define FDEBUG(str, ...)
#   define DEBUG_VAR(x, str, ...)
#endif

#endif
