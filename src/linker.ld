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
    /* All sections required for the processor to boot properly */
    .boot (READONLY) : {
        __ld_image_start = .;
        KEEP(*(.serial_nor_fcfb))
        KEEP(*(.boot_data))
        KEEP(*(.dcd))
        KEEP(*(.csf))
        FILL(0x58)
        . = ALIGN(0x1000);
        KEEP(*(.ivt))
        KEEP(*(.reset_vector))
        . = ALIGN(0x10);
    } > FLEXSPI

    /* All sections required for C/C++ initialization */
    .init (READONLY) : {
        KEEP(*(.init))
        __preinit_array_start = .;  /* must be called this for libc_init_array() to work */
        KEEP(*(.preinit_array))
        __preinit_array_end = .;    /* must be called this for libc_init_array() to work */
        __init_array_start = .;     /* must be called this for libc_init_array() to work */
        KEEP(*(.init_array))
        __init_array_end = .;       /* must be called this for libc_init_array() to work */
        /* TODO: actually use fini_array */
        KEEP(*(.fini))
        __fini_array_start = .;
        KEEP(*(.fini_array))
        __fini_array_end = .;
        . = ALIGN(0x10);
    } > FLEXSPI

    /* All "flash" sections */
    .flash : {
        *(.flash_code)
        *(.flash_data)
    } > FLEXSPI

    /* All code to be placed into the ITCM */
    .itcm (READONLY) : {
        *(.itcm_code)
        *(.text*)
        . = ALIGN(0x10);
    } > ITCM AT > FLEXSPI

    __ld_itcm_start = ADDR(.itcm);
    __ld_itcm_load = LOADADDR(.itcm);
    __ld_itcm_size = SIZEOF(.itcm);

    /* All data to be placed into the DTCM */
    .dtcm : {
        *(.interrupt_vector)
        *(.dtcm_data)
        *(.data*)
        *(.rodata*)
        /* TODO: these probably should be placed in FLEXSPI */
        . = ALIGN(0x10);
    } > DTCM AT > FLEXSPI

    __ld_dtcm_start = ADDR(.dtcm);
    __ld_dtcm_load = LOADADDR(.dtcm);
    __ld_dtcm_size = SIZEOF(.dtcm);

    .bss : {
        *(.bss*)
        *(COMMON*)      /* this might be useless since COMMON only exists in .o files */
    } > DTCM

    __ld_bss_start = ADDR(.bss);
    __ld_bss_size = SIZEOF(.bss);

    /* All data pre-allocated to exist within the OCRAM */
    .ocram : {
        . = ALIGN(0x10);
    } > OCRAM1 AT > FLEXSPI

    /* All ARM symbol information */
    .ARM : {
        *(.ARM.*)
    } > ITCM AT > FLEXSPI   /* must go in ITCM since most functions will be called in this "area" */

    /* All debug symbol information */
    .debug : {
        *(.debug*)
        *(.comment*)
    } > FLEXSPI

    /* Exists to find the end of the flash image */
    .end (READONLY) : {
        __ld_image_end = .;
    } > FLEXSPI

    /* Any sections that have not been placed */
    .all : {
        *(*)
    } > OCRAM2
    ASSERT(SIZEOF(.all) == 0, "Something was placed in .all!")

    /* The length of the flashed program image */
    __ld_image_length = __ld_image_end - __ld_image_start;

    /* RM 31.3.2 */
    /* The ITCM, DTCM, OCRAM configuration information */
    __ld_itcm_blocks = ((__ld_itcm_size) >> 15) + 1;
    __ld_dtcm_blocks = ((__ld_dtcm_size) >> 15) + 1;
    __ld_ocram_blocks = 16 - __ld_itcm_blocks - __ld_dtcm_blocks;
    __ld_stack_start = ORIGIN(OCRAM1) + (__ld_ocram_blocks << 15);  /* TODO: find out if this is correct */
    ASSERT(__ld_ocram_blocks >= 2, "Not enough memory allocated to OCRAM. Too much allocated to ITCM/DTCM")

    /* Now we construct the block masks */
    /* ITCM  = 0b11 */
    /* DTCM  = 0b10 */
    /* OCRAM = 0b01 */
    __ld_itcm_mask = (1 << (__ld_itcm_blocks * 2)) - 1;
    __ld_dtcm_mask = ((1 << ((__ld_itcm_blocks + __ld_dtcm_blocks) * 2)) - 1) & ~__ld_itcm_mask;
    /* xor is missing so thats why this looks strange */
    /* We start with 55555555 since that default initializes to OCRAM */
    /* We want to assign the ITCM blocks to 0x11 so we or with the itcm 1's mask */
    /* We want to assign the DTCM blocks to 0b10 so we xor with the dtcm 1's mask. This flips the 5's (0b01) to 0b10 */
    __ld_flexram_config = ((0x55555555 | __ld_dtcm_mask) & (~(0x55555555 & __ld_dtcm_mask))) | __ld_itcm_mask;
}
