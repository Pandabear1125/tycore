#ifndef TYCORE_MEMORY_H
#define TYCORE_MEMORY_H

// TODO seperate flash into flash_code and flash_data
#define FLASH_CODE  __attribute__((section(".flash_code")))
#define FLASH_DATA  __attribute__((section(".flash_data")))
#define ITCM        __attribute__((section(".itcm_code")))
#define DTCM        __attribute__((section(".dtcm_data")))

#endif // TYCORE_MEMORY_H