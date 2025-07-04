OUTPUT = tycore

SOURCE_DIR = src
BUILD_DIR = build
TOOLS_DIR = tools

SOURCE = $(shell find $(SOURCE_DIR) -name '*.cpp' -or -name '*.c')
FORMAT_SOURCE = $(shell find $(SOURCE_DIR) -name '*.cpp' -or -name '*.c' -or -name '*.h' -or -name '*.hpp')

SOURCE_OBJS = $(SOURCE:%=$(BUILD_DIR)/%.o)
SOURCE_DEPS = $(SOURCE:%=$(BUILD_DIR)/%.d)

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
COMPILER_FLAGS += -Wall -Wextra -Wpedantic							# enable all warnings and treat them as errors
COMPILER_FLAGS += --specs=nano.specs								# use the newlib nano library, significantly reduces binary size
COMPILER_FLAGS += -ffunction-sections -fdata-sections				# put functions and data in separate sections
COMPILER_FLAGS += -O2												# optimize for speed
COMPILER_FLAGS += -fdump-ipa-all									# dump interprocedural analysis, useful for debugging low-level performance
COMPILER_FLAGS += -MMD -MP											# generate dependencies

CXX_FLAGS 		= -std=gnu++11										# use C++11 standard with GNU extensions. Extensions are needed for various things like asm and inline
C_FLAGS 		= -std=gnu11										# use C11 standard with GNU extensions. Extensions are needed for various things like asm and inline

# Cortex-M7 specific flags
CPU_FLAGS 		= -mcpu=cortex-m7 -mthumb -mfpu=fpv5-d16 -mfloat-abi=hard

# Linker flags, --gc-sections removes unused sections, --relax allows for smaller instruction sizes where possible. Others are for debugging
LINKER_FLAGS 	= -Wl,--gc-sections,--relax,--print-memory-usage,-T$(SOURCE_DIR)/linker.ld,-Map=$(OUTPUT).map,--cref

# Utilize all available CPU cores for parallel build
MAKEFLAGS += -j$(nproc)


# TODO: eventually get rid of this clean
all: clean
    # automatically format code 
	@clang-format -i -style=file $(FORMAT_SOURCE)
    # verify the register map correctness
    # TODO: remove this once the regmap is finished
	@python3 $(TOOLS_DIR)/check_register_map.py $(SOURCE_DIR)/imxrt_regmap.h
    # use bear to generate compile_commands.json
	bear -- make build


build: $(OUTPUT).hex


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
	@echo "[Linking] $^\n"
	@$(COMPILER_CPP) $(CXX_FLAGS) $(CPU_FLAGS) $(COMPILER_FLAGS) $(LINKER_FLAGS) $^ -o $@
	@$(OBJDUMP) -dstz  $(OUTPUT).elf > $(OUTPUT).dump


$(OUTPUT).hex : $(OUTPUT).elf
	@$(OBJCOPY) -O ihex -R .eeprom $^ $@


upload: all
	tycmd upload $(OUTPUT).hex


clean:
	rm -rf $(OUTPUT).dump $(OUTPUT).map
	rm -rf $(BUILD_DIR) $(OUTPUT).elf $(OUTPUT).hex
	

install:
	sudo apt install -y build-essential
	sudo apt install -y bear
	sudo apt install -y clangd
	sudo apt install -y clang-format
	@bash $(TOOLS_DIR)/install_compiler.sh


uninstall:
	@bash $(TOOLS_DIR)/uninstall_compiler.sh


.PHONY: all build upload clean install uninstall


# Include compile dependencies for proper incremental build
-include $(SOURCE_DEPS)
