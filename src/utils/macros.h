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
#define UNUSED __attribute__ ((unused))

// #ifdef __cplusplus
// extern "C" {
// #endif  // __cplusplus extern "C"

// #ifdef __cplusplus
// }
// #endif  // __cplusplus extern "C"

#endif
