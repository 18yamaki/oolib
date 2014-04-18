# A List Class for C.
# imitates object oriented on C.
# @copyright MIT License.
# @author y.yamaki

PROGRAM		= List.elf

SRCS		= $(wildcard *.c)
OBJS		= $(addsuffix .o,$(basename $(SRCS)))
DEPS		= $(addsuffix .dep,$(basename $(SRCS)))

all: $(PROGRAM)
$(PROGRAM): $(OBJS)
	$(LINK.o) -o $@ $^

%.dep: %.c
	($(CC) -MM $(CPPFLAGS) $(TARGET_ARCH) $< > $@.$$$$ &&	\
	sed 's%\($*\).o[ :]*%\1.o $@ : %g' < $@.$$$$ > $@;	\
	$(RM) $@.$$$$)

clean:
	$(RM) $(PROGRAM) $(OBJS)

distclean:
	$(RM) $(PROGRAM) $(OBJS) $(DEPS)

ifneq ($(findstring clean, $(MAKECMDGOALS)),clean)
-include $(DEPS)
endif

