.SILENT:
include ../../../mk/paw.mk

CFILES = $(shell find . -name "*.c")
CFILES += $(shell find ../aux -name "*.c")
CFILES += $(shell find ../xt -name "*.c")
CFILES += $(shell find ../ctrace -name "*.c")
CFILES += $(shell find ../io -name "*.c")
CFILES += $(shell find ../rsm -name "*.c")
CFILES += $(shell find ../drivers -name "*.c")
DFILES = $(CFILES:.c=.d)
OFILES = $(CFILES:.c=.o)

CFLAGS =			\
	$(SYS_CFLAGS)	\
	-DPRINTF_DISABLE_SUPPORT_PTRDIFF_T \
	-DPRINTF_DISABLE_SUPPORT_FLOAT	   \
	-I../head						   \
	-I../xt/flanterm/src			   \

.PHONY: all
all: $(OFILES)

-include $(DFILES)
%.o: %.c
	$(PROMPT) "CC" $<
	$(CC) -c $(CFLAGS) $< -o $@
