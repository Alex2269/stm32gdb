
TARGET = stm32f103-ll-trace-swo

# debug build?
DEBUG = 1
# optimization
OPT = -O3

# debug output periph regs
OPT += -g3

ENABLE_SEMIHOSTING ?= 0

# source path
ROOT_SRC_DIR = .
SOURCES_DIR   += $(shell find ${ROOT_SRC_DIR} -type d)

# firmware library path
PERIFLIB_PATH = 

# Build path
BUILD_DIR = build


ROOT_DIR = .
# C sources
C_SOURCES   += $(shell find ${ROOT_DIR} -name '*.c')

# ASM sources
ASM_SOURCES += $(shell find ${ROOT_DIR} -name 'startup_*.s')


PERIFLIB_SOURCES = 


#######################################
# binaries
#######################################
BINPATH = /usr/bin
PREFIX = arm-none-eabi-
CC = $(BINPATH)/$(PREFIX)gcc -std=c11
AS = $(BINPATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(BINPATH)/$(PREFIX)objcopy
AR = $(BINPATH)/$(PREFIX)ar
SZ = $(BINPATH)/$(PREFIX)size
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m3

# fpu
# NONE for Cortex-M0/M0+/M3

# float-abi

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS :=
C_DEFS += -DSTM32F103xB
C_DEFS += -DUSE_FULL_LL_DRIVER
C_DEFS += -DHSE_VALUE=8000000
C_DEFS += -DHSE_STARTUP_TIMEOUT=100
C_DEFS += -DLSE_STARTUP_TIMEOUT=5000
C_DEFS += -DLSE_VALUE=32768
C_DEFS += -DHSI_VALUE=8000000
C_DEFS += -DLSI_VALUE=40000

C_DEFS += -DUART_HOSTING=1
# C_DEFS += -DUART_HOSTING=0


ifeq (1,$(ENABLE_SEMIHOSTING))
C_DEFS += -DSEMIHOSTING_ENABLE=1
endif


# AS includes
AS_INCLUDES = 

# C includes
ROOT_INC_DIR = .
C_INCLUDES += $(shell find ${ROOT_INC_DIR} -type d -name Inc | sed 's,\./,-I,g')
C_INCLUDES += $(shell find ${ROOT_INC_DIR} -type d -name Include | sed 's,\./,-I,g')

# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif

# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"

# link script
LINK_DIR = .
LDSCRIPT += $(shell find ${LINK_DIR} -name '*_FLASH.ld')

# libraries
LIBS += -lm -lc

ifeq (1,$(ENABLE_SEMIHOSTING))
LIBS += --specs=rdimon.specs -lrdimon
# LIBS += --specs=nano.specs -lrdimon_nano # no float printf
else
LIBS += --specs=nano.specs -lnosys
endif

LIBDIR =
LDFLAGS = $(MCU) -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@
	
$(BUILD_DIR):
	mkdir $@

#######################################
# Make flash
#	"write through st-link v2"
# Make stm32flash:
#	"write through uart /dev/ttyUSB0"
#######################################
flash:
	st-flash --reset write $(BUILD_DIR)/$(TARGET).bin 0x8000000

stm32flash:
	stm32flash -w $(BUILD_DIR)/$(TARGET).bin -v -g 0x0 /dev/ttyUSB0
#######################################
debug:
	arm-none-eabi-gdb \
	-iex 'target extended | openocd -f interface/stlink-v2.cfg -f target/stm32f1x.cfg \
	-c "adapter_khz 1800" -c "interface hla" -c "gdb_port pipe" ' \
	-iex 'monitor halt' \
	-iex 'monitor tpiu config internal itm_swo.fifo uart off 72000000' \
	-iex 'monitor itm port 0 on' \
	$(BUILD_DIR)/$(TARGET).elf

# # collect ITM data
# mkfifo itm_swo.fifo
# cat /dev/ttyS0 itm_swo.fifo
#######################################

# # 	-iex 'monitor tpiu config internal itm_swo.fifo uart off 72000000' \
# # 	-iex 'monitor tpiu config external uart off 72000000 1800000' \

# # send captured ITM to the file itm_swo.fifo

# # (the microcontroller SWO pin must be connected to the programmer SWO pin)
# # 72000000 must match the core clock frequency
# monitor tpiu config internal itm.txt uart off 72000000

# # OR: make the microcontroller SWO pin output compatible with UART (8N1)
# # 72000000 must match the core clock frequency
# # 4000000 is the frequency of the SWO pin
# monitor tpiu config external uart off 72000000 4000000

# # enable ITM port 0
# monitor itm port 0 on


# clean up
#######################################
clean:
	-rm -fR .dep $(BUILD_DIR)

# *** EOF ***
