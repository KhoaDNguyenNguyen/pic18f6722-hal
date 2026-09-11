CC = /opt/microchip/xc8/v4.00/bin/xc8-cc
MCU = 18F6722
DFP = $(HOME)/.local/share/microchip/dfp/PIC18Fxxxx_DFP/xc8

ALL_SRC = $(wildcard src/*.c)
LIB_SRC = $(filter-out src/main.c, $(ALL_SRC))
MAIN_SRC ?= src/main.c

INC = -I./inc
TARGET = build/main.hex

TARGET_DEF ?= -DTARGET_BOARD
CFLAGS = -mcpu=$(MCU) -mdfp="$(DFP)" -std=c99 -O1 $(TARGET_DEF)

.PHONY: all flash test erase clean pre_build sim board

all: clean pre_build $(TARGET)

pre_build:
	@mkdir -p build

$(TARGET): $(LIB_SRC) $(MAIN_SRC)
	$(CC) $(CFLAGS) $(INC) $(LIB_SRC) $(MAIN_SRC) -o $(TARGET)

board:
	$(MAKE) all TARGET_DEF=-DTARGET_BOARD

sim:
	$(MAKE) all TARGET_DEF=-DTARGET_SIMULATION

flash: board
	pk2cmd -P -M -F $(TARGET) -R

test:
	$(MAKE) flash MAIN_SRC=test/test_main.c

erase:
	pk2cmd -P -E

clean:
	rm -rf build/
	rm -f *.hex *.p1 *.d *.cmf *.elf *.hxl *.sym *.o *.s *.rlf *.sdb *.lst
	rm -f src/*.p1 src/*.d src/*.o src/*.s src/*.rlf src/*.sdb src/*.lst
	rm -f test/*.p1 test/*.d test/*.o test/*.s test/*.rlf test/*.sdb test/*.lst
