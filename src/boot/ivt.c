// RM 9.7 p.256

// we expect the IVT to live 0x1000 bytes offset from the first flash address since were booting
// from FlexSPI NOR (the external serial chip)

#include <stdint.h>

#include "../utils/macros.h"

// prevent optimization since this is critical boot code
#pragma GCC optimize("O0")

CFUNC void reset_vector(void);

extern const uint32_t image_vector_table[];
extern const uint32_t boot_data[];
extern const uint8_t  dcd[];
extern const uint32_t csf[];    // unused
extern const uint32_t serial_nor_configuration[];

// the Image Vector Table entry
// RM 9.7.1.1
SECTION(".ivt") const uint32_t image_vector_table[8] = {
    /* header   */ 0x412000D1,                      // VERSION|LENGTH|TAG, it must be in little endian
    /* entry    */ (uint32_t)&reset_vector,         // the address of the first instruction
    /* reserved */ 0x00000000,
    /* DCD      */ (uint32_t)dcd,                   // the address of the Device Configuration Data
    /* bootdata */ (uint32_t)boot_data,             // the address of the boot data
    /* self     */ (uint32_t)image_vector_table,    // the address of the Image Vector Table (itself)
    /* CSF      */ 0x00000000,                      // the address of the Command Sequence File used by High-Assurance Boot
    /* reserved */ 0x00000000
};

// the length of the flash image, derrived form the linker
extern uint32_t __ld_image_length;

// the boot data entry
// RM 9.7.1.2
SECTION(".boot_data") const uint32_t boot_data[3] = {
    /* start  */ 0x60000000,                        // the address of the start of the image (start of flash)
    /* length */ (uint32_t)&__ld_image_length,      // the total size of the image  
    /* plugin */ 0x00000000                         // any plugin flags
};

// the Device Configuration Data entry
// RM 9.7.2
SECTION(".dcd") const uint8_t dcd[1768] = {
    /* header */ 0xD2, 0x00, 0x04, 0x41,
    /* write  */ // ...
    /* check  */ // ...
};

// the Command Sequence File used by the High-Assurance Boot
// RM 9.12
// currently unused
SECTION(".csf") const uint32_t csf[128] = { 0 };

// the Serial NOR FlexSPI configuration entry
// RM 9.6.3
// RM 9.6.3.3
SECTION(".serial_nor_fcfb") const uint32_t serial_nor_configuration[] = {
    // FlexSPI NOR common memory configuration block

/* 0x000 : tag                      */  0x42464346,
/* 0x004 : version                  */  0x56010000,
/* 0x008 : reserved                 */  0x00000000, 
/* 0x00C : readSampleClkSrc         */ 
/* 0x00D : csHoldTime               */
/* 0x00E : csSetupTime              */                  // columnAddressWidth   |   csSetupTime |   csHoldTime  |   readSampleClkSrc
/* 0x00F : columnAdressWidth        */  0x00030301,     // other devices        | default value | default value | loopback from DQS pad
/* 0x010 : deviceModeCfgEnable      */
/* 0x011 : reserved                 */                  // waitTimeCfgCommands  |   reserved    | deviceModeCfgEnable
/* 0x012 : waitTimeCfgCommands      */  0x00000000,     // use read status      | reserved      | disabled
/* 0x014 : deviceModeSeq            */  0x00000000,     // no LUT sequences (DMCE disabled) | no LUT index (DMCE disabled) | must be 0
/* 0x018 : deviceModeArg            */  0x00000000,     // DMCE disabled
/* 0x01C : configCmdEnable          */
/* 0x01D : reserved                 */  0x00000000,     // reserved | CCE disabled
/* 0x020 : configCmdSeqs            */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,     // CCE disabled
/* 0x02C : reserved                 */  0x00000000,
/* 0x030 : cfgCmdArgs               */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,     // CCE disabled
/* 0x03C : reserved                 */  0x00000000, 
/* 0x040 : controllerMiscOption     */  0x00000000,     // no specific options
/* 0x044 : deviceType               */
/* 0x045 : sflashPadType            */
/* 0x046 : serialClkFreq            */                  // lutCustomSeqEnable   |   serialClkFreq   |   sflashPadType   |   deviceType  
/* 0x047 : lutCustomSeqEnable       */  0x00080401,     // use predefined       |   133MHz          |   quad pads       |   Serial NOR
/* 0x048 : reserved                 */  0x00000000,
/*       :                          */  0x00000000,
/* 0x050 : sflashA1Size             */  0x00800000,     // 8MB
/* 0x054 : sflashA2Size             */  0x00000000, 
/* 0x058 : sflashB1Size             */  0x00000000,
/* 0x05C : sflashB2Size             */  0x00000000,
/* 0x060 : csPadSettingOverride     */  0x00000000,     // not supported
/* 0x064 : sclkPadSettingOverride   */  0x00000000,     // not supported
/* 0x068 : dataPadSettingOverride   */  0x00000000,     // not supported
/* 0x06C : dqsPadSettingOverride    */  0x00000000,     // not supported
/* 0x070 : timoutInMs               */  0x00000000,     // no timeout
/* 0x074 : commandInterval          */  0x00000000,     // only for SPI NAND
/* 0x078 : dataValidTime            */  0x00000000,     // not needed
/* 0x07C : busyOffset               */                  // busyBitPolarity  |   busyOffset
/* 0x07E : busyBitPolarity          */  0x00000000,     // 1 if busy        |   no offset
/* 0x080 : lookupTable              */  0x0A1804EB,     // 0
/*       :                          */  0x26043206,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x24040405,     // 4
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,     // 8
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000406,     // 12
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,     // 16
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x08180420,     // 20
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,     // 24
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,     // 28
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x081804D8,     // 32
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x08180402,     // 36
/*       :                          */  0x00002004,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,     // 40
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000460,     // 44
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,     // 48
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,     // 52
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,     // 56
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,     // 60
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,     // end LUT
/* 0x180 : lutCustomSeq             */  0x00000000,     // Read
/*       :                          */  0x00000000,     // ReadStatus
/*       :                          */  0x00000000,     // WriteEnable
/*       :                          */  0x00000000,     // EraseSector
/*       :                          */  0x00000000,     // PageProgram
/*       :                          */  0x00000000,     // ChipErase
/*       :                          */  0x00000000,     // Dummy
/*       :                          */  0x00000000,     // Reserved
/*       :                          */  0x00000000,     // ?
/*       :                          */  0x00000000,     // ?
/*       :                          */  0x00000000,     // ?
/*       :                          */  0x00000000,     // ?
/* 0x1B0 : reserved                 */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,

// Serial NOR configuration block

/* 0x1C0 : pageSize                 */  0x00000100,
/* 0x1C4 : sectorSize               */  0x00001000,
/* 0x1C8 : ipCmdSerialClkFreq       */  0x00000001,              // 30MHz
/* 0x1CC : reserved                 */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000,
/*       :                          */  0x00000000
};
