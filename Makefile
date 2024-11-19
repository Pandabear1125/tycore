OUTPUT = tycore

SOURCE_DIR = src
BUILD_DIR = build
TOOLS_DIR = tools

SOURCE = $(shell find $(SOURCE_DIR) -name '*.cpp' -or -name '*.c')

SOURCE_OBJS = $(SOURCE:%=$(BUILD_DIR)/%.o)

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

COMPILER_FLAGS += -fno-exceptions -Wpedantic						# disables exceptions, there is not a valid place to put the ARM.exidx such that it covers the whole address space 
COMPILER_FLAGS += -Wall -Wextra -Wpedantic -Werror -Wfatal-errors 	# enable all warnings and treat them as errors
COMPILER_FLAGS += --specs=nano.specs								# use the newlib nano library, significantly reduces binary size
COMPILER_FLAGS += -ffunction-sections -fdata-sections 				# put functions and data in separate sections

CXX_FLAGS 		= -std=gnu++17							# use C++17 standard with GNU extensions. Extensions are needed for various things like asm and inline
C_FLAGS 		= -std=gnu11							# use C11 standard with GNU extensions. Extensions are needed for various things like asm and inline

# Cortex-M7 specific flags
CPU_FLAGS 		= -mcpu=cortex-m7 -mthumb -mfpu=fpv5-d16 -mfloat-abi=hard

# Linker flags, --gc-sections removes unused sections, --relax allows for smaller instruction sizes where possible. Others are for debugging
LINKER_FLAGS 	= -Wl,--gc-sections,--relax,--print-memory-usage,-T$(SOURCE_DIR)/linker.ld,-Map=$(OUTPUT).map,--cref


all: clean $(OUTPUT).hex
	@rm -f $(OUTPUT).dump
	@$(OBJDUMP) -dstz  $(OUTPUT).elf > $(OUTPUT).dump


$(BUILD_DIR)/%.c.o : %.c
	@echo [Building $<]
	@mkdir -p $(dir $@)
	@$(COMPILER_C) $(C_FLAGS) $(CPU_FLAGS) $(COMPILER_FLAGS) -c $< -o $@
	@$(OBJDUMP) -dstz $@ > $@.dump


$(BUILD_DIR)/%.cpp.o : %.cpp
	@echo [Building $<]
	@mkdir -p $(dir $@)
	@$(COMPILER_CPP) $(CXX_FLAGS) $(CPU_FLAGS) $(COMPILER_FLAGS) -c $< -o $@
	@$(OBJDUMP) -dstz $@ > $@.dump


$(OUTPUT).elf : $(SOURCE_OBJS)
	@rm -f $(OUTPUT).map
	$(COMPILER_CPP) $(CXX_FLAGS) $(CPU_FLAGS) $(COMPILER_FLAGS) $(LINKER_FLAGS) $^ -o $@


$(OUTPUT).hex : $(OUTPUT).elf
	@$(OBJCOPY) -O ihex -R .eeprom $^ $@


upload: all
	tycmd upload $(OUTPUT).hex


clean:
	rm -rf $(OUTPUT).dump $(OUTPUT).map
	rm -rf $(BUILD_DIR) $(OUTPUT).elf $(OUTPUT).hex


install:
	@bash $(TOOLS_DIR)/install_compiler.sh


uninstall:
	@bash $(TOOLS_DIR)/uninstall_compiler.sh


.PHONY: all clean install
	
