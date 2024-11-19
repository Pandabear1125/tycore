#ifndef MACROS_H
#define MACROS_H

#ifdef __cplusplus
#define CFUNC extern "C"
#define CDATA extern "C"
#else
#define CFUNC
#define CDATA
#endif

#define WEAK __attribute__ ((weak))
#define SECTION(n) __attribute__ ((section(n), used))

#endif