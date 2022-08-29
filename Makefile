##########################################################################################################################
# File automatically-generated by tool: [projectgenerator] version: [3.15.2] date: [Mon Aug 29 13:23:18 CST 2022]
##########################################################################################################################

# ------------------------------------------------
# Generic Makefile (based on gcc)
#
# ChangeLog :
#	2017-02-10 - Several enhancements + project update mode
#   2015-07-22 - first version
# ------------------------------------------------

######################################
# target
######################################
TARGET = eva


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og


#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

######################################
# source
######################################
# C sources
C_SOURCES =  \
Src/main.c \
Src/gpio.c \
Src/freertos.c \
Src/adc.c \
Src/can.c \
Src/dma.c \
Src/iwdg.c \
Src/mbedtls.c \
Src/hardware_rng.c \
Src/rng.c \
Src/tim.c \
Src/usart.c \
Src/stm32f2xx_it.c \
Src/stm32f2xx_hal_msp.c \
Src/stm32f2xx_hal_timebase_tim.c \
Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_adc.c \
Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_adc_ex.c \
Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal.c \
Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_rcc.c \
Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_rcc_ex.c \
Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_cortex.c \
Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_flash.c \
Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_flash_ex.c \
Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_pwr.c \
Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_pwr_ex.c \
Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_gpio.c \
Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_dma.c \
Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_dma_ex.c \
Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_exti.c \
Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_can.c \
Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_iwdg.c \
Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_rng.c \
Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_tim.c \
Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_tim_ex.c \
Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_uart.c \
Src/system_stm32f2xx.c \
Middlewares/Third_Party/FreeRTOS/Source/croutine.c \
Middlewares/Third_Party/FreeRTOS/Source/event_groups.c \
Middlewares/Third_Party/FreeRTOS/Source/list.c \
Middlewares/Third_Party/FreeRTOS/Source/queue.c \
Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c \
Middlewares/Third_Party/FreeRTOS/Source/tasks.c \
Middlewares/Third_Party/FreeRTOS/Source/timers.c \
Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.c \
Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c \
Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/port.c \
Middlewares/Third_Party/mbedTLS/library/cipher_wrap.c \
Middlewares/Third_Party/mbedTLS/library/dhm.c \
Middlewares/Third_Party/mbedTLS/library/ecp_curves.c \
Middlewares/Third_Party/mbedTLS/library/entropy_poll.c \
Middlewares/Third_Party/mbedTLS/library/md_wrap.c \
Middlewares/Third_Party/mbedTLS/library/memory_buffer_alloc.c \
Middlewares/Third_Party/mbedTLS/library/pem.c \
Middlewares/Third_Party/mbedTLS/library/pk_wrap.c \
Middlewares/Third_Party/mbedTLS/library/platform_util.c \
Middlewares/Third_Party/mbedTLS/library/rsa_internal.c \
Middlewares/Third_Party/mbedTLS/library/ssl_ciphersuites.c \
Middlewares/Third_Party/mbedTLS/library/version_features.c  

# ASM sources
ASM_SOURCES =  \
startup_stm32f207xx.s


#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
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
C_DEFS =  \
-DMBEDTLS_CONFIG_FILE=\"mbedtls_config.h\" \
-DUSE_HAL_DRIVER \
-DSTM32F207xx


# AS includes
AS_INCLUDES =  \
-IInc

# C includes
C_INCLUDES =  \
-IInc \
-IDrivers/STM32F2xx_HAL_Driver/Inc \
-IDrivers/STM32F2xx_HAL_Driver/Inc/Legacy \
-IMiddlewares/Third_Party/FreeRTOS/Source/include \
-IMiddlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS \
-IMiddlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 \
-IMiddlewares/Third_Party/mbedTLS/include/mbedtls \
-IDrivers/CMSIS/Device/ST/STM32F2xx/Include \
-IMiddlewares/Third_Party/mbedTLS/include \
-IDrivers/CMSIS/Include


# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = STM32F207VETx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections
include user.mk

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

include override.mk

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	

include target.mk
	
$(BUILD_DIR):
	mkdir $@		

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***