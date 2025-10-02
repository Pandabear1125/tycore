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

// Full data-synchronization barrier
// Ensures all pipelined memory accesses are completed
#define DSB() __asm__ __volatile__ ("dsb" : : : "memory")

// Data memory barrier
// Ensures ordering of memory accesses but does not wait for completion
#define DMB() __asm__ __volatile__ ("dmb" : : : "memory")

// Instruction synchronization barrier
// Ensures all pipelined instructions are completed
#define ISB() __asm__ __volatile__ ("isb" : : : "memory")

// Compiler barrier
// Prevents compiler from reordering memory accesses across this point
#define COMPILER_BARRIER() __asm__ __volatile__ ("" : : : "memory")

// Wait for interrupt
#define WFI() __asm__ __volatile__ ("wfi" : : : "memory")
// Wait for event
#define WFE() __asm__ __volatile__ ("wfe" : : : "memory")
// Send event
#define SEV() __asm__ __volatile__ ("sev" : : : "memory")
// No operation
#define NOP() __asm__ __volatile__ ("nop" : : : "memory")

// Enable interrupts
#define ENABLE_INTERRUPTS() __asm__ __volatile__ ("cpsie i" : : : "memory")
// Disable interrupts
#define DISABLE_INTERRUPTS() __asm__ __volatile__ ("cpsid i" : : : "memory")

// Enable faults
#define ENABLE_FAULTS() __asm__ __volatile__ ("cpsie f" : : : "memory")
// Disable faults
#define DISABLE_FAULTS() __asm__ __volatile__ ("cpsid f" : : : "memory")

// #ifdef __cplusplus
// extern "C" {
// #endif  // __cplusplus extern "C"

// #ifdef __cplusplus
// }
// #endif  // __cplusplus extern "C"

#endif
