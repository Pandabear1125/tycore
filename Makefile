OUTPUT = tycore

SOURCE_DIR = src
BUILD_DIR = build
TOOLS_DIR = tools

SOURCE = $(shell find $(SOURCE_DIR) -name '*.c')

SOURCE_OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(SOURCE))

# Base arm-none-eabi and Teensyduino tool paths
COMPILER_TOOLS_PATH = $(TOOLS_DIR)/compiler/arm-gnu-toolchain/bin

# arm-none-eabi tools
COMPILER_CPP	= $(COMPILER_TOOLS_PATH)/arm-none-eabi-g++
COMPILER_C		= $(COMPILER_TOOLS_PATH)/arm-none-eabi-gcc
AR				= $(COMPILER_TOOLS_PATH)/arm-none-eabi-ar
GDB				= $(COMPILER_TOOLS_PATH)/arm-none-eabi-gdb
OBJCOPY			= $(COMPILER_TOOLS_PATH)/arm-none-eabi-objcopy
OBJDUMP			= $(COMPILER_TOOLS_PATH)/arm-none-eabi-objdump
READELF			= $(COMPILER_TOOLS_PATH)/arm-none-eabi-readelf
ADDR2LINE		= $(COMPILER_TOOLS_PATH)/arm-none-eabi-addr2line
SIZE			= $(COMPILER_TOOLS_PATH)/arm-none-eabi-size

COMPILER_FLAGS  = -nostartfiles		# TODO remove this
COMPILER_FLAGS += -fno-exceptions	# disables exceptions, there is not a valid place to put the ARM.exidx such that it covers the whole address space 

CPU_FLAGS = -mcpu=cortex-m7 -mthumb -mfpu=fpv5-d16 -mfloat-abi=hard

LINKER_FLAGS = -Wl,--gc-sections,--relax,--print-memory-usage,-T$(SOURCE_DIR)/linker.ld,-Map=$(OUTPUT).map,--cref


all: clean $(OUTPUT).hex
	@rm -f $(OUTPUT).dump
	@$(OBJDUMP) -dstz  $(OUTPUT).elf > $(OUTPUT).dump


$(BUILD_DIR)/%.o : %.c
	@echo [Building $<]
	@mkdir -p $(dir $@)
	@$(COMPILER_CPP) $(CPU_FLAGS) $(COMPILER_FLAGS) -c $< -o $@


$(OUTPUT).elf : $(SOURCE_OBJS)
	@rm -f $(OUTPUT).map
	$(COMPILER_CPP) $(CPU_FLAGS) $(COMPILER_FLAGS) $(LINKER_FLAGS) $^ -o $@


$(OUTPUT).hex : $(OUTPUT).elf
	@$(OBJCOPY) -O ihex -R .eeprom $^ $@


upload: all
	tycmd upload $(OUTPUT).hex


clean:
	rm -rf $(BUILD_DIR) $(OUTPUT).elf $(OUTPUT).hex


install:
	@bash $(TOOLS_DIR)/install_compiler.sh


uninstall:
	@bash $(TOOLS_DIR)/uninstall_compiler.sh


.PHONY: all clean install
	
