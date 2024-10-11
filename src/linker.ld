/* Defined memory regions of the processor */
MEMORY {
    /* On-chip, on-dye memory */
    /* ITCM, DTCM, and OCRAM1 share the same 512K space */
    /* This space is sectioned off into 16 32KB blocks */
    ITCM    :   ORIGIN = 0x00000000,    LENGTH = 512K
    DTCM    :   ORIGIN = 0x20000000,    LENGTH = 512K
    OCRAM1  :   ORIGIN = 0x20280000,    LENGTH = 512K

    /* On-chip, off-dye 512KB SRAM memory */
    OCRAM2  :   ORIGIN = 0x20200000,    LENGTH = 512K

    /* Flash memory. mimxrt1060 supports 256MB but Teensy4.1 only has a 8MB flash chip */
    FLEXSPI :   ORIGIN = 0x60000000,    LENGTH = 8M

    /* External memory. mimxrt1060 supports 240MB but Teensy4.1 only has 2 slots for 8MB chips */
    FLEXSPI2:   ORIGIN = 0x70000000,    LENGTH = 16M
}

/* Defined entry point */
/* Since we boot from flash (FLEXSPI NOR), the bootloader looks at address 0x60000000 */
/* It must find the flash config here */
/* This ENTRY command is somewhat pointless, all it does is stop the linker from complaining there is no _start defined */
ENTRY(ResetVector)

/* Defined elf sections */
SECTIONS {
    
}