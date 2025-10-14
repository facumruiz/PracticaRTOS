CC                    := gcc
BIN                   := posix_demo

BUILD_DIR             := ./build
BUILD_DIR_ABS         := $(abspath $(BUILD_DIR))

FREERTOS_DIR_REL      := ../../../FreeRTOS
FREERTOS_DIR          := $(abspath $(FREERTOS_DIR_REL))

FREERTOS_PLUS_DIR_REL := ../../../FreeRTOS-Plus
FREERTOS_PLUS_DIR     := $(abspath $(FREERTOS_PLUS_DIR_REL))

KERNEL_DIR            := ${FREERTOS_DIR}/Source

# -------------------- Includes --------------------
INCLUDE_DIRS          := -I.
INCLUDE_DIRS          += -I${KERNEL_DIR}/include
INCLUDE_DIRS          += -I${KERNEL_DIR}/portable/ThirdParty/GCC/Posix
INCLUDE_DIRS          += -I${KERNEL_DIR}/portable/ThirdParty/GCC/Posix/utils
INCLUDE_DIRS          += -I${FREERTOS_DIR}/Demo/Common/include
INCLUDE_DIRS          += -I${FREERTOS_PLUS_DIR}/Source/FreeRTOS-Plus-Trace/Include

# -------------------- Source files --------------------
# Archivos de tu demo
SOURCE_FILES          := main.c supporting_functions.c freertos_hooks.c

# Archivos de FreeRTOS kernel
SOURCE_FILES         += $(wildcard ${FREERTOS_DIR}/Source/*.c)

# Memory manager (usar malloc/free)
SOURCE_FILES         += ${KERNEL_DIR}/portable/MemMang/heap_3.c

# POSIX port
SOURCE_FILES         += ${KERNEL_DIR}/portable/ThirdParty/GCC/Posix/utils/wait_for_event.c
SOURCE_FILES         += ${KERNEL_DIR}/portable/ThirdParty/GCC/Posix/port.c

# -------------------- Flags --------------------
CFLAGS                := -ggdb3
LDFLAGS               := -ggdb3 -pthread
CPPFLAGS              := $(INCLUDE_DIRS) -DBUILD_DIR=\"$(BUILD_DIR_ABS)\"
CPPFLAGS              += -D_WINDOWS_

ifeq ($(TRACE_ON_ENTER),1)
  CPPFLAGS            += -DTRACE_ON_ENTER=1
else
  CPPFLAGS            += -DTRACE_ON_ENTER=0
endif

ifeq ($(COVERAGE_TEST),1)
  CPPFLAGS            += -DprojCOVERAGE_TEST=1
else
  CPPFLAGS            += -DprojCOVERAGE_TEST=0
endif

ifdef PROFILE
  CFLAGS              += -pg  -O0
  LDFLAGS             += -pg  -O0
else
  CFLAGS              += -O3
  LDFLAGS             += -O3
endif

ifdef SANITIZE_ADDRESS
  CFLAGS              += -fsanitize=address -fsanitize=alignment
  LDFLAGS             += -fsanitize=address -fsanitize=alignment
endif

ifdef SANITIZE_LEAK
  LDFLAGS             += -fsanitize=leak
endif

# -------------------- Build --------------------
OBJ_FILES = $(SOURCE_FILES:%.c=$(BUILD_DIR)/%.o)
DEP_FILE  = $(OBJ_FILES:%.o=%.d)

${BIN} : $(BUILD_DIR)/$(BIN)

${BUILD_DIR}/${BIN} : ${OBJ_FILES}
	-mkdir -p ${@D}
	$(CC) $^ $(LDFLAGS) -o $@

-include ${DEP_FILE}

${BUILD_DIR}/%.o : %.c Makefile
	-mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -c $< -o $@

# -------------------- Clean --------------------
.PHONY: clean
clean:
	-rm -rf $(BUILD_DIR)

# -------------------- Profiling --------------------
GPROF_OPTIONS := --directory-path=$(INCLUDE_DIRS)
profile:
	gprof -a -p --all-lines $(GPROF_OPTIONS) $(BUILD_DIR)/$(BIN) $(BUILD_DIR)/gmon.out > $(BUILD_DIR)/prof_flat.txt
	gprof -a --graph $(GPROF_OPTIONS) $(BUILD_DIR)/$(BIN) $(BUILD_DIR)/gmon.out > $(BUILD_DIR)/prof_call_graph.txt
