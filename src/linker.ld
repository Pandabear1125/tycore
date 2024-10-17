/* Defined memory regions of the processor */
MEMORY {
    /* On-chip, on-dye memory */
    /* ITCM, DTCM, and OCRAM1 share the same 512K space */
    /* This space is sectioned off into 16 32KB blocks */
    ITCM        :   ORIGIN = 0x00000000,    LENGTH = 512K
    DTCM        :   ORIGIN = 0x20000000,    LENGTH = 512K
    OCRAM1      :   ORIGIN = 0x20280000,    LENGTH = 512K

    /* On-chip, off-dye 512KB SRAM memory */
    OCRAM2      :   ORIGIN = 0x20200000,    LENGTH = 512K

    /* Flash memory. mimxrt1060 supports 256MB but Teensy4.1 only has a 8MB flash chip */
    FLEXSPI     :   ORIGIN = 0x60000000,    LENGTH = 8M

    /* External memory. mimxrt1060 supports 240MB but Teensy4.1 only has 2 slots for 8MB chips */
    FLEXSPI2    :   ORIGIN = 0x70000000,    LENGTH = 16M
}

/* Defined entry point */
/* Since we boot from flash (FLEXSPI NOR), the bootloader looks at address 0x60000000 */
/* It must find the flash config here */
/* This ENTRY command is somewhat pointless, all it does is stop the linker from complaining there is no _start defined */
ENTRY(reset_vector)

/* Defined elf sections */
SECTIONS {
    .boot (READONLY) : {
        __ld_image_start = .;
        __ld_boot_start = .;
        KEEP(*(.serial_nor_fcfb))
        KEEP(*(.boot_data))
        KEEP(*(.dcd))
        KEEP(*(.csf))
        FILL(0x58)
        . = ALIGN(0x1000);
        KEEP(*(.ivt))
        KEEP(*(.reset_vector))
        __ld_boot_end = .;
    } > FLEXSPI

    .init : {
        KEEP(*(.init*))
        __ld_preinit_array_start = .;
        KEEP(*(.preinit_array*))
        __ld_preinit_array_end = .;
        __ld_init_array_start = .;
        KEEP(*(.init_array*))
        __ld_init_array_end = .;
        KEEP(*(.fini*))
    } > FLEXSPI

    .itcm (READONLY) : {
        __ld_itcm_start = .;
        *(.text*)
        __ld_itcm_end = .;
    } > ITCM AT > FLEXSPI

    .dtcm : {
        __ld_dtcm_start = .;
        *(.data*)
        *(.rodata*)
        *(.bss*)
        *(COMMON*)   /* this might be useless since COMMON only exists in .o files */
        __ld_dtcm_end = .;
    } > DTCM AT > FLEXSPI

    .ocram : {
        __ld_ocram_start = .;
        __ld_ocram_end = .;
    } > OCRAM1 AT > FLEXSPI

    .ARM : {
        *(.ARM.*)
    } > FLEXSPI

    .debug : {
        *(.debug*)
        *(.comment*)
    } > FLEXSPI

    .end (READONLY) : {
        __ld_image_end = .;
    } > FLEXSPI

    .all : {
        *(*)
    } > OCRAM2
    ASSERT(SIZEOF(.all) == 0, "Something was placed in .all!")

    __ld_image_length = __ld_image_end - __ld_image_start;
}
