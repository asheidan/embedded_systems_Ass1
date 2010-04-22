### Makefile for AVR #########################################################
TARGET     = test.elf
TARGOBJS   = test.o
TARGHEX    = $(TARGET:.elf=.hex)

DEVICE     = attiny2313
CLOCK      = 8000000
PROGRAMMER = -c stk500v2 -P avrdoper
FUSES      = -U hfuse:w:0xd9:m -U lfuse:w:0x24:m

SOURCES = $(shell ls *.c)

### Paths ####################################################################

AVR-PATH    := /usr/local/CrossPack-AVR/bin
AVR-CC      := $(AVR-PATH)/avr-gcc
AVR-OBJCOPY := $(AVR-PATH)/avr-objcopy
AVR-OBJDUMP := $(AVR-PATH)/avr-objdump
AVR-SIZE    := $(AVR-PATH)/avr-size

### Commands #################################################################

AVRDUDE = $(AVR-PATH)/avrdude $(PROGRAMMER) -p $(DEVICE)
COMPILE = $(AVR-CC) -Wall -Os -mmcu=$(DEVICE)

### Functions ################################################################

# $(call make-depend,source-file,object-file,depend-file)
define make-depend
	@# Include -MM to exclude "system headers"
	$(AVR-CC) -M -MP -MF $3 -MT $2 $1
endef

### Project Rules ############################################################

default: $(TARGHEX)

$(TARGET): $(TARGOBJS)
	$(COMPILE) -o $@ $^

### Rules ####################################################################

disasm: $(TARGET)
	@$(AVR-OBJDUMP) -d $<

sizes: $(TARGOBJS)
	@$(AVR-SIZE) --totals $(sort $^)

flash: $(TARGHEX)
	$(AVRDUDE) -U flash:w:$<:i

fuse:
	$(AVRDUDE) $(FUSES)

%.hex: %.elf
	$(AVR-OBJCOPY) -j .text -j .data -O ihex $< $@

%.o: %.c
	$(call make-depend,$<,$@,$(subst .o,.d,$@))
	$(COMPILE) -c -o $@ $<

clean:
	-rm -f *.o *.hex *.elf *.d *.tmp

# Including generated dependencies
ifneq "$(MAKECMDGOALS)" "clean"
	-include $(subst .c,.d,$(SOURCES))
endif

.PHONY: clean clean_all default

### Written mostly late at night by Emil Eriksson 2010 #######################
