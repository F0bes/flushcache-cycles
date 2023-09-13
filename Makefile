EE_BIN = flushcache_cycles.elf
EE_OBJS = flushcache_cycles.o
EE_LIBS = -lkernel

EE_CFLAGS = -Werror
all: $(EE_BIN)

clean:
	rm -f $(EE_OBJS) $(EE_BIN)
	make -C iop clean

run: $(EE_BIN)
	ps2client execee host:$(EE_BIN)

wsl: $(EE_BIN)
	$(PCSX2) -elf "$(shell wslpath -w $(shell pwd))/$(EE_BIN)"

emu: $(EE_BIN)
	$(PCSX2) -elf "$(shell pwd)/$(EE_BIN)"

reset:
	ps2client reset
	ps2client netdump


include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal
