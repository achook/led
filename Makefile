#Main application file name
MAIN_APP = main
#Main hex file path in windows format

MAIN_PATH = $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
OUTPUT_PATH = $(MAIN_PATH)output
OUTPUT_APP = $(OUTPUT_PATH)/$(MAIN_APP)
MAIN_HEX_PATH = $(OUTPUT_APP).hex

# Compiler and other Section
CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE := avrdude

#Options for avr-gcc
CFLAGS = -g -Os -std=c11 -o

#Linking options for avr-gcc
LFLAGS = -Os -mmcu=attiny85 -o

#Options for HEX file generation
HFLAGS = -j .text -j .data -O ihex

#Options for avrdude to burn the hex file
#MMCU model here according to avrdude options
DUDEFLAGS = -c
DUDEFLAGS += usbasp 
DUDEFLAGS += -p
DUDEFLAGS += attiny85
DUDEFLAGS += -b 
DUDEFLAGS += 19200 
DUDEFLAGS += -U flash:w:$(MAIN_HEX_PATH):i

# Sources files needed for building the application 
SRC = $(MAIN_APP).c
SRC += 

# The headers files needed for building the application
INCLUDE = -I. 
INCLUDE += 

# commands Section
Burn : Build
	$(AVRDUDE) $(DUDEFLAGS)

Build : $(OUTPUT_APP).elf
	$(OBJCOPY) $(HFLAGS) $< $(OUTPUT_APP).hex
	
$(OUTPUT_APP).elf: $(OUTPUT_APP).o
	$(CC) $(SRC) $(INCLUDE) $(LFLAGS) $@
	
$(OUTPUT_APP).o:$(SRC)
	$(CC) $^ $(INCLUDE) $(CFLAGS) $@