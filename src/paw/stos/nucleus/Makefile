.SILENT:
include ../../../mk/paw.mk

CFILES = $(shell ls | grep *.c)
CFILES += $(shell find ../aux -name "*.c")
CFILES += $(shell find ../xt -name "*.c")
CFILES += $(shell find ../ctrace -name "*.c")
CFILES += $(shell find ../io -name "*.c")
DFILES = $(CFILES:.c=.d)
OFILES = $(CFILES:.c=.o)

CFLAGS =			\
	$(SYS_CFLAGS)	\
	-DPRINTF_DISABLE_SUPPORT_PTRDIFF_T \
	-DPRINTF_DISABLE_SUPPORT_FLOAT	   \
	-I../head

.PHONY: all
all: $(OFILES)

-include $(DFILES)
%.o: %.c
	$(PROMPT) "CC" $<
	$(CC) -c $(CFLAGS) $< -o $@
