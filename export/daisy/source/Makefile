# Project Name
TARGET = HeavyDaisy_olm_main_

# Library Locations
LIBDAISY_DIR = ../../libdaisy

LDSCRIPT = D:\git_workspaces\DroneSynth\olm-pd\sram_linker_sdram.lds

APP_TYPE = BOOT_SRAM

# OPTIMIZER
OPT = -O3

# Project Source
C_SOURCES = $(wildcard *.c)
CPP_SOURCES = $(wildcard *.cpp)

# Core location, and generic makefile.
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile