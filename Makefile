-include config.mk

PROXY        = victory
LDFLAGS 	= -mdll -Wl,--enable-stdcall-fixup -Wl,--strip-all -Wl,--exclude-all-symbols
NFLAGS       = -f elf -Iinc/
CC            = gcc
CFLAGS       = -std=c99 -Iinc/
CPPFLAGS       = -masm=intel -Iinc/ -Os -mtune=i586


OBJS = w2p.o dllmain.o
       
NASM        ?= nasm

.PHONY: default

%.o: %.asm
	$(NASM) $(NFLAGS) -o $@ $<

$(PROXY).w2p: $(OBJS) modexp.def
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ -lstdc++ -static

clean:
	$(RM) $(OBJS) $(PROXY).w2p
